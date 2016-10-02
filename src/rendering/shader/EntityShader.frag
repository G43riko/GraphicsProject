#version 330
in vec2 pass_Texture;

out vec4 FragmentColor;

uniform sampler2D textureSampler;

void main() {
  //FragmentColor = vec4(vec3(0.0f, 1.0f, 1.0f), 1.0f);
  FragmentColor = texture(textureSampler, pass_Texture);
}