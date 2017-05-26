//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_GTYPES_H
#define GAMEENGINE_GTYPES_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "GConst.h"

class DirectionalLight;
class MaterialedModel;
class ParticleTexture;
class CubeTexture;
class BasicShader;
class GameObject;
class PointLight;
class Texture2D;
class SpotLight;
class Vector2f;
class Vector3f;
class Material;
class RawModel;
class Particle;
class Camera;
class Entity;
class Vertex;
class Mesh;

typedef std::shared_ptr<DirectionalLight> PointerDirectionalLight;
typedef std::shared_ptr<MaterialedModel> PointerMaterialedModel;
typedef std::shared_ptr<ParticleTexture> PointerParticleTexture;
typedef std::shared_ptr<CubeTexture> PointerCubeTexture;
typedef std::shared_ptr<BasicShader> PointerBasicShader;
typedef std::shared_ptr<PointLight> PointerPointLight;
typedef std::shared_ptr<GameObject> PointerGameObject;
typedef std::shared_ptr<Texture2D> PointerTexture2D;
typedef std::shared_ptr<SpotLight> PointerSpotLight;
typedef std::shared_ptr<RawModel> PointerRawModel;
typedef std::shared_ptr<Material> PointerMaterial;
typedef std::shared_ptr<Entity> PointerEntity;
typedef std::shared_ptr<Vertex> PointerVertex;
typedef std::shared_ptr<Camera> PointerCamera;
typedef std::shared_ptr<Mesh> PointerMesh;

typedef std::map<PointerParticleTexture, std::vector<Particle>> ParticlesList;
typedef std::map<PointerMaterialedModel, std::vector<PointerEntity>> EntitiesList;

typedef std::vector<int> VectorI;
typedef std::vector<float> VectorF;
typedef std::vector<Vector3f> VectorV3;
typedef std::vector<Vector2f> VectorV2;
typedef std::vector<std::string> VectorS;
typedef std::vector<uint> VectorUI;
typedef std::vector<u_char> VectorUC;

typedef struct objectType{
    std::string title;
    PointerMesh mesh;
    objectType(std::string title, PointerMesh mesh) : title(title), mesh(mesh){};
} ObjectType;

typedef std::map<std::string, ObjectType*> SOMap;
typedef std::map<std::string, std::string> SSMap;

enum Directions{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACK
};

typedef struct renderOptions{
    bool deferred   = false;
    bool blinn      = true;
    bool grey       = false;
    bool inverse    = false;
    bool normals    = false;
    bool parallax   = false;
    bool ssao       = false;
    float fixGamma  = 0;
    float hdri      = 0;

} RenderOptions;

typedef struct vec3{
    float x;
    float y;
    float z;
} Vec3;

enum LightTypes{
    POINT = 1,
    SPOT = 2,
    DIRECTIONAL = 3
};

typedef struct materialData{
    Vec3 diffuseColor;
    Vec3 ambientColor;
    Vec3 specularColor;
    float reflectivity;
    float shineDumper;
} MaterialData;

typedef struct lightData{
    LightTypes type;
    Vec3 position;
    Vec3 diffuseColor;
    Vec3 specularColor;
    Vec3 attenuation;
    Vec3 direction;
    float cutOff;
    float outerCutOff;
} LightData;

typedef struct masterOptions{
    bool useShadows;
    bool useGuis;
    bool useSkybox;
    bool useParticles;
    bool useEntities;
    bool useWaters;
    bool useVoxels;
    bool usePostFx;
    bool useTextures;
    bool useNormals;
    bool useLights;
    bool useSpeculars;
    bool useEnviromentals;
}MasterOptions;

typedef struct cubeImagedata{
    VectorUC data;
    uint width;
    uint height;
    std::string title;
} CubeImageData;

#endif //GAMEENGINE_GTYPES_H
