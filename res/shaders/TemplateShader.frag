struct Material {
    sampler2D diffuse;
    float reflectivity;
    float shineDumper;
};
struct DirLight {
    vec3 direction;
    vec3 diffuseColor;
    vec3 specularColor;
};
struct PointLight {
    vec3 position;
    vec3 attenuation;
    vec3 diffuseColor;
    vec3 specularColor;
};
struct SpotLight {
    vec3 position;
    vec3  direction;
    float cutOff;
    float outerCutOff;
    vec3 attenuation;
    vec3 diffuseColor;
    vec3 specularColor;
};
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, Material material){
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineDumper);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // Combine results
    vec3 diffuse = light.diffuseColor * diff;
    vec3 specular = light.specularColor * spec * material.reflectivity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return ambient + diffuse + specular;
}
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, Material material){
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineDumper);
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));
    // Combine results
    vec3 diffuse  = light.diffuseColor  * diff;
    vec3 specular = light.specularColor * spec * material.reflectivity;
    diffuse  *= attenuation;
    specular *= attenuation;
    return diffuse + specular;
}
vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir, Material material){
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineDumper);
    // Combine results
    vec3 diffuse  = light.diffuseColor  * diff;
    vec3 specular = light.specularColor * spec * material.reflectivity;
    return diffuse + specular;
}