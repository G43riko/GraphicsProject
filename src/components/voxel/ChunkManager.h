//
// Created by gabriel on 7.5.2017.
//

#ifndef GAMEENGINE_CHUNKMANAGER_H
#define GAMEENGINE_CHUNKMANAGER_H

#include "AbstractChunk.h"
#include <functional>
#include <map>
#include <string>

typedef struct chunkArea{
    int size;
    AbstractChunk ** chunksAround;
    chunkArea(int size){
        chunksAround = new AbstractChunk* [(int)pow((size * 2) + 1, 2)];
    }
    ~chunkArea(void){
        delete[] chunksAround;
    }
} ChunkArea;

#define CHUNK_LINE_DIVIDER ";"


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
class ChunkStorage{
    std::map<unsigned long, unsigned long> keys;
    std::vector<AbstractChunk *> chunks;
    std::hash<std::string> hasher;
public:
    void setChunk(std::string key, AbstractChunk * chunk){
        unsigned long hash = hasher(key);
        if(hasChunk(key)){
            chunks[keys[hash]] = chunk;
        }
        else{
            chunks.push_back(chunk);
            keys[hash] = chunks.size() - 1;
        }
    }
    AbstractChunk * getChunk(std::string key){
        unsigned long hash = hasher(key);
        if(hasChunk(key)){
            return chunks[keys[hash]];
        }
        return nullptr;
    }

    bool hasChunk(std::string key){
        unsigned long hash = hasher(key);
        if(keys.empty()){
            return false;
        }
       return MAP_CONTAINS_KEY(keys, hash);
    }
    void cleanUp(void){
        for(auto chunk : chunks){
            delete chunk;
        }
        chunks.clear();
        keys.clear();
    }
};

#define CHUNKS_ADDRESS_FILENAME "src/voxel/chunkAdress.data"
typedef std::map<std::string, AbstractChunk*> MapSA;

class ChunkManager{
    ChunkFileManager * manager = ChunkFileManager::create(CHUNKS_ADDRESS_FILENAME);
    int renderDistance = 1;
    AbstractChunk * activeChunk;
    ChunkArea aroundChunks;
    ChunkStorage chunks;

    inline ChunkArea setChunksByPos(float x, float z){
        activeChunk = getChunkByPos(x, z);
        return getChunksAround(*activeChunk, renderDistance);
    }
public:
    inline ~ChunkManager(){
        delete manager;
        chunks.cleanUp();
    }
    inline void storeChunk(AbstractChunk * chunk){
        if(IS_NULL(chunk)){
            throw "ide sa uložíť nulový chunk";
        }


    };

    inline ChunkManager(float x, float z, int dist = 1) : renderDistance(dist), aroundChunks(setChunksByPos(x, z)){

    }
//    inline static AbstractChunk loadChunk(void){};

    /**
     * Vráti true ak sa panačik pohol z chunku ináč vráti false
     *
     * @param x
     * @param z
     * @return
     */
    inline bool checkAndSetActualChunksByPos(float x, float z){
        if(activeChunk -> isPosInside(x, z)){
            return false;
        }
        aroundChunks = setChunksByPos(x, z);
        return true;
    }


    inline ChunkArea getChunksAround(AbstractChunk chunk, int size = 1) {
        ChunkArea result(size);
        int counter = 0;
        for(int i=-size ; i<=size ; i++){
            for(int j=-size ; j<=size ; j++){
                printf("do blokov okolo sa pridava blok %d %d\n", chunk.getPosX() + i, chunk.getPosZ() + j);
                result.chunksAround[counter++] = getChunk(chunk.getPosX() + i, chunk.getPosZ() + j);
            }
        }
        return result;
    };
    inline bool isChunkInMemory(std::string key){
        return chunks.hasChunk(key);
    };

    inline AbstractChunk * getChunk(int x, int z) {
        //TODO if not exisist generate or load
        std::string key = std::to_string(x) + "_" + std::to_string(z);
        if(isChunkInMemory(key)){  //či je naloadovany
            return chunks.getChunk(key);
        }
        AbstractChunk * newChunk = nullptr;
        if(manager->isGeneratedChunk(key)){ //či je vygenerovany a uložený v textáku
            newChunk =  manager -> loadChunk(key);
            printf("načítava sa chunk %d_%d\n", x, z);
        }
        else{
            newChunk = new AbstractChunk(x, z);
            printf("generuje sa chunk %d_%d\n", x, z);
        }
        chunks.setChunk(key, newChunk);
        return newChunk;
    }

    inline AbstractChunk * getChunkByPos(float x, float z) {
        int act_x = (int)(x / CHUNK_SIZE);
        int act_z = (int)(z / CHUNK_SIZE);
        printf("z pozicie %f %f sa dostal blok %d %d\n", x, z, act_x, act_z);
        return getChunk(act_x, act_z);
    }
};

#endif //GAMEENGINE_CHUNKMANAGER_H
