//
// Created by gabriel on 7.5.2017.
//

#ifndef GAMEENGINE_CHUNKMANAGER_H
#define GAMEENGINE_CHUNKMANAGER_H

#include <src/utils/GUtils.h>
#include <math.h>
#include "AbstractChunk.h"
#include <functional>
#include <map>
#include <string>
#include <unordered_map>

#define CHUNK_LINE_DIVIDER ";"
#define CHUNKS_ADDRESS_FILENAME "src/voxel_old/chunkAdress.data"
typedef std::unordered_map<std::string, AbstractChunk*> MapSA;

typedef struct chunkArea{
    unsigned int _size;
    AbstractChunk ** chunksAround = nullptr;
    chunkArea(unsigned int size) : _size(size){
        if(size > 0){
            chunksAround = new AbstractChunk* [(int)pow((size * 2) + 1, 2)];
        }
    }
    ~chunkArea(void){
        //TODO možný memory leak
//        if(IS_NOT_NULL(chunksAround)){
//            delete chunksAround;
//        }
    }
} ChunkArea;


class ChunkFileManager{
    /*
     * subor v ktorom su uložene riadky jednotlivých chunkov
     * tento súbor sa vždy v statickej metode načíta
     * a tento objekt si pamatá riadky jednotlivých chunkov
     * ak chunk nieje uložený tak prida nový riadok a uloží to
     * na konci sa musí všetko uložiť do suboru s adresami chunkov
     *
     * chunk line format: LINE, POS_X, POS_Z,
     */
    std::string fileName;
    std::map<std::string, unsigned int> chunkLines;
    unsigned int maxLine;

    ChunkFileManager(std::string fileName) : fileName(fileName){
        printf("načitava sa obsah súboru %s\n", fileName.c_str());

        //TODO tu načíta súbor z riadkami
    };
    ChunkFileManager(const ChunkFileManager&){};
    inline void store(int line, std::string data){

        printf("uklada sa obsah súboru %s\n", fileName.c_str());

        //TODO tu sa uloží konkretny riadok do súboru;
    }
public:
//    inline bool isGeneratedChunk(int x, int z){
//
//    }
    inline AbstractChunk * loadChunk(std::string chunkPos){
        printf("nacitava sa chunk zo suboru na pozicii %s \n", chunkPos.c_str());
        return nullptr;
    }
    inline bool isGeneratedChunk(std::string chunkPos){
        return MAP_CONTAINS_KEY(chunkLines, chunkPos);
    }
    inline static ChunkFileManager * create(std::string fileName){
        static ChunkFileManager * result = nullptr;
        if(IS_NULL(result)){
            result = new ChunkFileManager(fileName);
        }
        return result;
    }

    inline void storeChunk(AbstractChunk * chunk){
        std::string chunkPosString = chunk->getPosString();
        unsigned int line;
        if(isGeneratedChunk(chunkPosString)){
            line = chunkLines[chunkPosString];

        }
        else{
            chunkLines[chunkPosString] = line = maxLine++;
        }
        std::string content = line + CHUNK_LINE_DIVIDER;
        content += chunk->getPosX() + CHUNK_LINE_DIVIDER + chunk->getPosZ();
        store(line, content);
    }
};


class ChunkManager{
    ChunkFileManager * manager = ChunkFileManager::create(CHUNKS_ADDRESS_FILENAME);
    int renderDistance = 1;
    AbstractChunk * activeChunk;
    ChunkArea aroundChunks = {0};
    std::unordered_map<std::string, AbstractChunk*> chunks;

    inline ChunkArea setChunksByPos(float x, float z){
        activeChunk = getChunkByPos(x, z);
        return getChunksAround(*activeChunk, renderDistance);
    }
public:
    inline ChunkManager(float x, float z, int dist = 1) : renderDistance(dist){
        aroundChunks = setChunksByPos(x, z);
    }
    inline ~ChunkManager(){
        delete manager;
        for(auto chunk : chunks){
            delete chunk.second;
        }
        chunks.clear();
    }
    inline void storeChunk(AbstractChunk * chunk){
        if(IS_NULL(chunk)){
            throw "ide sa uložíť nulový chunk";
        }


    };


    /**
     * Vráti true ak sa panačik pohol z chunku ináč vráti false
     *
     * @param x
     * @param z
     * @return
     */
    inline bool checkAndSetActualChunksByPos(float x, float z){
        if(activeChunk -> isPosInside(x, z)){//ak je player na aktualnom bloke tak je to v poriadku
            return false;
        }
        aroundChunks = setChunksByPos(x, z); //ináč nastavíme okolité chunky
        return true;
    }


    inline ChunkArea getChunksAround(AbstractChunk chunk, int size = 1) {
        ChunkArea result(size);
        int counter = 0;
        for(int i=-size ; i<=size ; i++){
            for(int j=-size ; j<=size ; j++){
                result.chunksAround[counter++] = getChunk(chunk.getPosX() + i, chunk.getPosZ() + j);
            }
        }
        return result;
    };
    inline bool isChunkInMemory(std::string key){
        return false; //MAP_CONTAINS_KEY(chunks, key);
    };

    inline AbstractChunk * getChunk(int x, int z) {
        std::string key = std::to_string(x) + "_" + std::to_string(z);
        if(isChunkInMemory(key)){  //či je naloadovany
            return chunks[key];
        }
        AbstractChunk * newChunk = nullptr;
        if(manager->isGeneratedChunk(key)){ //či je vygenerovany a uložený v textáku
            newChunk =  manager -> loadChunk(key);
        }
        else{
            newChunk = new AbstractChunk(x, z);
        }
        chunks[key] = newChunk;
        return newChunk;
    }

    inline AbstractChunk * getChunkByPos(float x, float z) {
        int act_x = (int)(x / CHUNK_SIZE);
        int act_z = (int)(z / CHUNK_SIZE);
        return getChunk(act_x, act_z);
    }
};

#endif //GAMEENGINE_CHUNKMANAGER_H
