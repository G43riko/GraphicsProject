#version 330
in vec3 Position;
in vec2 Texture;

out vec2 pass_Texture;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
  pass_Texture = Texture;
  gl_Position = projectionMatrix * viewMatrix * transformationMatrix *vec4(Position, 1.0);
}
