#version 330
in vec2 pass_Texture;
in vec3 surfaceNormal;
in vec3 toLightVector;

out vec4 FragmentColor;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform int levels;

void main() {
    //FragmentColor = vec4(vec3(0.0f, 1.0f, 1.0f), 1.0f);

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.1);
    if(levels > 0){
        float level = floor(brightness * levels);
        brightness = level / levels;
    }

    vec3 diffuse = brightness * lightColor;
    FragmentColor = vec4(diffuse, 1.0) * texture(textureSampler, pass_Texture);
}