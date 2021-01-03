#include "Snake.h"
#include "SNode.h"
#include "Component/Constant.h"
#include "Food/Food.h"
#include "Scene/PlayScene.h"

Snake* Snake::createWithPos(Vec2 pos)
{
	Snake* snake = new(std::nothrow)Snake;
	if (snake && snake->init(pos))
	{
		snake->autorelease();
		return snake;
	}
	CC_SAFE_DELETE(snake);
	return nullptr;
}

Snake* Snake::createRand()
{
	Snake* snake = new(std::nothrow)Snake;
	if (snake && snake->randInit())
	{
		snake->autorelease();
		return snake;
	}
	CC_SAFE_DELETE(snake);
	return nullptr;
}

bool Snake::init(Vec2 pos,Color3B color)
{
	if (!Node::create())
		return false;
	_cnt = 0;
	_addingCnt = 0;
	_score = 1;
	ADPressed = 0;
	WSPressed = 0;
	SNode* head;
	if(PlayScene::_snake==nullptr)
		head = SNode::create(MY_HEAD_PATH,color);
	else
		head = SNode::create(HEAD_PATH, color);
	
	head->_snake = this;
	head->setPosition(pos);
	head->getPhysicsBody()->setVelocity(Vec2(SPEED[1],0));
	_path.push_back(pos);
	head->_pos = _path.begin().getNode();
	_nodes.push_back(head);
	return true;
}

bool Snake::randInit()
{
	Size size = Director::getInstance()->getVisibleSize();
	auto pos=Vec2(CCRANDOM_0_1() * size.width, CCRANDOM_0_1() * size.height);
	while(pos.distance(PlayScene::_snake->getPosition())<100)
		pos = Vec2(CCRANDOM_0_1() * size.width, CCRANDOM_0_1() * size.height);
	return init(pos,RAND_CCC3());
}

void Snake::setSpeed(int wspressed)
{
	head()->setVLength(SPEED[wspressed + 1]);
}

void Snake::push_back(SNode* snode)
{
	_nodes.push_back(snode);
	snode->_snake = this;
	head()->getParent()->addChild(snode);
	_addingCnt--;
}

void Snake::addNode()
{
	_addingCnt++;
	_nodes.back()->addBack();
}

void Snake::eatFood(int score)
{
	_score+=score;
	_cnt+=score;
	while (_cnt >= _nodes.size() * SNAKE_ADD_COEFFICIENT)
	{
		_cnt -= _nodes.size() * SNAKE_ADD_COEFFICIENT;
		addNode();
	}
}

void Snake::scheduleController()
{
	head()->scheduleController();
}

void Snake::scheduleAI()
{
	head()->scheduleAI();
}

void Snake::setWS(int WSPressed)
{
	this->WSPressed=WSPressed;
	head()->setVLength(0);
}

void Snake::removeAll()
{
	PlayScene::_snakeNum--;
	for (SNode* node : _nodes)
	{
		node->removeFromParent();
	}
	_nodes.clear();	
	if (this == PlayScene::_snake)
		dynamic_cast<PlayScene*>(Director::getInstance()->getRunningScene())->_gameOver = true;
	this->removeFromParent();
	
}

