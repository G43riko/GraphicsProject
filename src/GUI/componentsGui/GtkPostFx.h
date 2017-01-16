//
// Created by gabriel on 16.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKPOSTFX_H
#define GRAPHICSPROJECT_GTKPOSTFX_H

#include <src/components/postProccessing/PostFxMaster.h>
#include <gtk/gtk.h>
#include <src/GUI/GtkHandler.h>

class GtkPostFx{
private:
    PostFxMaster * master = nullptr;
    GtkWidget * panel = nullptr;
    GtkWidget * contrastValue = nullptr;
    GtkWidget * usePostFx = nullptr;
public:
    static inline void postFxChange(GtkWidget *widget, gpointer data){
        GtkPostFx * postFx = (GtkPostFx *)data;
        bool usePostFx = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(postFx->usePostFx)) == gtk_true();

        if(postFx -> master ->getUsingPostFx() != usePostFx){
            postFx -> master ->setUsingPostFx(usePostFx);
            gtk_widget_set_sensitive(postFx -> contrastValue, usePostFx);
            return;
        }

        postFx -> master -> setContrastValue((float)gtk_range_get_value(GTK_RANGE(postFx->contrastValue)));
    };
    GtkPostFx(PostFxMaster * master) : master(master){
        panel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 20);

        usePostFx = gtk_check_button_new_with_label("Používat PostFx");
        g_signal_connect(usePostFx, "toggled", G_CALLBACK(GtkPostFx::postFxChange), this);
        gtk_container_add (GTK_CONTAINER (panel), usePostFx);


        contrastValue = GtkHandler::addSlider("contrast:", 0.00, 2, 0.01, master -> getContrastValue(), G_CALLBACK(GtkPostFx::postFxChange), this, panel);
    };
    GtkWidget * getPanel(void){
        return GTK_WIDGET(panel);
    };
};

#endif //GRAPHICSPROJECT_GTKPOSTFX_H
