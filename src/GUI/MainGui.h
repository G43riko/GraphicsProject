//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINGUI_H
#define GRAPHICSPROJECT_MAINGUI_H

#include <gtk/gtk.h>
#include <string>
#include <src/components/water/WaterMaster.h>
#include "GtkHandler.h"


static void showValue(GtkWidget *widget, gpointer data) {
    printf("value: %lf\n", gtk_range_get_value(GTK_RANGE(widget)));
}


/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void hello(GtkWidget *widget, gpointer data){
    g_print ("Hello World\n");
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data){
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return TRUE;
}
/* Another callback */
static void destroy(GtkWidget *widget, gpointer data){
    gtk_main_quit ();
}


class GtkWater{
private:
    WaterMaster * master = nullptr;
    GtkWidget * panel;
    GtkWidget * waterSpeed = nullptr;
    GtkWidget * refractiveRation = nullptr;
    GtkWidget * waveStrength = nullptr;
    GtkWidget * shineDumper = nullptr;
    GtkWidget * reflectivity = nullptr;
    GtkWidget * tiling = nullptr;
    GtkWidget * addSlider(std::string title, double min, double max, double step, double value){
        GtkWidget * result =  GtkHandler::createSlider(min, max, step, value);
        gtk_widget_set_size_request(GTK_WIDGET(result), 300, 20);
        GtkWidget * locPanel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 20);

        GtkWidget * label = gtk_label_new(title.c_str());
        gtk_label_set_xalign(GTK_LABEL(label), -1.0f);
        gtk_widget_set_size_request(GTK_WIDGET(label), 120, 20);
        gtk_widget_show (label);

        g_signal_connect (result, "value_changed", G_CALLBACK(GtkWater::waterChange), this);
        gtk_container_add (GTK_CONTAINER (locPanel), label);
        gtk_container_add (GTK_CONTAINER (locPanel), result);
        gtk_container_add (GTK_CONTAINER (panel), locPanel);
        return result;
    }
public:
    static inline void waterChange(GtkWidget *widget, gpointer data){
        GtkWater * water = (GtkWater *)data;
        water -> master -> setTiling((int)gtk_range_get_value(GTK_RANGE(water->tiling)));
        water -> master -> setWaveStrength((float)gtk_range_get_value(GTK_RANGE(water->waveStrength)));
        water -> master -> setShineDumper((float)gtk_range_get_value(GTK_RANGE(water->shineDumper)));
        water -> master -> setReflectivity((float)gtk_range_get_value(GTK_RANGE(water->reflectivity)));
        water -> master -> setRefractiveRation((float)gtk_range_get_value(GTK_RANGE(water->refractiveRation)));
        water -> master -> setWaterSpeed((float)gtk_range_get_value(GTK_RANGE(water->waterSpeed)));
    }
    GtkWater(WaterMaster * master) : master(master){
        panel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 5);

        tiling = addSlider("Tiling:", 0, 20, 1, 6);
        waveStrength = addSlider("Wave strength:", 0.00, 0.3, 0.001, 0.02);
        shineDumper = addSlider("Shine dumper:", 0.00, 200, 1, 20);
        reflectivity = addSlider("Reflectivity:", 0.00, 10, 0.01, 0.6);
        refractiveRation = addSlider("Refractive ration:", 0.00, 5, 0.1, 1.0);
        waterSpeed = addSlider("Water speed:", 0.0, 0.01, 0.00001, 0.001);
    };

    GtkWidget * getPanel(void){
        return panel;
    };
};



class MainGui {
private:
    GtkWater * water = nullptr;
    GtkWidget * window = nullptr;

public:
    void setWater(GtkWater * water){
        this -> water = water;
        gtk_container_add (GTK_CONTAINER(window), water->getPanel());
    }
    void cleanUp(void){

    }
    int init(){
        gtk_init(nullptr, nullptr);

        window = GtkHandler::initWindow();
        GtkWidget * button = GtkHandler::createButton("neklikaj!!!!");



        /* When the window is given the "delete-event" signal (this is given
         * by the window manager, usually by the "close" option, or on the
         * titlebar), we ask it to call the delete_event () function
         * as defined above. The data passed to the callback
         * function is NULL and is ignored in the callback function. */
        g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);

        /* Here we connect the "destroy" event to a signal handler.
         * This event occurs when we call gtk_widget_destroy() on the window,
         * or if we return FALSE in the "delete-event" callback. */
        g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);

        /* Sets the border width of the window. */
        gtk_container_set_border_width (GTK_CONTAINER (window), 10);


        /* When the button receives the "clicked" signal, it will call the
         * function hello() passing it NULL as its argument.  The hello()
         * function is defined above. */
        g_signal_connect (button, "clicked", G_CALLBACK (hello), NULL);

        /* This will cause the window to be destroyed by calling
         * gtk_widget_destroy(window) when "clicked".  Again, the destroy
         * signal could come from here, or the window manager. */
        g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

        /* This packs the button into the window (a gtk container). */
        GtkWidget * gbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        gtk_widget_show (gbox1);

        GtkWidget * slider = GtkHandler::createSlider(0, 10, 1, 2);
        g_signal_connect (slider, "value_changed", G_CALLBACK(showValue), NULL);

        gtk_container_add (GTK_CONTAINER(gbox1), slider);
        gtk_container_add (GTK_CONTAINER(gbox1), button);

//        gtk_container_add (GTK_CONTAINER(window), gbox1);

        gtk_widget_show (window);

//        gtk_main ();

        return 0;
    }

    void update(){
        gtk_main_iteration_do(false);
    }
};


#endif //GRAPHICSPROJECT_MAINGUI_H
