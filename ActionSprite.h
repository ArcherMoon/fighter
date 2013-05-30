#ifndef __ACTION_SPRITE_H__
#define __ACTION_SPRITE_H__

#include "cocos2d.h"
#include "Defines.h"

class ActionSprite : public cocos2d::CCSprite
{
public:
    ActionSprite();
    ~ActionSprite();

    virtual void update(float delta);
    
    /* actions */
    CC_SYNTHESIZE(cocos2d::CCAction *, idleAction, IdleAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, attackAction, AttackAction);   
    CC_SYNTHESIZE(cocos2d::CCAction *, walkAction, WalkAction);   
    

    /* action methods */
    void idle();        /* ���� */
    void attack();
    void walkWithDirection(cocos2d::CCPoint direction);
    void hurtWithDamage(float damage);

    /* ����״̬ */
    CC_SYNTHESIZE(ActionState,_actionState, ActionState);

    /* attributes */
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    CC_SYNTHESIZE(float, _hitPoints, HitPoints);
    CC_SYNTHESIZE(float, _damage,Damage);

    /* movement */
    CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);
    

    /* ���ں���sprite��ʵ�ʴ�С */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);
    CC_SYNTHESIZE( float, centerToBottom, CenterToBottom);

    /* ���ڽ�����ײ��� */
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, _hitBox, HitBox);

private:

};
    
#endif
