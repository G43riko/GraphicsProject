#version 140

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D colourTexture;

void main(void){
	out_Color = texture(colourTexture, textureCoords);
	float contrast = 0.7;
    out_Color.rgb = (out_Color.rgb - 0.5) * (1.0 + contrast) + 0.5;
    /*
	//bright filter
	float brightness = out_Colour.r * 0.2126 + out_Colour.g * 0.7152 + out_Colour.b + 0.0722;
	out_Colour *= brightness;
    */

	//out_Colour = vec4(1, 0, 1, 1);
}