//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKSCENE_H
#define GRAPHICSPROJECT_GTKSCENE_H

#include <src/game/Scene.h>
#include <gtk/gtk.h>
#include <src/GUI/GtkHandler.h>



class GtkScene{
private:
    Scene * scene = nullptr;
    GtkWidget * panel = nullptr;

public:
    GtkScene(Scene * scene) : scene(scene){
        panel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 20);
    };
    GtkWidget * getPanel(void){
        return GTK_WIDGET(panel);
    };
};

#endif //GRAPHICSPROJECT_GTKSCENE_H
