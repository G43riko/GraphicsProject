#version 330

in vec3 toLightVector[8];
in vec3 surfaceNormal;
in vec2 pass_Texture;
in vec3 toCameraVector;

out vec4 out_color;

const int NUM_X = 8;
const int NUM_Y = 8;
const float offsetX = 1.0f / NUM_X;
const float offsetY = 1.0f / NUM_Y;
const float shineDumper = 100.0f;
const float reflectivity = 0.8f;

uniform vec4 color;
uniform vec3 lightColor[8];
uniform float colorMatrix[NUM_X * NUM_Y];

void main() {
    out_color = color;
    return;
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDifuse = vec3(0);
    vec3 totalSpecular = vec3(0);


    vec3 unitVectorToCamera = normalize(toCameraVector);

    for(int i=0 ; i<8 ; i++){
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = nDot1;
        totalDifuse += brightness * lightColor[i];

        vec3 lightDirection = -unitLightVector;
        vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
        float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
        specularFactor = max(specularFactor, 0.0f);
        float dampedFactor = pow(specularFactor, shineDumper);
        totalSpecular += (dampedFactor * reflectivity * lightColor[i]);
    }
    totalDifuse = max(totalDifuse, 0.1);

    out_color = vec4(totalDifuse, 1.0) * color + vec4(totalSpecular, 1.0);

    out_color.xyz *= colorMatrix[int(pass_Texture.x / offsetX) * NUM_X + int(pass_Texture.y / offsetY)];

    /*
    float limit = 0.01;
    if(pass_Texture.x < limit || pass_Texture.y < limit || pass_Texture.x > 1 - limit || pass_Texture.y > 1 - limit){
        out_color = vec4(0, 0, 0, 1);
    }
    */
}