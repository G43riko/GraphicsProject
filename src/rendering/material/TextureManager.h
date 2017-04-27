//
// Created by gabriel on 22.1.2017.
//

#ifndef GRAPHICSPROJECT_TEXTUREMANAGER_H
#define GRAPHICSPROJECT_TEXTUREMANAGER_H

#include <GL/glew.h>
#include <src/utils/FileLoader.h>
#include <src/components/particles/ParticleTexture.h>
#include "Texture2D.h"
#include "CubeTexture.h"


class TextureManager{
private:
    static std::map<std::string, PointerTexture2D>          loadedTextures2D;
    static std::map<std::string, PointerCubeTexture>        loadedCubeTextures;
    static std::map<std::string, PointerParticleTexture>    loadedParticleTextures;
public:
    static inline PointerTexture2D createTexture2D(std::string fileName){
        if(loadedTextures2D.find(fileName) == loadedTextures2D.end()){
            loadedTextures2D[fileName] = initTexture2D(ContentLoader::loadTexturePNG(fileName));
        }
        return loadedTextures2D[fileName];
    };
    static inline PointerTexture2D createTexture2D(Vector3f color){
        std::string fileName = color.toString();
        if(loadedTextures2D.find(fileName) == loadedTextures2D.end()){
            loadedTextures2D[fileName] = initTexture2D(ContentLoader::loadTextureColor(color));
        }
        return loadedTextures2D[fileName];
    };
    static inline PointerCubeTexture createCubeTexture(std::string fileName){
        if(loadedCubeTextures.find(fileName) == loadedCubeTextures.end()){
            loadedCubeTextures[fileName] = initCubeTexture(ContentLoader::loadCubeTexture(fileName));
        }
        return loadedCubeTextures[fileName];
    };
    static inline PointerParticleTexture createParticleTexture(std::string fileName, int rows, int columns){
        if(loadedParticleTextures.find(fileName) == loadedParticleTextures.end()){
            loadedParticleTextures[fileName] = PointerParticleTexture(new ParticleTexture(createTexture2D(fileName), rows, columns));
        }
        return loadedParticleTextures[fileName];
    };

    static inline void cleanUp(void){
        for (auto it = loadedTextures2D.begin(); it != loadedTextures2D.end(); ++it){
            it -> second -> cleanUp();
        }
        loadedTextures2D.clear();

        for (auto it = loadedCubeTextures.begin(); it != loadedCubeTextures.end(); ++it){
            it -> second -> cleanUp();
        }
        loadedCubeTextures.clear();

        loadedParticleTextures.clear();
    };
private:
    static inline PointerTexture2D initTexture2D(CubeImageData data){
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //TODO ako zistiť či ide o GL_RGBA alebo GL_RGB??
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data.data());

        //ANISOTROPIC
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

        //MIPMAING
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);

        return PointerTexture2D(new Texture2D(data.title, texture_id, data.width, data.height));
    };

    static inline PointerCubeTexture initCubeTexture(CubeImageData * datas){
        std::vector<std::string> TITLES = {"Right", "Left", "Top", "Bottom", "Back", "Front"};
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

        for(unsigned int i=0 ; i<6 ; i++){
            unsigned int width;
            unsigned int height;
            std::vector<unsigned char> image;
            lodepng::decode(image, width, height, "res/textures/skies/" + datas[0].title + TITLES[i] + ".png");
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        PointerCubeTexture result = PointerCubeTexture(new CubeTexture(datas[0].title, texture_id));
        delete[] datas;
        return result;
    };
};

#endif //GRAPHICSPROJECT_TEXTUREMANAGER_H
