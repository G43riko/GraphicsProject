//
// Created by gabriel on 12.11.2016.
//

#ifndef GRAPHICSPROJECT_TERRAIN_H
#define GRAPHICSPROJECT_TERRAIN_H


#include <src/rendering/model/RawModel.h>
#include <src/rendering/material/Texture2D.h>
#include <src/utils/Loader.h>
#include <src/utils/Vectors.h>
#include <src/rendering/model/MaterialedModel.h>

class Terrain {
public:
    Terrain(int gridX, int gridZ, Loader loader, PointerTexture2D texture, GLuint size) :
            texture(texture),
            x(static_cast<float>(gridX * SIZE)),
            z(static_cast<float>(gridZ * SIZE)){
        PointerRawModel m = generateTerrain(loader, create(size, size), size);
        printf("raw: %ld, %d, %d\n", m.use_count(), m->getVertexCount(), m->getVaoID());
        model = createMaterialedModel(m, createMaterial(texture));
    }

    float getX() {
        return x;
    }

    float getZ() {
        return z;
    }

    PointerMaterialedModel getModel() {
        return model;
    }

private:
    static float ** mapa;
    static constexpr float MAX_HEIGHT = 100;
    static constexpr float MAX_PIXEL_COLOR = 256 * 256 * 256;
    static constexpr int SIZE = 800;
    static constexpr float VERTEX_COUNT = 128;
    PointerTexture2D texture;
    float x;
    float z;
    PointerMaterialedModel model;

    Vector3f calculateNormal(int x, int z, float ** map, int size);


    float getHeight(int x, int z, float ** map, int size);

    PointerRawModel generateTerrain(Loader loader, float ** map, GLuint size);
    static float** create(GLuint x2, GLuint y2);

    static void generateMap(int x1, int y1, int x2, int y2, float ** map);
};


#endif //GRAPHICSPROJECT_TERRAIN_H
