#version 330
in vec2 pass_Texture;
in vec3 surfaceNormal;
in vec3 toLightVector[8];
in vec4 shadowCoords;
in vec3 reflectedVector;
in vec3 refractedVector;

struct Material{
    sampler2D diffuseSampler;
    sampler2D normalSampler;
    sampler2D alphaSampler;
    sampler2D reflectSampler;
    samplerCube environmentalMap;
    int hasNormalMap;
    int hasAlphaMap;
    int hasReflectMap;
    int hasEnvironmentalMap;
    float shineDumper;
    float reflectivity;
};

struct Options{
    int renderShadow;
};

struct Light{
    int type;
    vec3 direction;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 position;
    vec3 attenuation;
    float cutOff;
    float outerCutOff;
};

out vec4 FragmentColor;
out vec4 Normals;
out vec4 Texture;

uniform sampler2D textureSampler;
uniform samplerCube environmentalMap;
uniform sampler2D shadowMap;
uniform vec3 lightColor[8];
uniform int levels;

const vec3 ambientLight = vec3(1, 0.9, 1);
void main() {
    //FragmentColor = vec4(vec3(0.0f, 1.0f, 1.0f), 1.0f);
    float objectNearestLight = texture(shadowMap, shadowCoords.xy).r;
    float lightFactor = 1.0f;
//    //SHADOWS
//    if(shadowCoords.z > objectNearestLight){
//        lightFactor = 1.0 - 0.4;
//    }

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDifuse = vec3(0);

//    DirLight sun = DirLight(vec3(-1, -1, 1), vec3(1), vec3(0));
//
//    /*DERECTIONAL LIGHT*/
//    vec3 lightDir = normalize(-sun.direction);
//    float diff = max(dot(unitNormal, lightDir), 0.0);
//    totalDifuse = sun.diffuseColor * diff;

    /*POINT LIGHTS*/
    for(int i=0 ; i<8 ; i++){
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = nDot1;
        if(levels > 0){
            float level = floor(brightness * levels);
            brightness = level / levels;
        }
        totalDifuse += brightness * lightColor[i];
    }
    totalDifuse *= lightFactor;
    totalDifuse = max(totalDifuse, 0.1);
    vec4 diffuseColor = texture(textureSampler, pass_Texture);


    FragmentColor = vec4(totalDifuse * ambientLight, 1.0) * diffuseColor;
    Normals = abs(vec4(unitNormal, 1.0));
    Texture = diffuseColor;
    /*
    vec4 reflectedColor = texture(environmentalMap, reflectedVector);
    vec4 refractedColor = texture(environmentalMap, refractedVector);
    vec4 environmentalColor = mix(reflectedColor, refractedColor, 0);
    FragmentColor = mix(FragmentColor, environmentalColor, 0.6);
    */

}