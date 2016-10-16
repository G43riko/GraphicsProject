#version 330
in vec2 pass_Texture;
in vec3 surfaceNormal;
in vec3 toLightVector[8];
in vec3 pass_Tangent;

out vec4 FragmentColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor[8];
uniform int levels;

void main() {
    //FragmentColor = vec4(vec3(0.0f, 1.0f, 1.0f), 1.0f);

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 totalDiffuse  = vec3(0.0f);

    for(int i=0 ; i<8 ; i++){
        vec3 unitLightVector = normalize(toLightVector[i]);

        float nDot1 = dot(unitNormal, unitLightVector);
        float brightness = max(nDot1, 0.0);
        if(levels > 0){
            float level = floor(brightness * levels);
            brightness = level / levels;
        }
        totalDiffuse += brightness * lightColor[i];
    }
    totalDiffuse = max(totalDiffuse, 0.2);

    FragmentColor = vec4(totalDiffuse, 1.0) * texture(textureSampler, pass_Texture);
    FragmentColor = vec4(pass_Tangent, 1.0);
    //FragmentColor = vec4(1,0,1, 1.0);
}