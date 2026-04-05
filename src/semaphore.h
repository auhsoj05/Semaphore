#ifndef _FCITX5_SEMAPHORE_SEMAPHORE_H
#define _FCITX5_SEMAPHORE_SEMAPHORE_H

#include <fcitx/inputmethodengine.h>
#include <fcitx/addonfactory.h>
#include <fcitx/instance.h>
#include <fcitx/addonmanager.h>

class SemaphoreEngine;

class SemaphoreEngine : public fcitx::InputMethodEngineV2{
	public:
	SemaphoreEngine(fcitx::Instance *instance);
	void keyEvent(const fcitx::InputMethodEntry &entry, fcitx::KeyEvent &keyEvent) override;
	auto instance() const {return instance_;}
	private:
		fcitx::Instance *instance_;

};

class SemaphoreEngineFactory : public fcitx::AddonFactory {
	fcitx::AddonInstance *create(fcitx::AddonManager  *manager) override{
		FCITX_UNUSED(manager);
		return new SemaphoreEngine(manager->instance());
	}
};
#endif
