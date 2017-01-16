//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKHANDLER_H
#define GRAPHICSPROJECT_GTKHANDLER_H

#include <gtk/gtk.h>

class GtkHandler{
    public:
        static inline GtkWidget * addSlider(std::string title, double min, double max, double step, double value, GCallback callback, gpointer data = nullptr, GtkWidget * target = nullptr){
            GtkWidget * result =  GtkHandler::createSlider(min, max, step, value);
            gtk_widget_set_size_request(GTK_WIDGET(result), 300, 20);
            if(data){
                g_signal_connect(result, "value_changed", callback, data);
            }
            if(target){
                GtkWidget * label = gtk_label_new(title.c_str());
                gtk_label_set_xalign(GTK_LABEL(label), -1.0f);
                gtk_widget_set_size_request(GTK_WIDGET(label), 120, 20);
                gtk_widget_show (label);

                GtkWidget * locPanel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 20);
                gtk_container_add (GTK_CONTAINER (locPanel), label);
                gtk_container_add (GTK_CONTAINER (locPanel), result);

                gtk_container_add (GTK_CONTAINER (target), locPanel);
            }
            return result;
        };

        static inline GtkWidget * createSlider(double min, double max, double step, double value){
            GtkWidget * slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min, max, step);
            gtk_range_set_value(GTK_RANGE(slider), value);
//            gtk_widget_show (slider);
            return slider;
        };
        static inline GtkWidget * createSlider(double min, double max, double step){
            return createSlider(min, max, step, min);
        };
        static inline GtkWidget * initWindow(){
            GtkWidget * window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
            gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
//            g_signal_connect (window, "delete-event", G_CALLBACK (gtk_main_quit), NULL);
            gtk_widget_hide_on_delete(window);

    //        gtk_window_set_resizable(GTK_WINDOW(window), false);
            return window;
        };
        static inline GtkWidget * createButton(char * label){
            GtkWidget * button = gtk_button_new_with_label(label);
            return button;
        };
        static inline GtkWidget * createBox(GtkOrientation orientation, int spacing){
            GtkWidget * box = gtk_box_new(orientation, spacing);
            return box;
        };
};
#endif //GRAPHICSPROJECT_GTKHANDLER_H
