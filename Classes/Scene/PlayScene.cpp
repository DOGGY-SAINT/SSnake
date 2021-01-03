#include "PlayScene.h"
#include "Component/Constant.h"
#include"HelloWorldScene.h"
#include "Food/Food.h"
#include"PauseScene.h"
#include "AudioEngine.h"
#include"AppDelegate.h"


Snake* PlayScene::_snake = nullptr;
int PlayScene::WSPressed = 0;
int PlayScene::ADPressed = 0;
bool PlayScene::_gameOver = false;
bool PlayScene::_gamePause=false;
int PlayScene::_snakeNum=0;

USING_NS_CC;

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
	srand(time(0));
	if (!initWithPhysics())
	{
		return false;
	}

	_snake = nullptr;
	_gameOver = false;
	_gamePause = false;
	_snakeNum = 0;

	_snake = Snake::createWithPos(Vec2(100, 100));
	_snake->scheduleController();
	addChild(_snake);
	addChild(_snake->head());

	/*_snake.addNode();*/
	if (!PlayScene::_snake)
		return false;
	if (AppDelegate::_musicOn)
	{
		AudioEngine::stopAll();
		AudioEngine::play2d(PLAYING_MUSIC_PATH, true, VOLUME);
	}


	initController();
	initKeyBoardListener();
	initScheduler();
	initContactListener();
	initScoreLable();
	initPhysicsWorld();
	initMenu();
	
	return true;
}

void PlayScene::initKeyBoardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void PlayScene::initScheduler()
{
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::gameEnd));
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateFood), 0.3f, CC_REPEAT_FOREVER, 0.1f);
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateScore));
	schedule(CC_SCHEDULE_SELECTOR(PlayScene::addSnake),1.0f,CC_REPEAT_FOREVER,1.0f);
}

void PlayScene::initContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlayScene::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void PlayScene::initScoreLable()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithTTF("Score:0", "fonts/arial.ttf", 20);
	label->setLocalZOrder(2);
	//label->setZOrder(2);
	label->setAnchorPoint(Vec2::ZERO);
	label->setTextColor(Color4B(255, 255, 255, 255));
	label->setName("ScoreLabel");
	this->addChild(label);
	label->setPosition(Vec2(20, visibleSize.height - 40));

}

void PlayScene::initPhysicsWorld()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto world = this->getPhysicsWorld();
	/*world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);*/
	world->setGravity(Vec2::ZERO);
	auto node = Node::create();
	node->setPosition(visibleSize / 2);
	auto body = PhysicsBody::createEdgeBox(visibleSize,PhysicsMaterial(5.0,0,0));
	SET_BITMASK(body, WALL);
	node->addComponent(body);
	/*this->addChild(node);*/
}

void PlayScene::initController()
{
	WSPressed = 0;
	ADPressed = 0;
	_snake->setWS(WSPressed);
	_snake->ADPressed = ADPressed;
}

void PlayScene::initMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//ÆÁÄ»ÖÐÐÄ
	auto closeItem = MenuItemImage::create(
		PAUSE_BUTTON1_PATH,
		PAUSE_BUTTON2_PATH,
		CC_CALLBACK_1(PlayScene::pauseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
	}
	else
	{
		closeItem->setAnchorPoint(Vec2(0.5f, 0.5f));
		auto scaleTo1 = ScaleTo::create(0.5f, 0.5f);
		closeItem->runAction(scaleTo1);
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = visibleSize.height - closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}


void PlayScene::pauseCallback(Ref* pSender)
{
	initController();
	_gamePause = true;
	Director::getInstance()->pushScene(PauseScene::createScene());
}

void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (WSPressed > 1)
		WSPressed = 1;
	if (WSPressed < -1)
		WSPressed = -1;
	if (ADPressed > 1)
		ADPressed = 1;
	if (ADPressed < -1)
		ADPressed = -1;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		WSPressed += 1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		ADPressed -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		WSPressed -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		ADPressed += 1;
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		pauseCallback(nullptr);
		return;
		break;
	}
	if (!PlayScene::_snake)
		return ;
 	_snake->setWS(WSPressed);
	_snake->ADPressed = ADPressed;
}

void PlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		WSPressed -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		ADPressed += 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		WSPressed += 1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		ADPressed -= 1;
		break;
	}
	if (!PlayScene::_snake)
		return ;
	_snake->setWS(WSPressed);
	_snake->ADPressed = ADPressed;
}

void PlayScene::updateFood(float dt)
{
	auto food = Food::create(FOOD_PATH);
	/*auto food = Food::createWithSNode(_snake->head());*/
	addChild(food);
}

void PlayScene::updateScore(float dt)
{
	auto label = dynamic_cast<Label*>(getChildByName("ScoreLabel"));
	label->setString("Score:" + std::to_string(_snake->_score));
}

void PlayScene::addSnake(float dt)
{
	if (_snakeNum >= 15)
		return;
	Snake* sn = Snake::createRand();
	sn->scheduleAI();
	sn->scheduleController();
	addChild(sn);
	addChild(sn->head());
	_snakeNum++;
}

bool PlayScene::onContactBegin(PhysicsContact& contact)
{
	SNode* SNode1 = nullptr, * SNode2 = nullptr;
	Food* Food1 = nullptr, * Food2 = nullptr;
	if (!contact.getShapeA() || !contact.getShapeB())
		return false;
	auto Sprite1 = dynamic_cast<Sprite*>(contact.getShapeA()->getBody()->getNode());
	auto Sprite2 = dynamic_cast<Sprite*>(contact.getShapeB()->getBody()->getNode());
	if (!Sprite1 || !Sprite2)
		return false;
	if (Sprite1->getTag() == SNAKE_TAG)
		SNode1 = dynamic_cast<SNode*>(Sprite1);
	else
		Food1 = dynamic_cast<Food*>(Sprite1);
	if (Sprite2->getTag() == SNAKE_TAG)
		SNode2 = dynamic_cast<SNode*>(Sprite2);
	else
		Food2 = dynamic_cast<Food*>(Sprite2);
	if (SNode1 && !SNode2)
	{
		SNode1->_snake->eatFood(Food2->getScore());
		Sprite2->removeFromParentAndCleanup(true);
	}
	else if (!SNode1 && SNode2)
	{
		SNode2->_snake->eatFood(Food1->getScore());
		Sprite1->removeFromParentAndCleanup(true);
	}
	else if (SNode1->_snake != SNode2->_snake)
	{
		if (SNode1->isHead())
			SNode1->_snake->removeAll();
		if (SNode2&&SNode2->isHead())
			SNode2->_snake->removeAll();
	}
	return false;
}

bool PlayScene::onContactSeparate(PhysicsContact& contact)
{
	return false;
}

void PlayScene::gameEnd(float dt)
{
	if (!_gameOver)
		return;
	_snake = nullptr;
	removeAllChildren();
	unscheduleAllCallbacks();
	
	if (AppDelegate::_musicOn)
	{
		AudioEngine::stopAll();
		AudioEngine::play2d(FAIL_MUSIC_PATH, false ,VOLUME);
	}
	Director::getInstance()->replaceScene(TransitionFade::create(5.0f, HelloWorld::create(5.0f)));
}
