#version 330
in vec2 Position;
//in vec2 Texture;

out vec2 pass_Texture;

uniform mat4 transformationMatrix;

void main() {
  pass_Texture =  vec2((Position.x + 1.0) / 2.0, (Position.y + 1.0) / 2.0);
  gl_Position = transformationMatrix * vec4(Position, 0.0, 1.0);

}
