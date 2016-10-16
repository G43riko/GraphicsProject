#version 140

in vec2 textureCoords;

out vec4 out_Colour;

uniform sampler2D colourTexture;

void main(void){
	//out_Colour = texture(colourTexture, textureCoords);
	out_Colour = vec4(1, 0, 1, 1);
}