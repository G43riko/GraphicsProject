#version 330

in vec3 Position;
out vec3 textureCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main(void){
    mat4 view = viewMatrix;
    view[3][0] = 0;
    view[3][1] = 0;
    view[3][2] = 0;
    gl_Position = projectionMatrix * view * vec4(Position, 1.0);
    textureCoords = Position;
}