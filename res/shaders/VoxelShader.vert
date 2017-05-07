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

const int MAX_LIGHTS = 8;

in vec3 Position;
in vec2 Texture;
in vec3 Normal;

out vec3 toLightVector[MAX_LIGHTS];
out vec3 surfaceNormal;
out vec2 pass_Texture;
out vec3 toCameraVector;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 transformationMatrix;
uniform vec3 cameraPosition;

uniform LightData lightData[MAX_LIGHTS];

uniform vec3 lightPosition[MAX_LIGHTS];

void main() {
    pass_Texture = Texture;
    vec4 worldPosition = transformationMatrix * vec4(Position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    surfaceNormal = (transformationMatrix * vec4(Normal, 0.0)).xyz;
    for(int i=0 ; i<MAX_LIGHTS ; i++){
        toLightVector[i] = lightData[i].position - worldPosition.xyz;
    }

    toCameraVector = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}