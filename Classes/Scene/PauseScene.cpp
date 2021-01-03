#include "PauseScene.h"
#include "AudioEngine.h"
#include "PlayScene.h"
#include "HelloWorldScene.h"
#include"Component/Constant.h"
#include"AppDelegate.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	return PauseScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	///////////////
	auto musicOnSpr = Sprite::create(MUSIC_ON_BUTTON_PATH);
	auto musicOffSpr = Sprite::create(MUSIC_OFF_BUTTON_PATH);
	auto musicOn = MenuItemSprite::create(musicOnSpr, musicOnSpr);
	auto musicOff = MenuItemSprite::create(musicOffSpr, musicOffSpr);
	auto musicButton = MenuItemToggle::createWithCallback([](Ref* sender) {
		if (AppDelegate::_musicOn == 1)
		{
			AppDelegate::_musicOn = 0;
			AudioEngine::stopAll();
		}
		else
		{
			AppDelegate::_musicOn = 1;
			AudioEngine::play2d(PLAYING_MUSIC_PATH, true, VOLUME);
		}
	},
		musicOn, musicOff, NULL);
	musicButton->setPosition(Vec2((visibleSize.width / 2) - 660, 14));
	auto menu2 = Menu::create(musicButton, NULL);
	this->addChild(menu2, 1);
	/////////////////////////
	auto goBackHome = MenuItemImage::create(
		HOME_BUTTON1_PATH,
		HOME_BUTTON2_PATH,
		CC_CALLBACK_1(PauseScene::goBackHomeCallback,this));
	goBackHome->setPosition(Vec2((visibleSize.width / 2) - 365, 15));
	auto menu3 = Menu::create(goBackHome, NULL);
	this->addChild(menu3, 1);
	////////////////
	auto closeItem = MenuItemImage::create(
		START_BUTTON1_PATH,
		START_BUTTON2_PATH,
		CC_CALLBACK_1(PauseScene::continueCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'picture/interface/startbutton2.png' and 'picture/interface/button2.1.jpg'");
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2 + 15;
		closeItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	initKeyBoardListener();
	return true;
}

void PauseScene::initKeyBoardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PauseScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void PauseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		continueCallback(nullptr);
}

void PauseScene::continueCallback(Ref* pSender)
{
	PlayScene::_gamePause = false;
	Director::getInstance()->popScene();
}

void PauseScene::goBackHomeCallback(cocos2d::Ref* pSender)
{
	PlayScene::_gamePause = false;
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(HelloWorld::create());
}
