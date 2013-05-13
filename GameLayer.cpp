#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    /* ¼ÓÔØ±³¾°Í¼ */
    initTiledMap();

    return true;
}

void GameLayer::initTiledMap()
{
    _tiledMap = CCTMXTiledMap::create("pd_tilemap.tmx");
    CCObject * pObject = NULL;
    CCTMXLayer * tmxLayer = NULL;
    /* ÉèÖÃÎª²»¿¹¾â³İ */
    CCARRAY_FOREACH(_tiledMap->getChildren(), pObject)
    {
        tmxLayer = (CCTMXLayer *)pObject;
        tmxLayer->getTexture()->setAliasTexParameters();
    }
    this->addChild(_tiledMap, -6);

    return;
}