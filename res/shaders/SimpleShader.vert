#version 150

in vec2 Position;

out vec2 textureCoords;

void main(void){

	gl_Position = vec4(Position, 0.0, 1.0);
	textureCoords = Position * 0.5 + 0.5;

}