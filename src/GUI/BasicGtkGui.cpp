//
// Created by gabriel on 15.1.2017.
//

#include "BasicGtkGui.h"

#include <src/core/BasicEngine.h>

void BasicGtkGui::gameStart(GtkWidget *widget, gpointer data){
    BasicGtkGui * gui = (BasicGtkGui *)data;
    gui -> engine -> setUpApp(new MainApplication());
    gtk_widget_set_sensitive(gui -> stopButton, true);
    gtk_widget_set_sensitive(gui -> startButton, false);
    gui -> engine -> appStart();
}
void BasicGtkGui::gameStop(GtkWidget *widget, gpointer data){
    BasicGtkGui * gui = (BasicGtkGui *)data;
    gtk_widget_set_sensitive(gui -> stopButton, false);
    gtk_widget_set_sensitive(gui -> startButton, true);
    gui -> engine -> appStop();
}
void BasicGtkGui::engineExit(GtkWidget *widget, gpointer data){
    BasicGtkGui * gui = (BasicGtkGui *)data;
    gui ->exitRequest = true;
}

void BasicGtkGui::changeFullScreen(GtkWidget *widget, gpointer data){
    BasicGtkGui * gui = (BasicGtkGui *)data;
    gtk_widget_set_sensitive(gui -> resolutionPanel, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) != gtk_true());
}
void BasicGtkGui::initAndShowIntroView(void){
    bool fullScreen = true;
    introPanel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 0);

    GtkHandler::createCheckBox(fullScreen, "Fullscreen", G_CALLBACK(BasicGtkGui::changeFullScreen), this, GTK_CONTAINER(introPanel));

    resolutionPanel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_set_homogeneous(GTK_BOX(resolutionPanel), true);
    gtk_widget_set_sensitive(resolutionPanel, !fullScreen);

    resX = gtk_spin_button_new_with_range(800, 4096, 1);
    gtk_widget_set_size_request(GTK_WIDGET(resX), 120, 20);

    resY = gtk_spin_button_new_with_range(600, 4096, 1);
    gtk_widget_set_size_request(GTK_WIDGET(resY), 120, 20);

    gtk_container_add(GTK_CONTAINER(resolutionPanel), gtk_label_new("Rozlíšenie: "));
    gtk_container_add(GTK_CONTAINER(resolutionPanel), resX);
    gtk_container_add(GTK_CONTAINER(resolutionPanel), resY);

    gtk_container_add(GTK_CONTAINER(introPanel), resolutionPanel);


    startButton = GtkHandler::createButton("Start game");
    g_signal_connect(startButton, "clicked", G_CALLBACK(BasicGtkGui::gameStart), this);
    gtk_container_add(GTK_CONTAINER(introPanel), startButton);

    stopButton = GtkHandler::createButton("Stop game");
    g_signal_connect(stopButton, "clicked", G_CALLBACK(BasicGtkGui::gameStop), this);
    gtk_container_add(GTK_CONTAINER(introPanel), stopButton);
    gtk_widget_set_sensitive(stopButton, false);


    GtkWidget * exitButton = GtkHandler::createButton("Exit engine");
    g_signal_connect(exitButton, "clicked", G_CALLBACK(BasicGtkGui::engineExit), this);
    gtk_container_add(GTK_CONTAINER(introPanel), exitButton);


    gtk_container_add(GTK_CONTAINER(mainPanel), introPanel);
}