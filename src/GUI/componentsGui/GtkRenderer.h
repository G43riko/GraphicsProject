//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKRENDERER_H
#define GRAPHICSPROJECT_GTKRENDERER_H

#include <gtk/gtk.h>
#include <src/GUI/GtkHandler.h>
#include <src/rendering/Renderer.h>

class GtkRenderer{
private:
    GtkWidget * panel = nullptr;
    Renderer * renderer = nullptr;

    GtkWidget * renderWater = nullptr;
    GtkWidget * renderSky = nullptr;
    GtkWidget * renderParticles = nullptr;
    GtkWidget * panelLights = nullptr;
public:
    static inline void rendererChange(GtkWidget *widget, gpointer data){
        GtkRenderer * renderer = (GtkRenderer *)data;

        renderer->renderer->setWater(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(renderer->renderWater)) == gtk_true());
        renderer->renderer->setSky(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(renderer->renderSky)) == gtk_true());
    };
    GtkRenderer(Renderer * renderer) : renderer(renderer){
        panel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 20);

        renderWater = gtk_check_button_new_with_label("Renderovať vodu");
        g_signal_connect(renderWater, "toggled", G_CALLBACK(GtkRenderer::rendererChange), this);
        gtk_container_add (GTK_CONTAINER (panel), renderWater);

        renderSky = gtk_check_button_new_with_label("Renderovať oblohu");
        g_signal_connect(renderSky, "toggled", G_CALLBACK(GtkRenderer::rendererChange), this);
        gtk_container_add (GTK_CONTAINER (panel), renderSky);
    };

    GtkWidget * getPanel(void){
        return GTK_WIDGET(panel);
    };
};
#endif //GRAPHICSPROJECT_GTKRENDERER_H
