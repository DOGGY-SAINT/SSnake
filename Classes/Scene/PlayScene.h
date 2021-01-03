#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Snake/SNode.h"
#include "Snake/Snake.h"

USING_NS_CC;

class PlayScene : public cocos2d::Scene
{ 
public:
    static Snake* _snake;
    static int WSPressed;
    static int ADPressed;
    static bool _gameOver;
    static bool _gamePause;
    static int _snakeNum;

    static cocos2d::Scene* createScene();

    virtual bool init();

    void initKeyBoardListener();

    void initScheduler();

    void initContactListener();

    void initScoreLable();

    void initPhysicsWorld();

    void initController();

    void initMenu();

    void pauseCallback(cocos2d::Ref* pSender);

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void updateFood(float dt);

    void updateScore(float dt);

    void addSnake(float dt);

    bool onContactBegin(PhysicsContact& contact);

    bool onContactSeparate(PhysicsContact& contact);

    void gameEnd(float dt);

    CREATE_FUNC(PlayScene);
};





#endif // __PLAY_SCENE_H__
