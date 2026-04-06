#include "iostream"
#include "pthread.h"
#include "unistd.h"
#include "math.h"
#include "main.h"
#include "gtkui.h"
#include "util.h"

bool isRunning = true;
pthread_t gui;

void* activate(void* data){
    int guireturn;

    guireturn=runGui(&isRunning);
    pthread_exit(&gui);

}
int main(int argc,char **argv){
    int test;
    bool debug = false;
    char string[]="test";
    leftstick.x=0,leftstick.y=0,rightstick.x=0,rightstick.y=0;
    int gamepad= open_gamepad();
    if(gamepad !=-1) return 1;

    pthread_create(&gui,NULL,activate,string);



	while(isRunning){
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
		
		std::cout<<"test:" << test << std::hex <<"\r";
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


