#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "cocos2d.h"
#include "Component/MyList.h"
#include "Component/Constant.h"

class SNode;
class PlayScene;
class Food;

USING_NS_CC;

class Snake:public Node
{
	friend class SNode;
	friend class PlayScene;
	friend class Food;
private:
	int _cnt;
	long _score;
	int _addingCnt;
	int ADPressed;
	int WSPressed;
	MyList<Vec2> _path;		//新的在后
	MyList<SNode*> _nodes;

public:
	static Snake* createWithPos(Vec2 pos);

	static Snake* createRand();

	bool init(Vec2 pos, Color3B color = SNAKE_DEFAULT_COLOR);

	bool randInit();

	void setSpeed(int wspressed);

	SNode* head()
	{
		if (_nodes.length() <= 0)
			return nullptr;
		return _nodes.front();
	}

	void push_back(SNode* snode);

	void addNode();
	
	void eatFood(int score);

	void scheduleController();

	void scheduleAI();

	void setWS(int WSPressed);

	void removeAll();

};


#endif