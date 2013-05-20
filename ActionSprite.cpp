#include "ActionSprite.h"


using namespace cocos2d;

ActionSprite::ActionSprite()
:idleAction(NULL)
,attackAction(NULL)
,walkAction(NULL)
{
}

ActionSprite::~ActionSprite()
{
}

void ActionSprite::idle()
{
    CCLOG("---idle before stopAllActions-----idle %d,attack %d", idleAction->retainCount(), attackAction->retainCount());
    this->stopAllActions();
    CCLOG("---idle before runAction-----%d,%d", idleAction->retainCount(), attackAction->retainCount());
    this->runAction(idleAction);
    CCLOG("---idle after runAction-----%d,%d", idleAction->retainCount(), attackAction->retainCount());
    _velocity = CCPointZero;

    return;
}

void ActionSprite::attack()
{
    CCLOG("---attack before stopAllActions-----idle %d,attack %d", idleAction->retainCount(), attackAction->retainCount());
    this->stopAllActions();
    CCLOG("---attack before runAction-----%d,%d", idleAction->retainCount(), attackAction->retainCount());
    this->runAction(attackAction);
    CCLOG("---attack before runAction-----%d,%d", idleAction->retainCount(), attackAction->retainCount());

    return;
}

void ActionSprite::walkWithDirection(CCPoint direction)
{
    this->stopAllActions();
    this->runAction(walkAction);

    _velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
}

void ActionSprite::update(float delta)
{
    _desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, delta));

    return;
}