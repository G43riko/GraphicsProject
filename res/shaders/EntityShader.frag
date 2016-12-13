#version 330
in vec2 pass_Texture;
in vec3 surfaceNormal;
in vec3 toLightVector[8];

out vec4 FragmentColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor[8];
uniform int levels;

void main() {
    //FragmentColor = vec4(vec3(0.0f, 1.0f, 1.0f), 1.0f);

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDifuse = vec3(0);
    for(int i=0 ; i<8 ; i++){
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.1);
        if(levels > 0){
            float level = floor(brightness * levels);
            brightness = level / levels;
        }
        totalDifuse += brightness * lightColor[i];
    }

    FragmentColor = vec4(totalDifuse, 1.0) * texture(textureSampler, pass_Texture);
}