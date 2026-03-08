#include "iostream"
#include "linux/input.h"
#include "pthread.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "unistd.h"
#include "gtk/gtk.h"
#include "cairo.h"

struct {float x,y;} leftstick,rightstick;
bool isRunning = true;
pthread_t gui;



static void draw_function(GtkDrawingArea *area,cairo_t *cr,int width, int height,gpointer data){

}
void* activate(void* data){

    GtkWidget *window;
    GtkWidget *DrawingArea;
    cairo_t *cr;
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Semaphore");
    gtk_window_set_default_size(GTK_WINDOW(window),255,255);
    std::cout << "gtk activate"<<std::endl;
    gtk_window_present(GTK_WINDOW(window));

    while(isRunning){
        g_main_context_iteration(NULL,true);
    }


return 0;
}

int main(int argc,char **argv){
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
    std::cout<<"here"<<iabs.maximum<<"\n";




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
        std::cout<<rightstick.y<<"\r";
        std::cout.flush();
    }
}
