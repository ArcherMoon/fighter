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

    /* ����״̬ */
    CC_SYNTHESIZE(ActionState,_actionState, ActionState);

    /* attributes */
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);

    /* movement */
    CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);
    

    /* ���ں���sprite��ʵ�ʴ�С */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);
    CC_SYNTHESIZE( float, centerToBottom, CenterToBottom);

private:

};
    
#endif
