#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::GameLayer(void)
{
}

GameLayer:: ~GameLayer(void)
{
}
    
bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    /* ���ر���ͼ */
    initTiledMap();

    /* ���ؾ��� */
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
    this->addChild(_actors, -5);

    /* ��ʼ��hero */
    this->initHero();

    /* ʹ�ܴ��� */
    this->setTouchEnabled(true);

    return true;
}

void GameLayer::initTiledMap()
{
    _tiledMap = CCTMXTiledMap::create("pd_tilemap.tmx");
    CCObject * pObject = NULL;
    CCTMXLayer * tmxLayer = NULL;
    /* ����Ϊ������� */
    CCARRAY_FOREACH(_tiledMap->getChildren(), pObject)
    {
        tmxLayer = (CCTMXLayer *)pObject;
        tmxLayer->getTexture()->setAliasTexParameters();
    }
    this->addChild(_tiledMap, -6);

    return;
}

void GameLayer::initHero()
{
    /* ����Ӣ�۲���ʼ�� */
    _hero = Hero::create();

    /* ���ΪspriteBatch���ӽڵ㣬���ڻ�ͼ */
    _actors->addChild(_hero);

    /* ����hero��λ�� */
    _hero->setPosition(ccp(_hero->getCenterToSides(), 80));

    /* ִ�п��еĶ��� */
    _hero->idle();

    return;
}

void  GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    _hero->attack();
}