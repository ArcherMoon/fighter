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
    void idle();        /* 空闲 */
    void attack();
    void walkWithDirection(cocos2d::CCPoint direction);
    void hurtWithDamage(float damage);

    /* 人物状态 */
    CC_SYNTHESIZE(ActionState,_actionState, ActionState);

    /* attributes */
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    CC_SYNTHESIZE(float, _hitPoints, HitPoints);
    CC_SYNTHESIZE(float, _damage,Damage);

    /* movement */
    CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);
    

    /* 用于衡量sprite的实际大小 */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);
    CC_SYNTHESIZE( float, centerToBottom, CenterToBottom);

    /* 用于进行碰撞检测 */
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, _hitBox, HitBox);

private:

};
    
#endif
