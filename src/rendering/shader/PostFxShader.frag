#version 130

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D guiTexture;
uniform vec2 mouseMove;

uniform int useCameraBlur;
uniform int useAntiAliasing;
uniform int typeOfView;

void main(void){
	out_Color = texture(guiTexture,textureCoords);

	//antialiasing
	if(useAntiAliasing > 0.5){

	}


	//greyScale
	if(typeOfView == 1){
		float average =  (out_Color.x + out_Color.y + out_Color.z ) / 3;
		out_Color = vec4(average, average, average, 1);
	}

	//invert
	if(typeOfView == 2){
		out_Color = vec4(1 - out_Color.xyz, 1);
	}

	if(typeOfView == 6){
		float levels = 30.0;
		vec4 tmp = floor(out_Color * levels);
		out_Color = tmp / levels;
	}

	//draw
	if(0 > 0.5){
		float value = 8;
		out_Color = round(out_Color * value) / value;;
	}

	//min and max
	if(0 > 0.5){
		vec3 min = vec3(0,0,0);
		vec3 max = vec3(1,1,1);

		float r = mix(min.x, max.x, out_Color.x);
		float g = mix(min.y, max.y, out_Color.y);
		float b = mix(min.z, max.z, out_Color.z);
		out_Color = vec4(r, g, b, 1);
	}

	//ambient occlusion
	if(0 > 0.5){
		float offset = 0.001;
		vec3 normal = out_Color.xyz;
		vec3 invert = 1 - texture(guiTexture,textureCoords+vec2(offset, offset)).xyz;
		vec3 result = 1 - (normal + invert);
		float edge = 1;
		if(result.x > edge || result.y > edge || result.z > edge)
			out_Color -= vec4(1, 1, 1, 0);
	}

	if(0 > 0.5){
	    float contrast = 0.3f;
	    out_Color.rgb = (out_Color.rgb - 0.5) * (1.0 + contrast) + 0.5;
	}

}