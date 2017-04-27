#version 330
in vec3 Position;
in vec2 Texture;
in vec3 Normal;

out vec2 pass_Texture;
out vec3 surfaceNormal;
out vec3 reflectedVector;
out vec3 refractedVector;
out vec4 shadowCoords;
out vec3 toLightVector[8];

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 cameraPosition;
uniform mat4 toShadowSpace;

uniform vec3 lightPosition[8];

uniform vec4 plane;

void main() {
    pass_Texture = Texture;
    vec4 worldPosition = transformationMatrix * vec4(Position, 1.0);
    shadowCoords = toShadowSpace * worldPosition;
    gl_ClipDistance[0] = dot(worldPosition, plane);

    gl_Position = projectionMatrix * viewMatrix * worldPosition;

    surfaceNormal = (transformationMatrix * vec4(Normal, 0.0)).xyz;
    for(int i=0 ; i<8 ; i++){
        toLightVector[i] = lightPosition[i] - worldPosition.xyz;
    }
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 viewVector = normalize(worldPosition.xyz - cameraPosition);
    reflectedVector = reflect(viewVector, unitNormal);
    refractedVector = refract(viewVector, unitNormal, 1.0/1.33);

}
