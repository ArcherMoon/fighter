#include "Robot.h"

using namespace cocos2d;

Robot::Robot(void)
{
}

Robot::~Robot(void)
{
}

bool Robot::init()
{
    /* �þ���֡��ʼ��������ʾ��ͼƬ */
    if (!initWithSpriteFrameName("robot_idle_00.png"))
    {
        return false;
    }

    /* �������еĶ���*/
    CCAnimation *idleAnimation = CCAnimation::create();
    for (int i = 0; i<5; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "robot_idle_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        idleAnimation->addSpriteFrame(frame);
    }
    idleAnimation->setDelayPerUnit(1.0/12.0);
    idleAnimation->setRestoreOriginalFrame(true);
    idleAction = CCRepeatForever::create(CCAnimate::create(idleAnimation));
    /* һ��Ҫ�����ü����������crash!! */
    idleAction->retain();
    
     /* ������������ */
    CCAnimation *attackAnimation = CCAnimation::create();
    for (int i= 0; i<5; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "robot_attack_%02d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        attackAnimation->addSpriteFrame(frame);
    }
    attackAnimation->setDelayPerUnit(1.0/24.0);
    attackAnimation->setRestoreOriginalFrame(true);
    attackAction = CCSequence::create(
        CCAnimate::create(attackAnimation),
        CCCallFunc::create(this, callfunc_selector(Robot::idle)),
        NULL);
    attackAction->retain();

    /* �����ƶ��Ķ��� */
    CCAnimation *walkAnimation = CCAnimation::create();
    for (int i = 0; i<6; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "robot_walk_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        walkAnimation->addSpriteFrame(frame);
    }
    walkAnimation->setDelayPerUnit(1.0/12.0);
    walkAnimation->setRestoreOriginalFrame(true);
    walkAction = CCRepeatForever::create(CCAnimate::create(walkAnimation));
    /* һ��Ҫ�����ü����������crash!! */
    walkAction->retain();

    this->centerToSides = 29.0;
    this->centerToBottom = 39.0;
    this->_walkSpeed = 80.0;
    this->_hitPoints = 100.0f;
    this->_damage = 10.0f;

    return true;
}


