//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_LOADER_H
#define GRAPHICSPROJECT_LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../rendering/model/RawModel.h"
#include "../rendering/model/Mesh.h"
#include <vector>
#include <list>
#include <src/utils/GTypes.h>
#include <iostream>
class Loader {
private:
    struct modelData{
        GLuint vaoID;
        GLuint vboIndices;
        GLuint vboVertices;
        GLuint vboTextures;
        GLuint vboNormals;
        GLuint vboTangents;
    };
    std::list<modelData *> models;
    inline struct modelData * createAndStoreObject(void){
        struct modelData * result = new modelData();
        models.push_back(result);
        return result;
    }
public:
    inline PointerRawModel loadToVao(const VectorF positions){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        storeDataInAttributeList(0, 3, positions, &data -> vboVertices);
        unbindVAO();
        return RawModel::create(data -> vaoID, (GLuint)positions.size() / 3);
    }

    inline PointerRawModel loadToVao(const VectorF positions, const VectorUI indices){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        bindIndicesBuffer(indices, &data -> vboIndices);
        storeDataInAttributeList(0, 3, positions, &data -> vboVertices);
        unbindVAO();
        return RawModel::create(data -> vaoID, (int)indices.size());
    }

    inline PointerRawModel loadToVao(const VectorF positions,
                                     const VectorF texts,
                                     const VectorF normals,
                                     const VectorUI indices){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        bindIndicesBuffer(indices, &data -> vboIndices);
        storeDataInAttributeList(0, 3, positions, &data -> vboVertices);
        storeDataInAttributeList(1, 2, texts, &data -> vboTextures);
        storeDataInAttributeList(2, 3, normals, &data -> vboNormals);
        unbindVAO();
        return RawModel::create(data -> vaoID, (int)indices.size());
    }
    inline PointerRawModel loadToVaoA(const GLfloat * vertices,
                                      const GLfloat * textures,
                                      const GLfloat * normals,
                                      const GLuint * indices){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        bindIndicesBufferArray(indices, &data -> vboIndices);
        storeDataInAttributeArray(0, 3, vertices, &data -> vboVertices);
        storeDataInAttributeArray(1, 2, textures, &data -> vboTextures);
        storeDataInAttributeArray(2, 3, normals, &data -> vboNormals);
        unbindVAO();
        return RawModel::create(data -> vaoID, sizeof(indices) / sizeof(GLuint));
    }

    inline PointerRawModel loadToVao(const VectorF positions,
                                     const VectorF texts,
                                     const VectorUI indices){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        bindIndicesBuffer(indices, &data -> vboIndices);
        storeDataInAttributeList(0, 3, positions, &data -> vboVertices);
        storeDataInAttributeList(1, 2, texts, &data -> vboTextures);
        unbindVAO();
        return RawModel::create(data -> vaoID, (int)indices.size());
    }

    inline PointerRawModel loadToVao(const VectorF positions, const int dimensions) {
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        storeDataInAttributeList(0, dimensions, positions, &data -> vboVertices);
        unbindVAO();
        return RawModel::create(data -> vaoID, (GLuint)(positions.size() / dimensions));
    }

    inline PointerRawModel loadToVao(const PointerMesh& mesh, GLenum renderType = GL_TRIANGLES){
        struct modelData * data = createAndStoreObject();
        createVAO(&data -> vaoID);
        bindIndicesBuffer(mesh -> getIndices(), &data -> vboIndices);
        storeDataInAttributeList(0, 3,  mesh -> getVertices(), &data -> vboVertices);
        storeDataInAttributeList(1, 2,  mesh -> getUvs(), &data -> vboTextures);
        storeDataInAttributeList(2, 3,  mesh -> getNormals(), &data -> vboNormals);
        storeDataInAttributeList(3, 3,  mesh -> getTangents(), &data -> vboTangents);
        unbindVAO();
        return RawModel::create(data -> vaoID, (GLuint)mesh -> getIndices().size(), renderType);
    }

    inline void cleanUp(void){
        for(struct modelData * model : models){
            glDeleteVertexArrays(1, &model -> vaoID);
            glDeleteBuffers(1, &model -> vboIndices);
            glDeleteBuffers(1, &model -> vboVertices);
            glDeleteBuffers(1, &model -> vboTextures);
            glDeleteBuffers(1, &model -> vboNormals);
            glDeleteBuffers(1, &model -> vboTangents);
            delete model;
        }
        models.clear();
    }
private:
    inline static void createVAO(GLuint * vaoID){
        glGenVertexArrays(1, vaoID);
        glBindVertexArray(* vaoID);
    }

