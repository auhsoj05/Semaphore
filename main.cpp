#include "iostream"
#include "linux/input.h"
#include "pthread.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "unistd.h"
#include "gtk/gtk.h"
#include "cairo.h"
#include "math.h"

struct {float x,y;} leftstick,rightstick;
bool isRunning = true;
int deadzone=64;
pthread_t gui;
u_int8_t getActiveSector(double x,double y){

    if (x*x+y*y <=deadzone*deadzone){
        return 0;}
    if (x==0)
        return ((y<0)<<2)^3;
    double angle = atan(y/x);
    if (-M_PI/2 < angle && angle < -3*M_PI/8)
        return ((x>0)<<2)^3;
    if(-3*M_PI/8<angle && angle< -M_PI/8)
        return 4<<(x>0);
    if(-M_PI/8<angle && angle<M_PI/8)
        return ((x<0)<<2)^1;
    if(M_PI/8 <angle && angle < 3*M_PI/8)
        return ((x<0)<<2)^2;
    if(3*M_PI/8<angle && angle < M_PI/2)
        return((x<0)<<2)^3;



    return 0;

}



static void draw_function(GtkDrawingArea *area,cairo_t *cr,int width, int height,gpointer data){
    GdkRGBA color;
    struct {double x,y;} leftcenter,rightcenter;
    leftcenter ={127.5,127.5};
    rightcenter={382.5,127.5};
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
void* activate(void* data){

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
    while(isRunning){
        g_main_context_iteration(NULL,true);
        gtk_widget_queue_draw(drawingArea);
        usleep(1000);
    }


return 0;
}

int main(int argc,char **argv){
    int test;
    int status;
    char string[] = "this";
    leftstick.x=0,leftstick.y=0,rightstick.x=0,rightstick.y=0;
    int gstat=gtk_init_check();
    if(gstat!=-1)
        pthread_create(&gui,NULL,activate,string);
    else
        std::cout<<"gtk could not initialize:" <<gstat <<"\n";
    int gamepad;
    if (argc > 1){
        gamepad = open(argv[1],O_RDONLY);
        std::cout <<argv[1]<<"\n";
    }else{
        gamepad = open("/dev/input/event5",O_RDONLY);
    }
    struct input_absinfo iabs;
    if(gamepad ==-1) std::cout <<gamepad;
    ioctl(gamepad,EVIOCGABS(ABS_X),&iabs);
    std::cout<<"max value:"<<iabs.maximum<<"\n";




    struct input_event events[8];
    while(isRunning){
    auto r1 = read(gamepad,events,sizeof events);
    if(r1 != -1){
        int new_event_count = r1/sizeof(struct input_event);
        for(int evi=0;evi<new_event_count;evi++){
            auto& ev = events[evi];
            switch (ev.type){
                case EV_ABS:
                    switch(ev.code){
                        case ABS_X:
                            leftstick.x=ev.value;
                            break;
                        case ABS_Y:
                            leftstick.y=ev.value;
                            break;
                        case ABS_RX:
                            rightstick.x=ev.value;
                            break;
                        case ABS_RY:
                            rightstick.y=ev.value;
                            break;
                    }
            }


        }

    }
    test=getActiveSector(leftstick.x-127.5,leftstick.y-127.5);

    std::cout << "current position LSx:";
        std::cout.width(3);
        std::cout<<leftstick.x ;
        std::cout << "LSy:";
        std::cout.width(3);
        std::cout<< leftstick.y;
        std::cout << "RSx:";
        std::cout.width(3);
        std::cout<<rightstick.x;
        std::cout<<"RSy:";
        std::cout.width(3);
        std::cout<<rightstick.y;
        std::cout<<"test:" << test <<"\r";
        std::cout.flush();
    }
    usleep(1000);
}
