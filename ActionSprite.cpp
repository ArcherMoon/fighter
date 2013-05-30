#include "ActionSprite.h"


using namespace cocos2d;

ActionSprite::ActionSprite()
:idleAction(NULL)
,attackAction(NULL)
,walkAction(NULL)
,_actionState(ActionStateNone)
{
}

ActionSprite::~ActionSprite()
{
}

void ActionSprite::idle()
{
    if (ActionStateIdle != _actionState)
    {
        this->stopAllActions();
        this->runAction(idleAction);
        _velocity = CCPointZero;
        _actionState = ActionStateIdle;
    }

    return;
}

void ActionSprite::attack()
{
    if (ActionStateIdle == _actionState ||
        ActionStateAttack == _actionState ||
        ActionStateWalk == _actionState)
    {
        this->stopAllActions();
        this->runAction(attackAction);
        _actionState = ActionStateAttack;
    }

    return;
}

void ActionSprite::walkWithDirection(CCPoint direction)
{
    /* 没有开始移动则执行移动动画，已经移动则计算速度 */
    if (ActionStateIdle == _actionState)
    {
        this->stopAllActions();
        this->runAction(walkAction);
        _actionState = ActionStateWalk;
    }

     if (ActionStateWalk == _actionState)
    {
        _velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
        /* 设置角色的朝向 */
        if (_velocity.x >= 0)
        {
            this->setScaleX(1.0);
        }
        else
        {
            this->setScaleX(-1.0);
        }
    }

     return;
}

void ActionSprite::knockout()
{
    this->stopAllActions();
    this->runAction(knockedOutAction);
    _hitPoints = 0;
    _actionState = ActionStateKnockedOut;
    return;
}

void ActionSprite::hurtWithDamage(float damage)
{
    if (ActionStateKnockedOut != _actionState)
    {
        this->stopAllActions();
        this->runAction(hurtAction);
        _actionState = ActionStateHurt;
        _hitPoints -= damage;

        if (_hitPoints <= 0 )
        {
            this->knockout();
        }
    }
    return;
}

void ActionSprite::update(float delta)
{
    _desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, delta));

    return;
}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), origin);
    boundingBox.actual.size = size;
    
    return boundingBox;
}

void ActionSprite::transformBoxes()
{
    _hitBox.actual.origin = ccpAdd(this->getPosition(), _hitBox.original.origin);
    /* 目前只考虑翻转，不考虑缩放 */
    float x;
    if (-1 == this->getScaleX())
    {
        x = _attackBox.original.origin.x - _hitBox.original.size.width - _attackBox.original.size.width;
    }
    else 
    {
        x = _attackBox.original.origin.x;
    }
    _attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(x, _attackBox.original.origin.y));
    return;
}

void ActionSprite::setPosition(CCPoint position)
{
    CCNode::setPosition(position);
    /* 更新碰撞盒位置 */
    this->transformBoxes();

    return;
}