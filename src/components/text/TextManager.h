//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_TEXTMANAGER_H
#define GAMEENGINE_TEXTMANAGER_H

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include "TextLine.h"
#include <src/utils/math/objects/Vectors.h>
#include <GL/glew.h>
#include <src/rendering/shader/BasicShader.h>

class TextManager{
    struct Character {
        uint     TextureID;  // ID handle of the glyph texture
        Vector2f Size;       // Size of glyph
        Vector2f Bearing;    // Offset from baseline to left/top of glyph
        long     Advance;    // Offset to advance to next glyph
    };
    uint VAO, VBO;

    std::map<char , Character> Characters;

    void prepareVaoAndVbo(void){
        // Configure VAO/VBO for texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
public:
    TextManager(void){
//        // FreeType
//        FT_Library ft;
//        // All functions return a value different than 0 whenever an error occurred
//        if (FT_Init_FreeType(&ft))
//            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
//
//        // Load font as face
//        FT_Face face;
//        if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
//            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
//
//        // Set size to load glyphs as
//        FT_Set_Pixel_Sizes(face, 0, 48);
//
//        // Disable byte-alignment restriction
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//        // Load first 128 characters of ASCII set
//        for (GLubyte c = 0; c < 128; c++)
//        {
//            // Load character glyph
//            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//            {
//                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
//                continue;
//            }
//            // Generate texture
//            GLuint texture;
//            glGenTextures(1, &texture);
//            glBindTexture(GL_TEXTURE_2D, texture);
//            glTexImage2D(GL_TEXTURE_2D,
//                         0,
//                         GL_RED,
//                         face -> glyph -> bitmap.width,
//                         face -> glyph -> bitmap.rows,
//                         0,
//                         GL_RED,
//                         GL_UNSIGNED_BYTE,
//                         face -> glyph -> bitmap.buffer);
//            // Set texture options
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//            // Now store character for later use
//            Character character = {texture,
//                                   Vector2f((int)face -> glyph -> bitmap.width, (int)face -> glyph -> bitmap.rows),
//                                   Vector2f((int)face -> glyph -> bitmap_left, (int)face -> glyph -> bitmap_top),
//                                   face -> glyph -> advance.x};
//            Characters.insert(std::pair<GLchar, Character>(c, character));
//        }
//        glBindTexture(GL_TEXTURE_2D, 0);
//        // Destroy FreeType once we're finished
//        FT_Done_Face(face);
//        FT_Done_FreeType(ft);

        prepareVaoAndVbo();
    }
    void RenderText(BasicShader& shader, const TextLine& text){
        // Activate corresponding render state
        shader.bind();
        shader.updateUniform3f("textColor", text.getColor());
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // Iterate through all characters
        std::string::const_iterator c;
        float x = text.getX();
        for (c = text.getText().begin(); c != text.getText().end(); c++) {
            Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * text.getScale();
            float ypos = text.getY() - (ch.Size.y - ch.Bearing.y) * text.getScale();

            float w = ch.Size.x * text.getScale();
            float h = ch.Size.y * text.getScale();
            // Update VBO for each character
            float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0, 0.0 },
                    { xpos,     ypos,       0.0, 1.0 },
                    { xpos + w, ypos,       1.0, 1.0 },

                    { xpos,     ypos + h,   0.0, 0.0 },
                    { xpos + w, ypos,       1.0, 1.0 },
                    { xpos + w, ypos + h,   1.0, 0.0 }
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (float)(ch.Advance >> 6) * text.getScale(); // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif //GAMEENGINE_TEXTMANAGER_H
