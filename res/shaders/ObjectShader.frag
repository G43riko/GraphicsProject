#version 330
in vec2 pass_Texture;
in vec3 toLightVector[8];

out vec4 FragmentColor;

uniform sampler2D textureSampler;
uniform sampler2D normalSampler;
uniform vec3 lightColor[8];
uniform vec3 attenuation[8];
uniform int levels;

void main() {
    vec4 normalMapValue = 2.0 * texture(normalSampler, pass_Texture) - 1.0;
    vec3 unitNormal = normalize(normalMapValue.rgb);
    vec3 totalDiffuse  = vec3(0.0f);

    for(int i=0 ; i<8 ; i++){
        if(lightColor[i] == vec3(0))
    			break;
        float distance = length(toLightVector[i]);
        float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.0);
        totalDiffuse += (brightness * lightColor[i]) / attFactor;
    }
    totalDiffuse = max(totalDiffuse, 0.2);

    FragmentColor = vec4(totalDiffuse, 1.0) * texture(textureSampler, pass_Texture);

}