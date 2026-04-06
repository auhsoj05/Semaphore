#include "semaphore.h"
#include "fcitx/inputcontextmanager.h"
#include "pthread.h"
#include "fcitx-utils/key.h"
#include "fcitx/event.h"
#include "fcitx-utils/eventdispatcher.h"
#include "util.h"



fcitx::InputContextManager *manager;
bool isrunning = false;
pthread_t loopt;
fcitx::Instance *inst;
fcitx::InputContextManager *im;
fcitx::InputContext *ic;
fcitx::Key key;

fcitx::Event *event;
fcitx::EventDispatcher *evD;
int gamepadfd;



void* loop(void* data){

	while(isrunning){
		updateSticks(gamepadfd);
		char letter = getletter();
		if(letter != 0x0){
		if(letter == '\b'){
			key = fcitx::Key(FcitxKey_BackSpace);

		}else{
			std::string keys(1,letter);
			key =  fcitx::Key(keys);
		}
		ic =im->lastFocusedInputContext();
		if(ic!=NULL){
		ic->forwardKey(key,false,1);
		evD->schedule(NULL);
	}}


		usleep(1000);

	};
	return data;
}

SemaphoreEngine::SemaphoreEngine(fcitx::Instance *instance):instance_(instance){
	inst = instance_;
	im = &(instance_->inputContextManager());
	ic = im->lastFocusedInputContext();
	evD = &(instance_->eventDispatcher());
	gamepadfd = open_gamepad();
	FCITX_INFO() << "gamepad" << gamepadfd;
	if(gamepadfd != -1){
		normalize(gamepadfd);

		isrunning=true;
		char threadname[] = "loop thread";
		manager = new fcitx::InputContextManager();
		pthread_create(&loopt,NULL,loop,threadname);
		pthread_detach(loopt);
	}

	}
SemaphoreEngine::~SemaphoreEngine(){
	if(gamepadfd != 0x0)
		close(gamepadfd);
}

void SemaphoreEngine::keyEvent(const fcitx::InputMethodEntry& entry, fcitx::KeyEvent& keyEvent){
	FCITX_UNUSED(entry);
	FCITX_INFO() << keyEvent.key() << " isRelease=" << keyEvent.isRelease();
	
}


FCITX_ADDON_FACTORY(SemaphoreEngineFactory);
