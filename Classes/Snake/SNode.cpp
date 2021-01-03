#include "SNode.h"
#include "Component\Constant.h"
#include "Scene/PlayScene.h"
#include "Food/Food.h"

SNode* SNode::create(std::string filename, Color3B color)
{
	SNode* snode = new(std::nothrow)SNode;
	if (snode && snode->init(filename, color))
	{
		snode->autorelease();
		return snode;
	}
	CC_SAFE_DELETE(snode);
	return nullptr;
}

void SNode::move(float dt)
{
	if (!PlayScene::_snake)
		return;
	_pos = _pos->next();
	setPosition(_pos->val());

	setVisible(true);
	getPhysicsBody()->setEnabled(true);
}

void SNode::scheduleMove()
{
	schedule(CC_SCHEDULE_SELECTOR(SNode::move));
}

bool SNode::init(std::string filename, Color3B color)
{
	if (!initWithFile(filename))
		return false;
	_snake = nullptr;
	setTag(SNAKE_TAG);
	setColor(color);
	auto body = PhysicsBody::createCircle(getContentSize().width / 2, DEFAULT_MATERIAL);
	body->setRotationEnable(false);
	SET_BITMASK(body, SNAKE);
	addComponent(body);
	return true;
}

void SNode::updateVelocity(float dt)
{
	if (!PlayScene::_snake)
		return;
	auto body = getPhysicsBody();
	if (!body || body->getVelocity() == Vec2::ZERO)
		return;
	float begin_r = body->getVelocity().getAngle();
	float end_d = getRotation();
	Vec2 velocity = body->getVelocity();
	velocity.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(end_d) - begin_r);
	velocity.y = -velocity.y;
	body->setVelocity(velocity);
}

void SNode::setVLength(float dt)
{
	auto body = getPhysicsBody();
	if (!body)
		return;
	float length = SPEED[_snake->WSPressed + 1];
	Vec2 velocity = body->getVelocity();
	if (velocity.length() != 0)
		velocity.scale(length / velocity.length());
	else
	{
		velocity = Vec2(length, 0);
		velocity.rotate(Vec2(0, 0), CC_DEGREES_TO_RADIANS(getRotation()));
	}
	float l = velocity.length();
	body->setVelocity(velocity);
}

void SNode::updateRotation(float dt)
{
	if (!PlayScene::_snake)
		return;
	float r_d = getRotation();
	if (_snake->ADPressed == 0)
		return;
	setRotation(r_d + ROTATE_RATE * _snake->ADPressed);
	updateVelocity(dt);
	setVLength(dt);
}


void SNode::updatePath(float dt)
{
	if (!PlayScene::_snake)
		return;
	setInSide();
	_snake->_path.push_back(getPosition());
	_pos = (--(_snake->_path.end())).getNode();
	while (_snake->_path.size() - _snake->_nodes.size() * 10 > SNAKE_REMAIN_MAX)
	{
		_snake->_path.pop_front();
	}
}

void SNode::setInSide()
{
	float x = _position.x, y = _position.y;
	Size size = Director::getInstance()->getVisibleSize();
	while (x < 0)
		x += size.width;
	while (x > size.width)
		x -= size.width;
	while (y < 0)
		y += size.height;
	while (y > size.height)
		y -= size.height;
	setPosition(Vec2(x, y));
}

bool SNode::isOutside()
{
	float x = _position.x, y = _position.y;
	Size size = Director::getInstance()->getVisibleSize();
	return (x > size.width || x < 0 || y<0 || y>size.height);
}

void SNode::scheduleController()
{
	schedule(CC_SCHEDULE_SELECTOR(SNode::updateRotation));
	schedule(CC_SCHEDULE_SELECTOR(SNode::updatePath));
}

void SNode::updateAI(float dt)
{
	if (!PlayScene::_snake)
		return;
	if (rand() % 1)
		return;
	_snake->ADPressed = rand() % 3 - 1;		//-1µ½1
	_snake->setWS(rand() % 3 - 1);
}

void SNode::scheduleAI()
{
	schedule(CC_SCHEDULE_SELECTOR(SNode::updateAI), 0.2f, CC_REPEAT_FOREVER, 0.2f);
}

void SNode::addBack()
{
	SNode* tail;
	if (_snake == PlayScene::_snake)
		tail = SNode::create(MY_NODE_PATH, _snake->head()->getColor());
	else
		tail = SNode::create(NODE_PATH, _snake->head()->getColor());

	auto pos = _snake->_nodes.back()->_pos;
	tail->setLocalZOrder(_snake->_nodes.back()->getLocalZOrder() - 1);
	for (int i = 0; i < SNAKE_NODE_GAP; i++)
		pos = pos->prev();
	tail->_pos = pos;

	tail->setVisible(false);
	tail->getPhysicsBody()->setEnabled(false);

	_snake->push_back(tail);
	tail->Sprite::setPosition(pos->val());
	tail->scheduleMove();
}


bool SNode::isHead()
{
	return this == _snake->head();
}

void SNode::onExit()
{
	if (!PlayScene::_gameOver&&!PlayScene::_gamePause)
	{
		getPhysicsBody()->setEnabled(false);
		Food* food = Food::createWithSNode(this);
		Director::getInstance()->getRunningScene()->addChild(food);
	}
	Sprite::onExit();
}




