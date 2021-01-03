#ifndef _PAUSE_SCENE_H_
#define _PAUSE_SCENE_H_
#include"cocos2d.h"
#include"AudioEngine.h"


class PauseScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void initKeyBoardListener();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// a selector callback
	void continueCallback(cocos2d::Ref* pSender);
	

	void goBackHomeCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(PauseScene);


};



#endif