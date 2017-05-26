//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_TEXTMASTER_H
#define GAMEENGINE_TEXTMASTER_H

#include <src/rendering/shader/TextShader.h>
#include <src/rendering/RenderUtil.h>
#include "TextManager.h"

class TextMaster {
    BasicShader *shader = new TextShader();
    TextManager manager;
    std::vector<TextLine> texts;
    TextLine text = TextLine("gabriel", 20, 20);
public:
    inline TextMaster(const PointerCamera camera){
        RenderUtil::updateProjectionMatrix(*shader, camera);
    };
    inline void renderTexts(){
        manager.RenderText(*shader, text);
        ITERATE_VECTOR(texts, i){
            manager.RenderText(*shader, texts[i]);
        }
    };
};
#endif //GAMEENGINE_TEXTMASTER_H
