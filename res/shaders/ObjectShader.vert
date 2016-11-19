#version 330
in vec3 Position;
in vec2 Texture;
in vec3 Normal;
in vec3 Tangent;

out vec2 pass_Texture;
out vec3 toLightVector[8];
out vec3 toCameraVector;
out float visibility;
out float distance;

const float density = 0.007f;
const float gradient = 1.5f;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPositionEyeSpace[8];

void main() {
    pass_Texture = Texture;
    vec4 worldPosition = transformationMatrix * vec4(Position, 1.0);
    mat4 modelViewMatrix = viewMatrix * transformationMatrix;
    vec4 positionRelativeToCam = modelViewMatrix * vec4(Position, 1.0);
    gl_Position = projectionMatrix * positionRelativeToCam;

    vec3 surfaceNormal = (transformationMatrix * vec4(Normal, 0.0)).xyz;

    vec3 norm = normalize(surfaceNormal);
    vec3 tang = normalize((modelViewMatrix * vec4(Tangent, 0.0)).xyz);
    vec3 bitang = normalize(cross(norm, tang));

    mat3 toTangentSpace = mat3(
        tang.x, bitang.x, norm.x,
        tang.y, bitang.y, norm.y,
        tang.z, bitang.z, norm.z
    );

    for(int i=0 ; i<8 ; i++)
        toLightVector[i] = toTangentSpace * (lightPositionEyeSpace[i] - positionRelativeToCam.xyz);
        //toLightVector[i] = lightPositionEyeSpace[i] - worldPosition.xyz;


    distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow(distance * density, gradient));
    visibility = clamp(visibility, 0, 1);

    toCameraVector = toTangentSpace * (-positionRelativeToCam.xyz);
}
