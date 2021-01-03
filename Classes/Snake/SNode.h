#ifndef __S_NODE_H__
#define __S_NODE_H__

#include "cocos2d.h"
#include "Component/MyList.h"

class Snake;
class PlayScene;
class Food;

USING_NS_CC;

class SNode :public cocos2d::Sprite
{
	friend class Snake;
	friend class PlayScene;
	friend class Food;
private:
	CC_SYNTHESIZE(Snake*,_snake,Snake);
	MyListNode<Vec2>* _pos;
public:
	static SNode* create(std::string filename,Color3B color);

	void move(float dt);

	void scheduleMove();

	bool init(std::string filename, Color3B color);

	void updateVelocity(float dt);

	void setVLength(float dt);

	void updateRotation(float dt);

	void updatePath(float dt);

	/*void update*/

	void setInSide();

	bool isOutside();

	void scheduleController();

	void updateAI(float dt);

	void scheduleAI();

	void addBack();

	bool isHead();

	virtual void onExit();

};







#endif