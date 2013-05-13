#include "Hero.h"

using namespace cocos2d;


bool Hero::init()
{
    /* �þ���֡��ʼ��������ʾ��ͼƬ */
    if (!initWithSpriteFrameName("hero_idle_00.png"))
    {
        return false;
    }

     /* �������еĶ��� */
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



