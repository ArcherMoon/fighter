#include "Hero.h"

using namespace cocos2d;

Hero::Hero(void)
{
}

Hero::~Hero(void)
{
}

bool Hero::init()
{
    /* �þ���֡��ʼ��������ʾ��ͼƬ */
    if (!initWithSpriteFrameName("hero_idle_00.png"))
    {
        return false;
    }

    /* �������еĶ���,���ַ��� */
    CCAnimation *idleAnimation = CCAnimation::create();
    for (int i = 0; i<6; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_idle_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        idleAnimation->addSpriteFrame(frame);
    }
    idleAnimation->setDelayPerUnit(1.0/12.0);
    idleAnimation->setRestoreOriginalFrame(true);
    idleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));
    /* һ��Ҫ�����ü����������crash!! */
    idleAction->retain();
    
     /* ������������ */
     CCArray * attackFrames = CCArray::createWithCapacity(3);
    for (int i=0; i<3; ++i)
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_attack_00_%02d.png", i)->getCString());
        attackFrames->addObject(frame);
    }
    CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, 1.0/24.0);
    attackAction = CCSequence::create(
        CCAnimate::create(attackAnimation),
        CCCallFunc::create(this, callfunc_selector(Hero::idle)),
        NULL);
    /* һ��Ҫ�����ü����������crash!! */
    attackAction->retain();

    /* �����ƶ��Ķ��� */
    CCAnimation *walkAnimation = CCAnimation::create();
    for (int i = 0; i<8; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_walk_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        walkAnimation->addSpriteFrame(frame);
    }
    walkAnimation->setDelayPerUnit(1.0/12.0);
    walkAnimation->setRestoreOriginalFrame(true);
    walkAction = CCRepeatForever::create(CCAnimate::create(walkAnimation));
    /* һ��Ҫ�����ü����������crash!! */
    walkAction->retain();

    CCLOG("---create actions-----idle %d,attack %d", idleAction->retainCount(), attackAction->retainCount());

     this->centerToSides = 39.0;
     this->_walkSpeed = 80.0;

    return true;
}


