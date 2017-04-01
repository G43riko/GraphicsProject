//
// Created by gabriel on 24.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKINTROGUI_H
#define GRAPHICSPROJECT_GTKINTROGUI_H

#include <gtk/gtk.h>
#include "GtkHandler.h"


class BasicEngine;

class GtkIntroGui {
private:
    GtkWidget * resX            = nullptr;
    GtkWidget * resY            = nullptr;
    GtkWidget * introPanel      = nullptr;
    GtkWidget * fullscreen      = nullptr;
    GtkWidget * stopButton      = nullptr;
    GtkWidget * startButton     = nullptr;
    GtkWidget * resolutionPanel = nullptr;

    bool exitRequest = false;
    BasicEngine * engine;
    static void gameStart(GtkWidget *widget, gpointer data);
    static void gameStop(GtkWidget *widget, gpointer data);
    static void engineExit(GtkWidget *widget, gpointer data);
    static void changeFullScreen(GtkWidget *widget, gpointer data);
public:
    inline void appIsRunning(bool value){
        gtk_widget_set_sensitive(stopButton, value);
        gtk_widget_set_sensitive(startButton, !value);
    }
    inline bool getFullscreen(void){
        return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(fullscreen)) == gtk_true();
    }
    inline int getResX(void){
        return gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(resX));
    }
    inline int getResY(void){
        return gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(resY));
    }
    void initAndShowIntroView(void);
    GtkIntroGui(BasicEngine * engine) : engine(engine){};
    inline bool getExitRequest(void){
        return exitRequest;
    };

    GtkWidget * getPanel(void){
        return introPanel;
    };
};


#endif //GRAPHICSPROJECT_GTKINTROGUI_H
