#version 150

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D guiTexture;

//uniform vec2 mouseMove;
//uniform int useCameraBlur;
//uniform int useAntiAliasing;
//uniform int typeOfView;

uniform int greyscale;
uniform int invert;
uniform float contrast;
uniform int levels;

struct vec5 {
    float a[5];
};

struct mat5 {
    vec5 a[5];
};

float center = 2;
float factor = 0.25;
float bias = 0;
float offset = 0.005;
vec4 sum = vec4(0);

void main(void){
	out_Color = texture(guiTexture,textureCoords);

	if(greyscale == 1){
		float average =  (out_Color.x + out_Color.y + out_Color.z ) / 3;
		out_Color = vec4(average, average, average, 1);
	}

	if(invert == 1){
		out_Color = vec4(1 - out_Color.xyz, out_Color.w);
	}

    /*
	if(levels > 0){
		vec4 tmp = floor(out_Color * levels);
		out_Color = tmp / levels;
	}
	*/

	if(contrast > 0){
	    out_Color.rgb = (out_Color.rgb - 0.5) * (1.0 + contrast) + 0.5;
	}

    /*
	mat5 matrix = mat5(vec5[5](vec5(float[5](0.1,  0.1,  0.1,  0.1,  0.1)),
                               vec5(float[5](0.1,  0.4,  0.4,  0.4,  0.1)),
                               vec5(float[5](0.1,  0.4,  0.8,  0.4,  0.1)),
                               vec5(float[5](0.1,  0.4,  0.4,  0.4,  0.1)),
                               vec5(float[5](0.1,  0.1,  0.1,  0.1,  0.1))));

    for(int i=0 ; i<5 ; i++){
        for(int j=0 ; j<5 ; j++){
            vec4 color = texture(guiTexture, textureCoords + (vec2(i, j) - center) * offset);
            sum += vec4(factor * color.xyz * matrix.a[i].a[j] + bias, color.w);
        }
    }
    out_Color = sum ;
    */
}