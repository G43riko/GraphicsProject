#version 330

in vec2 position;

out vec2 textureCoords;
out vec3 toCameraVector;
out vec4 clipSpace;
out vec3 fromLightVector[8];

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightPosition[8];

const float tiling = 6;

void main(void) {
    vec4 worldPosition = modelMatrix * vec4(position.x, 0.0, position.y, 1.0);
	clipSpace = projectionMatrix * viewMatrix * worldPosition;
	gl_Position = clipSpace;
	textureCoords = vec2(position.x/2.0 + 0.5, position.y/2.0 + 0.5) * tiling;
	toCameraVector = cameraPosition - worldPosition.xyz;

    for(int i=0 ; i<8 ; i++){
        fromLightVector[i] = worldPosition.xyz - lightPosition[i];
    }

}