#version 330
struct LightData{
    int type;
    vec3 position;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 attenuation;
    vec3 direction;
    float cutOff;
    float outerCutOff;
};
struct Material{
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float reflectivity;
    float shineDumper;
};

struct PointLight {
    vec3 position;
    vec3 attenuation;
    vec3 diffuseColor;
    vec3 specularColor;
};

const int MAX_LIGHTS = 8;

in vec3 toLightVector[MAX_LIGHTS];
in vec3 surfaceNormal;
in vec2 pass_Texture;
in vec3 toCameraVector;

out vec4 out_color;

const int NUM_X = 8;
const int NUM_Y = 8;
const float offsetX = 1.0f / NUM_X;
const float offsetY = 1.0f / NUM_Y;
//const float shineDumper = 100.0f;
//const float reflectivity = 0.8f;

uniform vec4 color;
uniform LightData lightData[MAX_LIGHTS];
uniform LightData sun;
uniform vec3 lightColor[MAX_LIGHTS];
uniform float colorMatrix[NUM_X * NUM_Y];
uniform Material material;
uniform bool blinn = true;

const float kPi = 3.14159265;
const float kShininess = 16.0;
const float kEnergyConservation = ( 8.0 + kShininess ) / ( 8.0 * kPi );

float calcSpecular(vec3 lightDir, vec3 viewDir, vec3 normal){
    if(blinn){
       vec3 halfwayDir = normalize(lightDir + viewDir);
       return kEnergyConservation * pow(max(dot(normal, halfwayDir), 0.0), kShininess);
    }
    else{
        vec3 reflectDir = reflect(-lightDir, normal);
        return pow(max(dot(viewDir, reflectDir), 0.0), material.shineDumper);
    }
}

vec3 calcDirectionalLight(LightData light, vec3 normal, vec3 viewDir){
    if(light.type == 3){
        vec3 lightDir = normalize(-light.direction);
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, normal);
//            vec3 reflectDir = reflect(-lightDir, normal);
//            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineDumper);
        float spec = calcSpecular(lightDir, viewDir, normal);
        vec3 diffuse  = light.diffuseColor  * diff * material.diffuseColor;
        vec3 specular = light.specularColor * spec * material.reflectivity * material.specularColor;
        return diffuse + specular;
    }
    return vec3(0);
}

vec3 calcLigh(LightData light, vec3 normal, vec3 viewDir, vec3 lightDir){
    if(light.type == 1){//Point Light
        float distance    = length(lightDir);
        vec3 lightDir = normalize(lightDir);
        float diff = max(dot(normal, lightDir), 0.0);
        float spec = calcSpecular(lightDir, viewDir, normal);

        float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));

        vec3 diffuse  = light.diffuseColor  * diff * material.diffuseColor;
        vec3 specular = light.specularColor * spec * material.reflectivity * material.specularColor;
        diffuse  *= attenuation;
        specular *= attenuation;
        return diffuse + specular;
    }
    else if(light.type == 2){
        float theta = dot(normalize(lightDir), normalize(-light.direction));
        if(theta > light.outerCutOff){
            float epsilon   = light.cutOff - light.outerCutOff;
            float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
            float distance    = length(lightDir);
            vec3 lightDir = normalize(lightDir);
            float diff = max(dot(normal, lightDir), 0.0);
            float spec = calcSpecular(lightDir, viewDir, normal);

            float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));

            vec3 diffuse  = light.diffuseColor  * diff * material.diffuseColor;
            vec3 specular = light.specularColor * spec * material.reflectivity * material.specularColor;
            diffuse  *= attenuation * intensity;
            specular *= attenuation * intensity;
            return diffuse + specular;
        }
    }
    else if(light.type == 3){
        return calcDirectionalLight(light, normal, viewDir);
    }
    return vec3(0);
}
void main(){
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDifuse = vec3(0);
    vec3 unitVectorToCamera = normalize(toCameraVector);

    for(int i=0 ; i<MAX_LIGHTS ; i++){
        totalDifuse += calcLigh(lightData[i], unitNormal, unitVectorToCamera, toLightVector[i]);
    }

    totalDifuse += calcDirectionalLight(sun, unitNormal, unitVectorToCamera);

    totalDifuse *= colorMatrix[int(pass_Texture.x / offsetX) * NUM_X + int(pass_Texture.y / offsetY)];
    totalDifuse = max(totalDifuse, 0.1);
    vec3 result = material.ambientColor + totalDifuse;

    out_color = vec4(result, 1.0f);

}

void main2() {
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDifuse = material.ambientColor;
    vec3 totalSpecular = vec3(0);




    vec3 unitVectorToCamera = normalize(toCameraVector);
    for(int i=0 ; i<MAX_LIGHTS ; i++){
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = nDot1;
        totalDifuse += brightness * lightColor[i];

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
        float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
        specularFactor = max(specularFactor, 0.0f);
        float dampedFactor = pow(specularFactor, material.shineDumper);
        totalSpecular += (dampedFactor * material.reflectivity * material.specularColor);
    }
//    PointLight light;
//    light.diffuseColor = vec3(1, 1, 1);
//    light.specularColor = vec3(1);
//    light.attenuation = vec3(1, 0, 0);
//    light.position = vec3(0, 1000, 0);
//    totalDifuse = calcPointLight(light, unitNormal, vec3(0, 1, 0), unitVectorToCamera);

    totalDifuse = max(totalDifuse, 0.1);
    out_color = vec4(totalDifuse, 1.0) * vec4(material.diffuseColor, 1.0) + vec4(totalSpecular, 1.0);

    out_color.xyz *= colorMatrix[int(pass_Texture.x / offsetX) * NUM_X + int(pass_Texture.y / offsetY)];

//    float limit = 0.01;
//    if(pass_Texture.x < limit || pass_Texture.y < limit || pass_Texture.x > 1 - limit || pass_Texture.y > 1 - limit){
//        out_color = vec4(0, 0, 0, 1);
//    }
}
