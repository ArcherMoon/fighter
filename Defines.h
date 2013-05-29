#ifndef __DEFINES_H__
#define __DEFINES_H__

#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define RANDOM_RANGE(low, high) (rand()%((high) - (low) + 1) + (low))

typedef enum _ActionState
{
    ActionStateNone = 0,
    ActionStateIdle,
    ActionStateWalk,
    ActionStateAttack,
    ActionStateMax
}ActionState;


#endif
