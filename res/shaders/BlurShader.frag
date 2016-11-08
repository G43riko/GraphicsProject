#version 330
in vec2 blurTextureCoords[11];

out vec4 FragmentColor;

uniform sampler2D originalTexture;

void main() {
    FragmentColor = vec4(0);
    FragmentColor += texture(originalTexture, blurTextureCoords[0]) * 0.0093;
    FragmentColor += texture(originalTexture, blurTextureCoords[1]) * 0.028002;
    FragmentColor += texture(originalTexture, blurTextureCoords[2]) * 0.065984;
    FragmentColor += texture(originalTexture, blurTextureCoords[3]) * 0.121703;
    FragmentColor += texture(originalTexture, blurTextureCoords[4]) * 0.175713;
    FragmentColor += texture(originalTexture, blurTextureCoords[5]) * 0.198596;
    FragmentColor += texture(originalTexture, blurTextureCoords[6]) * 0.175713;
    FragmentColor += texture(originalTexture, blurTextureCoords[7]) * 0.121703;
    FragmentColor += texture(originalTexture, blurTextureCoords[8]) * 0.065984;
    FragmentColor += texture(originalTexture, blurTextureCoords[9]) * 0.028002;
    FragmentColor += texture(originalTexture, blurTextureCoords[10]) * 0.0093;
}

