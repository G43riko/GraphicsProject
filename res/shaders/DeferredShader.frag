#version 330
in vec2 pass_Texture;
in vec3 surfaceNormal;
in vec3 position;

out vec4 FragmentColor;
out vec4 Normal;
out vec4 Position;
out vec4 Diffuse;

uniform sampler2D textureSampler;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform vec3 samples[64];

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(){
    vec4 diffuseColor = texture(textureSampler, pass_Texture);
    vec3 unitNormal = normalize(surfaceNormal);

    Diffuse = diffuseColor;
    Normal = vec4(unitNormal, 1.0);
    Position = vec4(position, 1.0);


    vec3 lightColor = vec3(1, 0, 1);
    vec3 light = vec3(10,5,10);
    vec3 lightDir = light - position ;

    vec3 normal = normalize(Normal.xyz);
    vec3 unitLightDir = normalize(lightDir);

    vec3 eyeDir = normalize(cameraPosition - Position.xyz);
    vec3 vHalfVector = normalize(unitLightDir.xyz + eyeDir);

    float lightAttenuation = 15;


    float toLightDistance = length(lightDir);
    float lightFactor = 0;
    if(toLightDistance < lightAttenuation){
        lightFactor = (1 - toLightDistance / lightAttenuation);
    }

    lightFactor = max(lightFactor, 0.2);
//    FragmentColor = vec4(lightFactor * lightColor, 1);

    FragmentColor = max(dot(normal, unitLightDir), 0) * vec4(lightColor, 1) * Diffuse + pow(max(dot(normal, vHalfVector), 0.0), 100) * 1.5;
    FragmentColor *= lightFactor;



    /*SSAO*/
    /*
    vec3 randnum = vec3(rand(pass_Texture), rand(pass_Texture), rand(pass_Texture));

    vec3 tangent = normalize(randnum - normal * dot(randnum, normal));
    vec3 bitang = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitang, normal);

    float occlusion = 0;
    float radius = 0.5;
    float bias = 0.025;
    for(int i=0 ; i<64 ; i++){
        vec3 res = TBN * samples[i];
        res = Position.xyz + res * radius;

        vec4 offset = vec4(res, 1.0);
        offset = projectionMatrix * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;

        float sampleDepth = Position.z;

        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(0.0000001));
        occlusion += (sampleDepth >= res.z + bias ? 1.0 : 0.0) * rangeCheck;
    }

    occlusion = 1.0 - (occlusion / 64);
    FragmentColor = vec4(occlusion);
    */
}