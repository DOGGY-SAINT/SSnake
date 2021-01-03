#include "HelloWorldScene.h"
#include "PlayScene.h"
#include "Component/Constant.h"
#include "AppDelegate.h"
#include"AudioEngine.h"

USING_NS_CC;


HelloWorld* HelloWorld::create(float delay)
{
	HelloWorld* scene = new(std::nothrow)HelloWorld;
	if (scene && scene->init(delay))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return nullptr;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init(float delay)
{
	if (!Scene::init())
	{
		return false;
	}
	schedule(CC_SCHEDULE_SELECTOR(HelloWorld::playBackgroundMusic),0,0,delay);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		START_BUTTON1_PATH,
		START_BUTTON2_PATH,
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'startbutton2.png' and 'button2.1.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2 + 110;
		closeItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);


	auto sprite0 = Sprite::create(START_SCENE_PATH);
	if (sprite0 == nullptr)
	{
		problemLoading(START_SCENE_PATH);
	}
	else
	{

		sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


		this->addChild(sprite0, 1);
	}
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayScene::create()));
}

void HelloWorld::playBackgroundMusic(float dt)
{
	if (AppDelegate::_musicOn)
	{
		AudioEngine::stopAll();
		AudioEngine::play2d(START_MUSIC_PATH,true,VOLUME);
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if(keyCode==EventKeyboard::KeyCode::KEY_ESCAPE)
		Director::getInstance()->popScene();
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}