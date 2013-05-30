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
    /* û�п�ʼ�ƶ���ִ���ƶ��������Ѿ��ƶ�������ٶ� */
    if (ActionStateIdle == _actionState)
    {
        this->stopAllActions();
        this->runAction(walkAction);
        _actionState = ActionStateWalk;
    }

     if (ActionStateWalk == _actionState)
    {
        _velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
        /* ���ý�ɫ�ĳ��� */
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

void ActionSprite::hurtWithDamage(float damage)
{
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
    /* Ŀǰֻ���Ƿ�ת������������ */
    if (-1 == this->getScaleX())
    {
        _attackBox.actual.origin.x -= (_hitBox.actual.size.width + _attackBox.actual.size.width);
    }
    _attackBox.actual.origin = ccpAdd(this->getPosition(), _attackBox.original.origin);
    return;
}

void ActionSprite::setPosition(CCPoint position)
{
    CCNode::setPosition(position);
    /* ������ײ��λ�� */
    this->transformBoxes();

    return;
}