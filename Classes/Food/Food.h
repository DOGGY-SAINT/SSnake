#include"Component/Constant.h"
#include"cocos2d.h"

class SNode;

USING_NS_CC;

class Food :public Sprite
{
private:
	CC_SYNTHESIZE(int,_score,Score);
	CC_SYNTHESIZE(Vec2, _pos, Pos);
public:
	static Food* createWithSNode(SNode* sn);

	static Food* create(std::string fileName);

	bool randInit(std::string fileName);

	bool initWithSNode(SNode* sn);

	void updatePos(float dt);
};