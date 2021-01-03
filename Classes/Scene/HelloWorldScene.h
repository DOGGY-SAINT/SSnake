#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:

	static HelloWorld* create(float delay=0);

	bool init(float delay);

	void menuCloseCallback(cocos2d::Ref* pSender);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void playBackgroundMusic(float dt);
};

#endif // __HELLOWORLD_SCENE_H__
