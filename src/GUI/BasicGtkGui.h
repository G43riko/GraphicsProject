//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINGUI_H
#define GRAPHICSPROJECT_MAINGUI_H

#include <gtk/gtk.h>
#include <string>
#include <src/components/water/WaterMaster.h>
#include <src/GUI/componentsGui/GtkScene.h>
#include "GtkHandler.h"
#include "src/GUI/componentsGui/GtkWater.h"
#include "src/GUI/componentsGui/GtkPostFx.h"
#include "src/GUI/componentsGui/GtkRenderer.h"

class BasicEngine;

class BasicGtkGui {
private:
    GtkScene * scene = nullptr;
    GtkWater * water = nullptr;
    GtkPostFx * postFx = nullptr;
    GtkRenderer * renderer = nullptr;
    GtkWidget * window = nullptr;
    GtkWidget * mainPanel = nullptr;
    GtkWidget * actualPanel = nullptr;
    GtkWidget * introPanel = nullptr;
    GtkWidget * resX = nullptr;
    GtkWidget * resY = nullptr;
    GtkWidget * stopButton = nullptr;
    GtkWidget * startButton = nullptr;
    GtkWidget * resolutionPanel = nullptr;
    BasicEngine * engine;
    static void gameStart(GtkWidget *widget, gpointer data);
    static void gameStop(GtkWidget *widget, gpointer data);
    static void engineExit(GtkWidget *widget, gpointer data);
    static void changeFullScreen(GtkWidget *widget, gpointer data);
    bool exitRequest = false;
public:
    inline bool getExitRequest(void){
        return exitRequest;
    }
    void initAndShowIntroView(void);
    BasicGtkGui(BasicEngine * engine) : engine(engine){};
    void setRenderer(GtkRenderer * renderer){
        if(this -> renderer == nullptr){
            this -> renderer = renderer;
            gtk_container_add(GTK_CONTAINER(mainPanel), renderer->getPanel());
        }
    };
    void showIntro(void){
        if(actualPanel){
            gtk_widget_hide(actualPanel);
            if(actualPanel == introPanel){
                hideWindow();
                actualPanel = nullptr;
                return;
            }
        }
        actualPanel = introPanel;
        gtk_widget_show_all(actualPanel);
        showWindow();
    };
    void showRenderer(void){
        if(actualPanel){
            gtk_widget_hide(actualPanel);
            if(actualPanel == renderer -> getPanel()){
                hideWindow();
                actualPanel = nullptr;
                return;
            }
        }
        actualPanel = renderer -> getPanel();
        gtk_widget_show_all(actualPanel);
        showWindow();
    };
    void setScene(GtkScene * scene){
        if(this -> scene == nullptr){
            this -> scene = scene;
            gtk_container_add(GTK_CONTAINER(mainPanel), scene->getPanel());
        }
    };
    void showScene(void){
        if(actualPanel){
            gtk_widget_hide(actualPanel);
            if(actualPanel == scene -> getPanel()){
                hideWindow();
                actualPanel = nullptr;
                return;
            }
        }
        actualPanel = scene -> getPanel();
        gtk_widget_show_all(actualPanel);
        showWindow();
    };
    void setPostFx(GtkPostFx * postFx){
        if(this -> postFx == nullptr){
            this -> postFx = postFx;
            gtk_container_add(GTK_CONTAINER(mainPanel), postFx->getPanel());
        }
    };
    void showPostFx(void){
        if(actualPanel){
            gtk_widget_hide(actualPanel);
            if(actualPanel == postFx -> getPanel()){
                hideWindow();
                actualPanel = nullptr;
                return;
            }
        }
        actualPanel = postFx -> getPanel();
        gtk_widget_show_all(actualPanel);
        showWindow();
    };
    void setWater(GtkWater * water){
        if(this -> water == nullptr){
            this -> water = water;
            gtk_container_add(GTK_CONTAINER(mainPanel), water->getPanel());
        }
    };
    void showWater(void){
        if(actualPanel){
            gtk_widget_hide(actualPanel);
            if(actualPanel == water -> getPanel()){
                hideWindow();
                actualPanel = nullptr;
                return;
            }
        }
        actualPanel = water -> getPanel();
        gtk_widget_show_all(actualPanel);
        showWindow();
    };
    void toggleWindow(void){
        isWindowVisible() ? hideWindow() : showWindow();
    };
    bool isWindowVisible(void){
        return gtk_widget_is_visible(window) == gtk_true();
    };
    void showWindow(void){
        gtk_widget_show(mainPanel);
        gtk_widget_show(window);
    };
    void hideWindow(void){
        gtk_widget_hide(window);
    };

    void cleanUp(void){

    };
    void testGtkTreeModel(void){
//      gtk_tree_view_co
//        GtkTreeModel * model = gtk_tree_model_new
        GtkTreeViewColumn * column = gtk_tree_view_column_new();
        gtk_tree_view_column_set_title(column, "nieco");
    };

    int init(){
//        enum {
//            STRING_COLUMN,
//            INT_COLUMN,
//            N_COLUMNS
//        };

        gtk_init(nullptr, nullptr);


//        GtkBuilder *builder;
//        builder = gtk_builder_new();
//        gtk_builder_add_from_file(builder, "res/test.glade", 0);
//        gtk_builder_connect_signals(builder, 0);
//        gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow")));
//        g_object_unref(G_OBJECT(builder));


        window = GtkHandler::initWindow();
        mainPanel = GtkHandler::createBox(GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add(GTK_CONTAINER(window), mainPanel);

//        GtkListStore * list_store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_INT);
//
//        GtkTreeIter iter;
//        gtk_list_store_append(list_store, &iter);
//        gtk_list_store_set(list_store, &iter, 0, "c", 1, "d", -1);
//        gtk_list_store_set_column_types()


        //GtkWidget * tree = gtk_tree_view_new_with_model()
        initAndShowIntroView();
        showIntro();
        return 0;
    };

    void update(){
        gtk_main_iteration_do(false);
    };
};


#endif //GRAPHICSPROJECT_MAINGUI_H
