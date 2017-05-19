//
// Created by gabriel on 24.1.2017.
//

#include <src/core/BasicEngine.h>
#include <src/misc/MainApplication.h>
#include "GtkIntroGui.h"

void GtkIntroGui::gameStart(GtkWidget *widget, gpointer data){
    GtkIntroGui * gui = (GtkIntroGui *)data;
    gui -> engine -> setUpApp(new MainApplication());
    gui -> engine -> appStart();
}
void GtkIntroGui::gameStop(GtkWidget *widget, gpointer data){
    GtkIntroGui * gui = (GtkIntroGui *)data;
    gui -> engine -> appStop();
}
void GtkIntroGui::engineExit(GtkWidget *widget, gpointer data){
    GtkIntroGui * gui = (GtkIntroGui *)data;
    gui ->exitRequest = true;
}

void GtkIntroGui::changeFullScreen(GtkWidget *widget, gpointer data){
    GtkIntroGui * gui = (GtkIntroGui *)data;
    gtk_widget_set_sensitive(gui -> resolutionPanel, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) != gtk_true());
}
void GtkIntroGui::initAndShowIntroView(void){
    bool fullScreen = true;
    introPanel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 0);

    fullscreen = GtkHandler::createCheckBox(fullScreen, "Fullscreen", G_CALLBACK(GtkIntroGui::changeFullScreen), this, GTK_CONTAINER(introPanel));

    resolutionPanel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(resolutionPanel), true);
    gtk_widget_set_sensitive(resolutionPanel, !fullScreen);

    resX = gtk_spin_button_new_with_range(RES_X_MIN, RES_X_MAX, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(resX), engine -> getResX());
    gtk_widget_set_size_request(GTK_WIDGET(resX), 120, 20);

    resY = gtk_spin_button_new_with_range(RES_Y_MIN, RES_Y_MAX, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(resY), engine -> getResY());
    gtk_widget_set_size_request(GTK_WIDGET(resY), 120, 20);

    gtk_container_add(GTK_CONTAINER(resolutionPanel), gtk_label_new("Rozlíšenie: "));
    gtk_container_add(GTK_CONTAINER(resolutionPanel), resX);
    gtk_container_add(GTK_CONTAINER(resolutionPanel), resY);

    gtk_container_add(GTK_CONTAINER(introPanel), resolutionPanel);


    startButton = GtkHandler::createButton("Start game");
    g_signal_connect(startButton, "clicked", G_CALLBACK(GtkIntroGui::gameStart), this);
    gtk_container_add(GTK_CONTAINER(introPanel), startButton);

    stopButton = GtkHandler::createButton("Stop game");
    g_signal_connect(stopButton, "clicked", G_CALLBACK(GtkIntroGui::gameStop), this);
    gtk_container_add(GTK_CONTAINER(introPanel), stopButton);
    gtk_widget_set_sensitive(stopButton, false);


    GtkWidget * exitButton = GtkHandler::createButton("Exit engine");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(GtkIntroGui::engineExit), this);
    gtk_container_add(GTK_CONTAINER(introPanel), exitButton);
}