    inline static void bindIndicesBuffer(const VectorUI buffer, GLuint * vboID){
        glGenBuffers(1, vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), GL_STATIC_DRAW);
    }
    inline static void bindIndicesBufferArray(const GLuint * buffer, GLuint * vboID){
        glGenBuffers(1, vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    }



    inline static void storeDataInAttributeArray(const GLuint attributeNumber, const int size, const GLfloat * buffer, GLuint * vboID){
        glGenBuffers(1, vboID);
        glBindBuffer(GL_ARRAY_BUFFER, *vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    inline static void storeDataInAttributeList(const GLuint attributeNumber, const int size, const VectorF buffer, GLuint * vboID){
        glGenBuffers(1, vboID);
        glBindBuffer(GL_ARRAY_BUFFER, *vboID);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    inline static void unbindVAO(void){ glBindVertexArray(0);}

    template <typename T>
    inline static void showBufferData(int size, GLuint id, GLuint type = GL_ARRAY_BUFFER){
        T * target = new T[size * sizeof(T)];
        glBindBuffer(type, id);
        glGetBufferSubData(type, 0, size * sizeof(T), target);
        std::cout << "načítalo sa " << size << " veci: "<< std::endl;
        for(int i=0 ; i<size ; i++){
            std::cout << target[i] << " ";
        }
        std::cout << std::endl;

        delete[] target;
    }
};

/*
class Loader {
private:
public:
    inline PointerRawModel loadToVao(const VectorF positions){
        GLuint vaoID = createVAO();
        storeDataInAttributeList(0, 3, positions);
        unbindVAO();
        return createRawModel(vaoID, (GLuint)positions.size() / 3);
    }

    inline PointerRawModel loadToVao(const VectorF positions, const VectorUI indices){
        GLuint vaoID = createVAO();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(0, 3, positions);
        unbindVAO();
        return createRawModel(vaoID, (int)indices.size());
    }

    inline PointerRawModel loadToVao(const VectorF positions,
                                     const VectorF texts,
                                     const VectorF normals,
                                     const VectorUI indices){
        GLuint vaoID = createVAO();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(0, 3, positions);
        storeDataInAttributeList(1, 2, texts);
        storeDataInAttributeList(2, 3, normals);
        unbindVAO();
        return createRawModel(vaoID, (GLuint)indices.size());
    }
    inline PointerRawModel loadToVaoA(const GLfloat * vertices,
                                      const GLfloat * textures,
                                      const GLfloat * normals,
                                      const GLuint * indices){
        GLuint vaoID = createVAO();
        bindIndicesBufferArray(indices);
        storeDataInAttributeArray(0, 3, vertices);
        storeDataInAttributeArray(1, 2, textures);
        storeDataInAttributeArray(2, 3, normals);
        unbindVAO();
        return createRawModel(vaoID, sizeof(indices) / sizeof(GLuint));
    }

    inline PointerRawModel loadToVao(const VectorF positions,
                                     const VectorF texts,
                                     const VectorUI indices){
        GLuint vaoID = createVAO();
        bindIndicesBuffer(indices);
        storeDataInAttributeList(0, 3, positions);
        storeDataInAttributeList(1, 2, texts);
        unbindVAO();
        return createRawModel(vaoID, (int)indices.size());
    }

    inline PointerRawModel loadToVao(const VectorF positions, const int dimensions) {
        GLuint vaoID = createVAO();
        storeDataInAttributeList(0, dimensions, positions);
        unbindVAO();
        return createRawModel(vaoID, (GLuint)(positions.size() / dimensions));
    }

    inline PointerRawModel loadToVao(const PointerMesh mesh){
        GLuint vaoID = createVAO();
        bindIndicesBuffer(mesh -> getIndices());
        storeDataInAttributeList(0, 3, mesh -> getVertices());
        storeDataInAttributeList(1, 2, mesh -> getUvs());
        storeDataInAttributeList(2, 3, mesh -> getNormals());
        storeDataInAttributeList(3, 3, mesh -> getTangents());
        unbindVAO();
        return createRawModel(vaoID, (GLuint)mesh -> getIndices().size());
    }

    inline void cleanUp(void)const{
        for(GLuint vao : vaos){
            glDeleteVertexArrays(1, &vao);
        }
        for(GLuint vbo : vbos){
            glDeleteBuffers(1, &vbo);
        }
    }
private:
    std::list<GLuint> vaos;
    std::list<GLuint> vbos;
    inline GLuint createVAO(void){
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        vaos.push_front(vaoID);
        return vaoID;
    }

    inline void bindIndicesBuffer(const VectorUI buffer){
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), GL_STATIC_DRAW);
        vbos.push_front(vboID);
    }
    inline void bindIndicesBufferArray(const GLuint * buffer){
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
        vbos.push_front(vboID);
    }



    inline void storeDataInAttributeArray(const GLuint attributeNumber, const int size, const GLfloat * buffer){
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbos.push_front(vboID);
    }

    inline void storeDataInAttributeList(const GLuint attributeNumber, const int size, const VectorF buffer){
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        vbos.push_front(vboID);
    }
    inline void unbindVAO(void) const{ glBindVertexArray(0);}
    template <typename T> ň
    static void showBufferData(int size, GLuint id, GLuint type = GL_ARRAY_BUFFER){
        T * target = new T[size * sizeof(T)];
        glBindBuffer(type, id);
        glGetBufferSubData(type, 0, size * sizeof(T), target);
        std::cout << "načítalo sa " << size << " veci: "<< std::endl;
        for(int i=0 ; i<size ; i++)
            std::cout << target[i] << " ";
        std::cout << std::endl;
        delete[] target;
    }
};
*/

#endif //GRAPHICSPROJECT_LOADER_H
