#include "iostream"
#include "linux/input.h"
#include "pthread.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "unistd.h"
#include "math.h"
#include "main.h"
#include "gtkui.h"

struct vector leftstick,rightstick,offset;
bool isRunning = true;
bool letterMode = true;
bool capitalize = false;
float deadzone=64;
pthread_t gui;

u_int8_t oldkey;
u_int8_t key;
u_int8_t mask;



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

char getletter(){
    u_int8_t left;
    u_int8_t right;
    left=getActiveSector(leftstick.x-127.5,leftstick.y-127.5);
    right=getActiveSector(rightstick.x-127.5,rightstick.y-127.5);
    key = ((left << 4)^right);



    if(key!=oldkey){
        oldkey=key;

    mask = (letterMode<<6)|((letterMode&capitalize)<<5) | (letterMode<<4);
    u_int8_t cmask = capitalize<<5;
    switch(key){
        case 0x32:
            return '1'^mask;
        case 0x31:
            return '2'^mask;
        case 0x38:
            return '3'^mask;
        case 0x37:
            return '4'^mask;
        case 0x63:
            return '5'^mask;
        case 0x53:
            return '6'^mask;
        case 0x43:
            return '7'^mask;
        case 0x21:
            return '8'^mask;
        case 0x28:
            return '9'^mask;
        case 0x57:
            if(!letterMode){
                letterMode=true;
                break;
            }return 'j'^cmask;

        case 0x72:
            if(letterMode){return 'k'^cmask;}
            return '0';
        case 0x62:
            return 'l'^cmask;
        case 0x52:
            return 'm'^cmask;
        case 0x42:
            return 'n'^cmask;
        case 0x18:
            return 'o'^cmask;
        case 0x71:
            return 'p'^cmask;
        case 0x61:
            return 'q'^cmask;
        case 0x51:
            return 'r'^cmask;
        case 0x41:
            return 's'^cmask;
        case 0x78:
            return 't'^cmask;
        case 0x68:
            return 'u'^cmask;
        case 0x47:
            return 'v'^cmask;
        case 0x65:
            return 'w'^cmask;
        case 0x64:
            return 'x'^cmask;
        case 0x58:
            return 'y'^cmask;
        case 0x54:
            return 'z'^cmask;
        case 0x67:
            letterMode = false;
            break;
        case 0x33:
            return ' ';
        case 0x48:
            return 0x08;
    }
    }
    return 0x0;
}








void* activate(void* data){
    int guireturn;

    guireturn=runGui(&isRunning);
    pthread_exit(&gui);

}

int main(int argc,char **argv){
    int trigger;
    int test;
    bool debug = false;
    int status;
    char string[]="test";
    leftstick.x=0,leftstick.y=0,rightstick.x=0,rightstick.y=0;
    int gamepad;
     pthread_create(&gui,NULL,activate,string);
    if (argc > 1){
        gamepad = open(argv[1],O_RDONLY);
        std::cout <<argv[1]<<"\n";
    }else{
        gamepad = open("/dev/input/event5",O_RDONLY);
    }
    struct input_absinfo iabs;
    if(gamepad ==-1) std::cout <<gamepad;
    ioctl(gamepad,EVIOCGABS(ABS_X),&iabs);
    double middle =iabs.maximum;
    offset.x=middle;offset.y=middle;





    struct input_event events[8];
    while(isRunning){
    auto r1 = read(gamepad,events,sizeof events);
    int oldtrigger=0;
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
                        case EV_KEY:
                    switch (ev.code){
                        case BTN_TR:
                        trigger=ev.value;
                        if(oldtrigger==0){
                           debug = trigger^debug;
                        }
                        oldtrigger=trigger;
                    }
            }


        }

    }
    test=getActiveSector(leftstick.x-127.5,leftstick.y-127.5);
    if(debug){
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
        std::cout<<"test:" << test << std::hex << (int)mask<< "\r";
        std::cout.flush();
        }else{
            u_int8_t letter = getletter();
            if(letter!=0x0){
            std::cout << letter ;
            std::cout.flush();}
        }

    usleep(1000);
    }

}
