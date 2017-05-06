//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_GTYPES_H
#define GAMEENGINE_GTYPES_H

#include <vector>
#include <string>
#include <memory>
#include <map>

class DirectionalLight;
class MaterialedModel;
class ParticleTexture;
class CubeTexture;
class PointLight;
class Texture2D;
class SpotLight;
class Vector2f;
class Vector3f;
class Material;
class RawModel;
class Particle;
class Entity;
class Vertex;
class Mesh;

typedef std::shared_ptr<DirectionalLight> PointerDirectionalLight;
typedef std::shared_ptr<MaterialedModel> PointerMaterialedModel;
typedef std::shared_ptr<ParticleTexture> PointerParticleTexture;
typedef std::shared_ptr<CubeTexture> PointerCubeTexture;
typedef std::shared_ptr<PointLight> PointerPointLight;
typedef std::shared_ptr<Texture2D> PointerTexture2D;
typedef std::shared_ptr<SpotLight> PointerSpotLight;
typedef std::shared_ptr<RawModel> PointerRawModel;
typedef std::shared_ptr<Material> PointerMaterial;
typedef std::shared_ptr<Entity> PointerEntity;
typedef std::shared_ptr<Vertex> PointerVertex;
typedef std::shared_ptr<Mesh> PointerMesh;

typedef std::map<PointerParticleTexture, std::vector<Particle>> ParticlesList;
typedef std::map<PointerMaterialedModel, std::vector<PointerEntity>> EntitiesList;

typedef std::vector<float> VectorF;
typedef std::vector<Vector3f> VectorV2;
typedef std::vector<Vector2f> VectorV3;
typedef std::vector<int> VectorI;
typedef std::vector<unsigned int> VectorUI;
typedef std::vector<unsigned char> VectorUC;
typedef std::vector<std::string> VectorS;

typedef struct objectType{
    std::string title;
    PointerMesh mesh;
    objectType(std::string title, PointerMesh mesh) : title(title), mesh(mesh){};
} ObjectType;

typedef std::map<std::string, ObjectType*> SSMap;


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
    unsigned int width;
    unsigned int height;
    std::string title;
} CubeImageData;

#endif //GAMEENGINE_GTYPES_H
