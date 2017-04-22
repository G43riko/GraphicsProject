#version 330

out vec4 out_color;

uniform vec4 color;

void main() {
    out_color = color;
    out_color.w = 0.2;
//    float limit = 0.001;
//    if(gl_PointCoord.x < limit || gl_PointCoord.y < limit){
//        out_color = vec4(0, 0, 0, 1);
//    }
}