#include "gtk/gtk.h"
#include <iostream>
#include "math.h"
#include "main.h"
#include "gtkui.h"

static void draw_function(GtkDrawingArea *area,cairo_t *cr,int width, int height,gpointer data){
    GdkRGBA color;
    struct vector leftcenter ={127.5,127.5},rightcenter={382.5,127.5};
    double radius=127.5;
    gtk_widget_get_color(GTK_WIDGET (area),&color);
    gdk_cairo_set_source_rgba(cr,&color);
    cairo_fill(cr);

    for(int i=0;i<8;i++){
        cairo_arc_negative(cr,leftcenter.x,leftcenter.y,radius,i*M_PI/4+M_PI/8,i*M_PI/4-M_PI/8);
        cairo_line_to(cr,leftcenter.x+deadzone*cos(i*M_PI/4-M_PI/8),leftcenter.y+deadzone*sin(i*M_PI/4-M_PI/8));
        cairo_arc(cr,leftcenter.x,leftcenter.y,deadzone,i*M_PI/4-M_PI/8,i*M_PI/4+M_PI/8);
        cairo_line_to(cr,leftcenter.x+radius*cos(i*M_PI/4+M_PI/8),leftcenter.y+radius*sin(i*M_PI/4+M_PI/8));
        cairo_stroke(cr);
        cairo_arc_negative(cr,rightcenter.x,rightcenter.y,radius,i*M_PI/4+M_PI/8,i*M_PI/4-M_PI/8);
        cairo_line_to(cr,rightcenter.x+deadzone*cos(i*M_PI/4-M_PI/8),rightcenter.y+deadzone*sin(i*M_PI/4-M_PI/8));
        cairo_arc(cr,rightcenter.x,rightcenter.y,deadzone,i*M_PI/4-M_PI/8,i*M_PI/4+M_PI/8);
        cairo_line_to(cr,rightcenter.x+radius*cos(i*M_PI/4+M_PI/8),rightcenter.y+radius*sin(i*M_PI/4+M_PI/8));
        cairo_stroke(cr);

    }
    cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
    cairo_set_line_width(cr,5);
    cairo_move_to(cr,leftstick.x,leftstick.y);
    cairo_line_to(cr,leftstick.x,leftstick.y);
    cairo_stroke(cr);
    //cairo_set_line_cap(cr,CAIRO_LINE_CAP_ROUND);
    //cairo_set_line_width(cr,5);
    cairo_move_to(cr,255+rightstick.x,rightstick.y);
    cairo_line_to(cr,255+rightstick.x,rightstick.y);
    cairo_stroke(cr);
}
int runGui(bool *running){

    int gstat=gtk_init_check();
    if(gstat!=-1){
    GtkWidget *window;
    GtkWidget *drawingArea;
    cairo_t *cr;
    window = gtk_window_new();
    drawingArea=gtk_drawing_area_new();
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawingArea),510);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawingArea),255);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawingArea),draw_function,NULL,NULL);

    gtk_window_set_title(GTK_WINDOW(window), "Semaphore");
    gtk_window_set_default_size(GTK_WINDOW(window),510,255);
    gtk_window_set_child(GTK_WINDOW (window),drawingArea);
    std::cout << "\r\t\t\t\rgtk activate"<<std::endl;
    gtk_widget_set_visible(window,TRUE);
    //gtk_window_present(GTK_WINDOW (window));
    while(running){
        g_main_context_iteration(NULL,true);
        gtk_widget_queue_draw(drawingArea);
        usleep(1000);
    }
    }

    else {
        return 1;}



return 0;
}
