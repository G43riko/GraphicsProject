#version 140

in vec2 position;

out vec2 textCoords1;
out vec2 textCoords2;
out float blend;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;


uniform vec4 textOffsets;
//uniform vec2 textOffset1;
//uniform vec2 textOffset2;
//uniform vec2 textCoordInfo;

uniform float blendFactor;
uniform float numberOfRows;
void main(void){
    vec2 textCoords = position + vec2(0.5, 0.5);
    textCoords.y = 1.0 - textCoords.y;

    textCoords /= numberOfRows;
//    textCoords1 = textCoords + textOffset1;
//    textCoords2 = textCoords + textOffset2;
    textCoords1 = textCoords + textOffsets.xy;
    textCoords2 = textCoords + textOffsets.zw;
    blend = blendFactor;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 0.0, 1.0);
}