#version 330
in vec3 Position;
in vec2 Texture;
in vec3 Normal;

out vec2 pass_Texture;
out vec3 surfaceNormal;
out vec3 toLightVector;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;

void main() {
  pass_Texture = Texture;
  vec4 worldPosition = transformationMatrix * vec4(Position, 1.0);
  gl_Position = projectionMatrix * viewMatrix * worldPosition;

  surfaceNormal = (transformationMatrix * vec4(Normal, 0.0)).xyz;
  toLightVector = lightPosition - worldPosition.xyz;

}
