#include "Hero.h"

using namespace cocos2d;


bool Hero::init()
{
    /* 用精灵帧初始化设置显示的图片 */
    if (!initWithSpriteFrameName("hero_idle_00.png"))
    {
        return false;
    }

     /* 创建空闲的动作 */
     CCArray *idleFrames = CCArray::createWithCapacity(6);
     for (int i=0; i<6; ++i)
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_idle_%02d.png", i)->getCString());
        idleFrames->addObject(frame);
    }
     CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, 1.0/12.0);
     idleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));

     this->centerToSides = 39.0;

    return true;
}



