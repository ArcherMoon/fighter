#include "Hero.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Hero::Hero(void)
{
}

Hero::~Hero(void)
{
}

bool Hero::init()
{
    /* 用精灵帧初始化设置显示的图片 */
    if (!initWithSpriteFrameName("hero_idle_00.png"))
    {
        return false;
    }

    /* 创建空闲的动作,两种方法 */
    CCAnimation *idleAnimation = CCAnimation::create();
    for (int i = 0; i<6; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_idle_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        idleAnimation->addSpriteFrame(frame);
    }
    idleAnimation->setDelayPerUnit(1.0/12.0);
    //idleAnimation->setRestoreOriginalFrame(true);
    this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));
    
     /* 创建攻击动作 */
     CCArray * attackFrames = CCArray::createWithCapacity(3);
    for (int i=0; i<3; ++i)
    {
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_attack_00_%02d.png", i)->getCString());
        attackFrames->addObject(frame);
    }
    CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, 1.0/24.0);
    this->setAttackAction(CCSequence::create(
                                    CCAnimate::create(attackAnimation),
                                    CCCallFunc::create(this, callfunc_selector(Hero::idle)),
                                     NULL));

    /* 创建移动的动作 */
    CCAnimation *walkAnimation = CCAnimation::create();
    for (int i = 0; i<8; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_walk_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        walkAnimation->addSpriteFrame(frame);
    }
    walkAnimation->setDelayPerUnit(1.0/12.0);
    //walkAnimation->setRestoreOriginalFrame(true);
    this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));

    /* 创建受伤的动作 */
    CCAnimation *hurtAnimation = CCAnimation::create();
    for (int i = 0; i<3; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_hurt_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        hurtAnimation->addSpriteFrame(frame);
    }
    hurtAnimation->setDelayPerUnit(1.0/12.0);
    //hurtAnimation->setRestoreOriginalFrame(true);
    this->setHurtAction(CCSequence::create(
                                    CCAnimate::create(hurtAnimation),
                                    CCCallFunc::create(this, callfunc_selector(Hero::idle)),
                                    NULL));

    /* 创建死亡的动作 */
    CCAnimation *knockoutAnimation = CCAnimation::create();
    for (int i = 0; i<5; ++i)
    {
        char szName[128] = {0};
        sprintf(szName, "hero_knockout_%02d.png", i);
        CCSpriteFrame *frame =  CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);
        knockoutAnimation->addSpriteFrame(frame);
    }
    knockoutAnimation->setDelayPerUnit(1.0/12.0);
    //knockoutAnimation->setRestoreOriginalFrame(true);
    this->setKnockedOutAction(CCSequence::create(
                                                CCAnimate::create(knockoutAnimation),
                                                CCBlink::create(2.0, 10),
                                                NULL));

    this->centerToSides = 29.0;
    this->centerToBottom = 39.0;
    this->_walkSpeed = 80.0;
    this->_hitPoints = 100.0f;
    this->_damage = 20.0f;

    float toSides = this->getCenterToSides();
    float toBottom = this->getCenterToBottom();
    this->setAttackBox(createBoundingBoxWithOrigin(ccp(toSides, -10), CCSize(20, 20)));
    this->setHitBox(createBoundingBoxWithOrigin(ccp(-toSides, -toBottom), CCSize(2*toSides, 2* toBottom)));
    
    return true;
}

void Hero::knockout()
{
    ActionSprite::knockout();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pd_herodeath.wav");
    return;
}