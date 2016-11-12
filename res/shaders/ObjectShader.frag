#version 330
in vec2 pass_Texture;
in vec3 toLightVector[8];
in vec3 toCameraVector;

layout (location = 0) out vec4 FragmentColor;
layout (location = 1) out vec4 BrightColor;

uniform sampler2D textureSampler;
uniform sampler2D normalSampler;
uniform vec3 lightColor[8];
uniform vec3 attenuation[8];
uniform int levels;

uniform float shineDumper;
uniform float reflectivity;

void main() {
    vec4 normalMapValue = 2.0 * texture(normalSampler, pass_Texture) - 1.0;
    vec3 unitNormal = normalize(normalMapValue.rgb);
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 totalDiffuse  = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);

    for(int i=0 ; i<8 ; i++){
        if(lightColor[i] == vec3(0.0))
    			break;

        float distance = length(toLightVector[i]);
        float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.0f);

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
        float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
        specularFactor = max(specularFactor, 0.0f);
        float dampedFactor = pow(specularFactor, shineDumper);
        totalSpecular += (dampedFactor * reflectivity * lightColor[i]) / attFactor;

        totalDiffuse += (brightness * lightColor[i]) / attFactor;
    }
    totalDiffuse = max(totalDiffuse, 0.2);

    FragmentColor = vec4(totalDiffuse, 1.0) * texture(textureSampler, pass_Texture) + vec4(totalSpecular, 1.0f);
    BrightColor = vec4(1, 0, 1, 1);
}