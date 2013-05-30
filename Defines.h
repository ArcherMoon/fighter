#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "cocos2d.h"

#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define RANDOM_RANGE(low, high) (rand()%((high) - (low) + 1) + (low))

typedef enum _ActionState
{
    ActionStateNone = 0,
    ActionStateIdle,
    ActionStateWalk,
    ActionStateAttack,
    ActionStateHurt,
    ActionStateKnockedOut,
    ActionStateMax
}ActionState;

typedef struct _boundingBox
{
    cocos2d::CCRect actual;
    cocos2d::CCRect original;
}BoundingBox;

#endif
