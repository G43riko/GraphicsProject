//
// Created by gabriel on 22.1.2017.
//

#ifndef GRAPHICSPROJECT_TEXTUREMANAGER_H
#define GRAPHICSPROJECT_TEXTUREMANAGER_H

#include <GL/glew.h>
#include <src/utils/resources/FileLoader.h>
#include <src/components/particles/ParticleTexture.h>


class TextureManager{
private:
    std::map<std::string, PointerTexture2D>          loadedTextures2D;
    std::map<std::string, PointerCubeTexture>        loadedCubeTextures;
    std::map<std::string, PointerParticleTexture>    loadedParticleTextures;
public:
    static TextureManager instance;

    inline PointerTexture2D createTexture2D(const std::string& fileName){
        if(loadedTextures2D.find(fileName) == loadedTextures2D.end()){
            loadedTextures2D[fileName] = initTexture2D(ContentLoader::loadTexturePNG(fileName));
        }
        return loadedTextures2D[fileName];
    };
    inline void removeTexture(const Vector3f& color){
        //TODO dorobiť vymazávanie textúr
        //TODO musí tu byť aj počítadlo či sa naozaj má odstrániť alebo sa ešte niekde používa
    }

    inline PointerTexture2D createTexture2D(const Vector3f& color){
        std::string fileName = color.toString();
        if(loadedTextures2D.find(fileName) == loadedTextures2D.end()){
            loadedTextures2D[fileName] = initTexture2D(ContentLoader::loadTextureColor(color));
        }
        return loadedTextures2D[fileName];
    };
    inline PointerCubeTexture createCubeTexture(const std::string& fileName){
        if(loadedCubeTextures.find(fileName) == loadedCubeTextures.end()){
            loadedCubeTextures[fileName] = initCubeTexture(ContentLoader::loadCubeTexture(fileName));
        }
        return loadedCubeTextures[fileName];
    };
    inline PointerParticleTexture createParticleTexture(const std::string& fileName, const int rows, const int columns){
        if(loadedParticleTextures.find(fileName) == loadedParticleTextures.end()){
            loadedParticleTextures[fileName] = PointerParticleTexture(new ParticleTexture(createTexture2D(fileName), rows, columns));
        }
        return loadedParticleTextures[fileName];
    };

    inline void cleanUp(void){
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
    inline PointerTexture2D initTexture2D(const CubeImageData& data){
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);



        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        //TODO ako zistiť či ide o GL_RGBA alebo GL_RGB??
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data.data());

        //ANISOTROPIC
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

        //MIPMAING
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);

        return Texture2D::create(data.title, texture_id, data.width, data.height);
    };

    inline PointerCubeTexture initCubeTexture(CubeImageData * datas){
        VectorS TITLES = {"Right", "Left", "Top", "Bottom", "Back", "Front"};
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

        for(unsigned int i=0 ; i<6 ; i++){
            unsigned int width;
            unsigned int height;
            VectorUC image;
            lodepng::decode(image, width, height, SKIES_FOLDER + datas[0].title + TITLES[i] + TEXTURES_EXTENSION);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        PointerCubeTexture result = CubeTexture::create(datas[0].title, texture_id);
        delete[] datas;
        return result;
    };
};

#endif //GRAPHICSPROJECT_TEXTUREMANAGER_H
