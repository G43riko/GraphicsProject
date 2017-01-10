#version 330

in vec2 textureCoords;
in vec3 toCameraVector;
in vec4 clipSpace;
in vec3 fromLightVector[8];

out vec4 out_Color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform vec3 lightColor[8];
uniform float moveFactor;
uniform float refractiveRation;
uniform float waveStrength;
uniform float shineDumper;
uniform float reflectivity;

void main(void) {
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;

    vec2 refractTextCoords = vec2(ndc.x, ndc.y);
    vec2 reflectTextCoords = vec2(ndc.x, -ndc.y);

    float near = 0.1f;
    float far = 1000.0f;
    float depth = texture(depthMap, refractTextCoords).r;
    float floorDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));

    depth = gl_FragCoord.z;
    float waterDistance = 2.0 * near * far / (far + near - (2.0 * depth - 1.0) * (far - near));
    float waterDepth = floorDistance - waterDistance;

//    vec2 distortion1 = (texture(dudvMap, vec2(textureCoords.x + moveFactor,  textureCoords.y)).rg * 2.0  - 1.0) * waveStrength;
//    vec2 distortion2 = (texture(dudvMap, vec2(-textureCoords.x + moveFactor,  textureCoords.y + moveFactor)).rg * 2.0  - 1.0) * waveStrength;
//    vec2 totalDistortion = distortion1 + distortion2;
	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg*0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y+moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength * clamp(waterDepth, 0.0f, 1.0f);

    refractTextCoords += totalDistortion;
    refractTextCoords = clamp(refractTextCoords, 0.0001, 0.999);

    reflectTextCoords += totalDistortion;
    reflectTextCoords.x = clamp(reflectTextCoords.x, 0.0001, 0.999);
    reflectTextCoords.y = clamp(reflectTextCoords.y, -0.999, -0.0001);

    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
    refractiveFactor = pow(refractiveFactor, refractiveRation);

    vec4 reflectColor = texture(reflectionTexture, reflectTextCoords);
    vec4 refractColor = texture(refractionTexture, refractTextCoords);

    vec4 normalMapColor = texture(normalMap, totalDistortion);
    vec3 normal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b, normalMapColor.g * 2.0 - 1.0);
    normal = normalize(normal);

    vec3 totalSpecular = vec3(0.0);
    for(int i=0 ; i<8 ; i++){
        vec3 reflectedLight = reflect(normalize(fromLightVector[i]), normal);
        float specular = max(dot(reflectedLight, viewVector), 0.0);
        specular = pow(specular, shineDumper);
        totalSpecular += lightColor[i] * specular * reflectivity * clamp(waterDepth, 0.0f, 1.0f);
    }


	//out_Color = vec4(0.0, 0.0, 1.0, 1.0);
	out_Color = mix(reflectColor, refractColor, refractiveFactor);
	out_Color = mix(out_Color, vec4(0.0, 0.3, 0.5, 1.0), 0.2) + vec4(totalSpecular, 0.0);
	//out_Color = vec4(vec3(waterDepth), 1.0f);

    out_Color.a = clamp(waterDepth, 0.0f, 1.0f);
}