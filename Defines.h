#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "cocos2d.h"

#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define CENTER ccp(SCREEN.width/2, SCREEN.height/2) 
#define CURTIME getCurMillSecond()

#ifndef UINT64_C
#define UINT64_C(val) __CONCAT(val,ULL)
#endif
#define FRANDOM ((float)rand()/UINT64_C(0x100000000))
#define FRANDOM_RANGE(low, high) ((high - low)*FRANDOM + low)
#define RANDOM_RANGE(low, high) (rand()%((high) - (low) + 1) + (low))

/* 从getCurrentMillSecond拷贝，函数前要加inline，否则 multiple definition */
inline unsigned long getCurMillSecond() 
{
	long lLastTime;
	struct timeval stCurrentTime;

	gettimeofday(&stCurrentTime,NULL);
	lLastTime = stCurrentTime.tv_sec*1000+stCurrentTime.tv_usec*0.001; //millseconds
	CCLOG("time is %ld\n", lLastTime);
	return (unsigned long)lLastTime;
};

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
    cocos2d::CCRect actual;     /* 绝对位置 */
    cocos2d::CCRect original;   /* 相对于精灵位置 */
}BoundingBox;

#endif
