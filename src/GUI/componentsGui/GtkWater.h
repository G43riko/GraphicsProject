//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_GTKWATER_H
#define GRAPHICSPROJECT_GTKWATER_H

class GtkWater{
private:
    WaterMaster * master = nullptr;
    GtkWidget * panel = nullptr;
    GtkWidget * waterSpeed = nullptr;
    GtkWidget * refractiveRation = nullptr;
    GtkWidget * waveStrength = nullptr;
    GtkWidget * shineDumper = nullptr;
    GtkWidget * reflectivity = nullptr;
    GtkWidget * tiling = nullptr;
    GtkWidget * waterHeight = nullptr;
    GtkWidget * addSlider(std::string title, double min, double max, double step, double value){
        GtkWidget * result =  GtkHandler::createSlider(min, max, step, value);
        gtk_widget_set_size_request(GTK_WIDGET(result), 300, 20);
        g_signal_connect(result, "value_changed", G_CALLBACK(GtkWater::waterChange), this);

        GtkWidget * label = gtk_label_new(title.c_str());
        gtk_label_set_xalign(GTK_LABEL(label), -1.0f);
        gtk_widget_set_size_request(GTK_WIDGET(label), 120, 20);
        gtk_widget_show (label);

        GtkWidget * locPanel = GtkHandler::createBox(GTK_ORIENTATION_HORIZONTAL, 20);
        gtk_container_add (GTK_CONTAINER (locPanel), label);
        gtk_container_add (GTK_CONTAINER (locPanel), result);
        gtk_container_add (GTK_CONTAINER (panel), locPanel);
        return result;
    }
public:
    static inline void waterChange(GtkWidget *widget, gpointer data){
        GtkWater * water = (GtkWater *)data;
        water -> master -> setTiling((float)gtk_range_get_value(GTK_RANGE(water->tiling)));
        water -> master -> setWaveStrength((float)gtk_range_get_value(GTK_RANGE(water->waveStrength)));
        water -> master -> setShineDumper((float)gtk_range_get_value(GTK_RANGE(water->shineDumper)));
        water -> master -> setReflectivity((float)gtk_range_get_value(GTK_RANGE(water->reflectivity)));
        water -> master -> setRefractiveRation((float)gtk_range_get_value(GTK_RANGE(water->refractiveRation)));
        water -> master -> setWaterSpeed((float)gtk_range_get_value(GTK_RANGE(water->waterSpeed)));
        water -> master -> setWaterHeight((float)gtk_range_get_value(GTK_RANGE(water->waterHeight)));
    };
    GtkWater(WaterMaster * master) : master(master){
        panel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 5);

        tiling = addSlider("Tiling:", 0, 20, 0.1, master -> getTilig());
        waveStrength = addSlider("Wave strength:", 0.00, 0.3, 0.001, master -> getWaveStrenght());
        shineDumper = addSlider("Shine dumper:", 0.00, 200, 1, master -> getShineDumper());
        reflectivity = addSlider("Reflectivity:", 0.00, 10, 0.01, master -> getReflectivity());
        refractiveRation = addSlider("Refractive ration:", 0.00, 5, 0.1, master -> getRefractiveRation());
        waterSpeed = addSlider("Water speed:", 0.0, 0.01, 0.00001, master -> getWaterSpeed());
        waterHeight = addSlider("Water height:", -20.0, 20, 0.1, master -> getWaterHeight());
    };
    GtkWidget * getPanel(void){
        return panel;
    };
};

#endif //GRAPHICSPROJECT_GTKWATER_H
