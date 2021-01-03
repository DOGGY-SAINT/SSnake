#include"Food.h"
#include"Component/Constant.h"
#include "Snake/SNode.h"
#include"Snake/Snake.h"

Food* Food::createWithSNode(SNode* sn)
{
	Food* food = new(std::nothrow)Food;
	if (food && food->initWithSNode(sn))
	{
		food->autorelease();
		return food;
	}
	CC_SAFE_DELETE(food);
	return nullptr;
}

Food* Food::create(std::string fileName)
{
	Food* food = new(std::nothrow)Food;
	if (food && food->randInit(fileName))
	{
		food->autorelease();
		return food;
	}
	CC_SAFE_DELETE(food);
	return nullptr;
}

bool Food::randInit(std::string fileName)
{
	if (!initWithFile(fileName))
		return false;
	_score = rand() % 6 + 1;		//1µ½5
	setScale(pow(_score / 5.0f, 0.6));
	setColor(RAND_CCC3());
	Size size = Director::getInstance()->getVisibleSize();
	setPosition(Vec2(CCRANDOM_0_1() * size.width, CCRANDOM_0_1() * size.height));
	setPos(_position);

	setTag(FOOD_TAG);

	auto body = PhysicsBody::createCircle(getContentSize().width / 2, DEFAULT_MATERIAL);
	SET_BITMASK(body, FOOD);
	addComponent(body);
	return true;
}

bool Food::initWithSNode(SNode* sn)
{
	if (!initWithFile(FOOD_PATH))
		return false;
	auto body = PhysicsBody::createCircle(getContentSize().width / 2.0f, DEFAULT_MATERIAL);
	SET_BITMASK(body, FOOD);
	addComponent(body);
	_score = sn->_snake->_score / sn->_snake->_nodes.size()+2;
	setScale(pow(_score / 5.0f, 0.6));
	setColor(sn->getColor());

	setPosition(sn->getPosition() + Vec2(CCRANDOM_0_1(), CCRANDOM_0_1()));
	setPos(_position);

	setTag(FOOD_TAG);
	setVisible(false);
	schedule(CC_SCHEDULE_SELECTOR(Food::updatePos),0,0,0);

	return true;
}

void Food::updatePos(float dt)
{
	if (isVisible())
		return;
	setPosition(_pos);
	setVisible(true);
}


