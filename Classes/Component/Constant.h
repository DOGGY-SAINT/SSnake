#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define FOOD_PATH				"picture/circle_10_white.png"
#define MY_HEAD_PATH			"picture/myhead.png"
#define HEAD_PATH				"picture/head.png"
#define MY_NODE_PATH			"picture/my_circle_20.png"
#define NODE_PATH				"picture/circle_20.png"
#define START_BUTTON1_PATH		"picture/startbutton1.png"
#define START_BUTTON2_PATH		"picture/startbutton2.png"
#define HOME_BUTTON1_PATH		"picture/homebutton1.png"
#define HOME_BUTTON2_PATH		"picture/homebutton2.png"
#define MUSIC_ON_BUTTON_PATH	"picture/musicOn.png"
#define MUSIC_OFF_BUTTON_PATH	"picture/musicOff.png"
#define PAUSE_BUTTON1_PATH		"picture/pausebutton1.png"
#define PAUSE_BUTTON2_PATH		"picture/pausebutton2.png"
#define START_SCENE_PATH		"picture/startscene.png"

#define FAIL_MUSIC_PATH			"music/fail.mp3"
#define PLAYING_MUSIC_PATH		"music/playing.mp3"
#define START_MUSIC_PATH		"music/start.mp3"

#define VOLUME		1.0f


#define SET_BITMASK(bodyName,maskName)\
bodyName->setCategoryBitmask(maskName##_CATEGORY);\
bodyName->setContactTestBitmask(maskName##_CONTACT);\
bodyName->setCollisionBitmask(maskName##_COLLISION);\

//无黑色
#define RAND_CCC3()\
Color3B(rand()%251+5,rand()%251+5,rand()%251+5)

#define SNAKE_TAG	1
#define FOOD_TAG	2
#define WALL_TAG	3

//category&contactTest!=0 事件发送
//category&collision!=0 碰撞发生

#define SNAKE_CATEGORY	0b0001
#define FOOD_CATEGORY	0b0010
#define WALL_CATEGORY	0b0100

#define SNAKE_CONTACT	0b0011
#define FOOD_CONTACT	0b0001
#define WALL_CONTACT	0b0000

#define SNAKE_COLLISION	0b0100
#define FOOD_COLLISION	0b0000
#define WALL_COLLISION	0b0001


const int SPEED[3] = { 60,90,120 };	//pixel per second

#define ROTATE_RATE	3		//degree per second

#define SNAKE_NODE_GAP		8			//节点间隔的点数
#define SNAKE_REMAIN_MAX	100			//节点末尾额外保留的点数
#define SNAKE_ADD_COEFFICIENT	2		//蛇到当前长度*系数倍才会变长
//#define SNAKE_DEFAULT_COLOR		ccc3(255, 192, 203)			//粉色
#define SNAKE_DEFAULT_COLOR		Color3B(255, 255, 255)			//白色

#define DEFAULT_MATERIAL	PhysicsMaterial(0.0f, 1.0f, 2.0f)





#endif