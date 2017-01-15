//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKHANDLER_H
#define GRAPHICSPROJECT_GTKHANDLER_H

#include <gtk/gtk.h>

class GtkHandler{
    public:
        static inline GtkWidget * createSlider(double min, double max, double step, double value){
            GtkWidget * slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, min, max, step);
            gtk_range_set_value(GTK_RANGE(slider), value);
            gtk_widget_show (slider);
            return slider;
        };
        static inline GtkWidget * createSlider(double min, double max, double step){
            return createSlider(min, max, step, min);
        }
        static inline GtkWidget * initWindow(){
            GtkWidget * window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
            gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    //        gtk_window_set_resizable(GTK_WINDOW(window), false);
            return window;
        };
        static inline GtkWidget * createButton(char * label){
            GtkWidget * button = gtk_button_new_with_label(label);
            gtk_widget_show (button);
            return button;
        };
        static inline GtkWidget * createBox(GtkOrientation orientation, int spacing){
            GtkWidget * box = gtk_box_new(orientation, spacing);
            gtk_widget_show(box);
            return box;
        };
};
#endif //GRAPHICSPROJECT_GTKHANDLER_H
