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

    /* 加载背景图 */
    initTiledMap();

    /* 加载精灵 */
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
    this->addChild(_actors, -5);

    /* 初始化hero */
    this->initHero();

    /* 使能触摸 */
    this->setTouchEnabled(true);

    return true;
}

void GameLayer::initTiledMap()
{
    _tiledMap = CCTMXTiledMap::create("pd_tilemap.tmx");
    CCObject * pObject = NULL;
    CCTMXLayer * tmxLayer = NULL;
    /* 设置为不抗锯齿 */
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
    /* 创建英雄并初始化 */
    _hero = Hero::create();

    /* 添加为spriteBatch的子节点，用于画图 */
    _actors->addChild(_hero);

    /* 设置hero的位置 */
    _hero->setPosition(ccp(_hero->getCenterToSides(), 80));

    /* 执行空闲的动作 */
    _hero->idle();

    return;
}

void  GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    _hero->attack();
}