#include "semaphore.h"
#include "fcitx/inputcontextmanager.h"
#include "pthread.h"
#include "fcitx-utils/key.h"
#include "fcitx/event.h"
#include "fcitx-utils/eventdispatcher.h"



fcitx::InputContextManager *manager;
bool isrunning = false;
pthread_t loopt;
fcitx::Instance *inst;
fcitx::InputContextManager *im;
fcitx::InputContext *ic;
fcitx::Key key = fcitx::Key("a");
fcitx::Event *event;
fcitx::EventDispatcher *evD;



void* loop(void* data){

	while(isrunning){
		ic =im->lastFocusedInputContext();
		if(ic!=NULL){
			event = new fcitx::CommitStringEvent("test",ic);
		ic->forwardKey(key,false,2);
		evD->schedule(NULL);
		FCITX_INFO() << "sent key";
		}


		sleep(5);

	};
	return data;
}

SemaphoreEngine::SemaphoreEngine(fcitx::Instance *instance):instance_(instance){
	inst = instance_;
	im = &(instance_->inputContextManager());
	ic = im->lastFocusedInputContext();
	evD = &(instance_->eventDispatcher());
		isrunning=true;
		char threadname[] = "loop thread";
		manager = new fcitx::InputContextManager();
		pthread_create(&loopt,NULL,loop,threadname);
		pthread_detach(loopt);
}

void SemaphoreEngine::keyEvent(const fcitx::InputMethodEntry& entry, fcitx::KeyEvent& keyEvent){
	FCITX_UNUSED(entry);
	FCITX_INFO() << keyEvent.key() << " isRelease=" << keyEvent.isRelease();
	
}


FCITX_ADDON_FACTORY(SemaphoreEngineFactory);
