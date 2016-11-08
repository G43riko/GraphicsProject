#version 330
in vec3 Position;


uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;

void main() {
  vec4 worldPosition = transformationMatrix * vec4(Position, 1.0);
  gl_Position = projectionMatrix * viewMatrix * worldPosition;
}
