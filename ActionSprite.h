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
    CC_SYNTHESIZE(cocos2d::CCAction *, walkAction, WalkAction);   
    

    /* action methods */
    void idle();        /* 空闲 */
    void attack();
    void walkWithDirection(cocos2d::CCPoint direction);

    /* 用于衡量sprite的实际大小 */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);

private:

};
    
#endif
