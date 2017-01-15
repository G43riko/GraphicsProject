#version 140

in vec2 textCoords1;
in vec2 textCoords2;
in float blend;

out vec4 out_colour;

uniform sampler2D particleTexture;

void main(void){

	vec4 color1 = texture(particleTexture, textCoords1);
	vec4 color2 = texture(particleTexture, textCoords2);
	out_colour = mix(color1, color2, blend);

}