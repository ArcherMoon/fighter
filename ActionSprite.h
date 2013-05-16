#ifndef __ACTION_SPRITE_H__
#define __ACTION_SPRITE_H__

#include "cocos2d.h"

class ActionSprite : public cocos2d::CCSprite
{
public:
    ActionSprite();
    ~ActionSprite();

    /* actions */
    CC_SYNTHESIZE(cocos2d::CCAction *, idleAction, IdleAction);
    CC_SYNTHESIZE(cocos2d::CCAction *, attackAction, AttackAction);   

    /* action methods */
    void idle();        /* ���� */
    void attack();

    /* ���ں���sprite��ʵ�ʴ�С */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);

private:

};
    
#endif
