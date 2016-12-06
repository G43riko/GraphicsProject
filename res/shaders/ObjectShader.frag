#version 330

in vec2 pass_Texture;
in vec3 toLightVector[8];
in vec3 toCameraVector;
in vec3 norm;

in float visibility;
in float distance;

layout (location = 0) out vec4 FragmentColor;
layout (location = 1) out vec4 BrightColor;
layout (location = 2) out vec4 GrayscaleColor;
layout (location = 3) out vec4 DistColor;


const int flagTextures = 0x01;
const int flagNormalMaps = 0x02;
const int flagLight = 0x04;
const int flagSpecular = 0x08;
const int flagFlog = 0x10;

const vec3 skyColor = vec3(1);

uniform sampler2D textureSampler;
uniform sampler2D normalSampler;
uniform vec3 lightColor[8];
uniform vec3 attenuation[8];
uniform int levels;
uniform int options;

uniform float shineDumper;
uniform float reflectivity;

void main() {
    vec4 normalMapValue = vec4(0, 0, 1, 1);
    if((options & flagNormalMaps) == flagNormalMaps)
        normalMapValue = 2.0 * texture(normalSampler, pass_Texture) - 1.0;

    vec3 unitNormal = normalize(normalMapValue.rgb);
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 totalDiffuse  = vec3(0.0f);
    vec3 totalSpecular = vec3(0.0f);

    if((options & flagLight) == flagLight){
        for(int i=0 ; i<8 ; i++){
            if(lightColor[i] == vec3(0.0))
                    break;

            float distance = length(toLightVector[i]);
            float attFactor = attenuation[i].x + (attenuation[i].y * distance) + (attenuation[i].z * distance * distance);
            vec3 unitLightVector = normalize(toLightVector[i]);

            float nDot1 = dot(unitNormal, unitLightVector);
            float brightness = max(nDot1, 0.0f);

            if((options & flagSpecular) == flagSpecular){
                vec3 lightDirection = -unitLightVector;
                vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
                float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
                specularFactor = max(specularFactor, 0.0f);
                float dampedFactor = pow(specularFactor, shineDumper);
                totalSpecular += (dampedFactor * reflectivity * lightColor[i]) / attFactor;
            }
            totalDiffuse += (brightness * lightColor[i]) / attFactor;
        }
    }
    totalDiffuse = max(totalDiffuse, 0.2);
    GrayscaleColor = texture(textureSampler, pass_Texture);
    vec4 texture = vec4(1);

    if((options & flagTextures) == flagTextures)
        texture = GrayscaleColor;

    FragmentColor = vec4(totalDiffuse, 1.0) * texture + vec4(totalSpecular, 1.0f);
    if((options & flagFlog) == flagFlog)
        FragmentColor = mix(vec4(skyColor, 1), FragmentColor, visibility);
    BrightColor = vec4(norm, 1);
    DistColor = vec4(1 - vec3(distance / 50), 1);
}