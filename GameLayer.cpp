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

    /* ��ʱ������update���� */
    this->scheduleUpdate();
    
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
    return;
}

void  GameLayer::didChangeDirectionTo(CCPoint direction)
{
    /* ִ���ƶ����� */
    _hero->walkWithDirection(direction);
    return;
}

void GameLayer::simpleDPadTouchEnded()
{
    _hero->idle();    
}

void GameLayer::update(float delta)
{
    _hero->update(delta);
    this->updatePositions();
    this->setViewpointCenter(_hero->getPosition());

    return;
}

void GameLayer::updatePositions()
{
    /* �趨�ƶ���Χ */
    float x = MIN(MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x), _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - _hero->getCenterToSides());
    float y = MIN(MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y), _tiledMap->getTileSize().height * 3 + _hero->getCenterToBottom());
    _hero->setPosition(ccp(x, y));

    return;
}

void GameLayer::setViewpointCenter(CCPoint position)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - winSize.width / 2);
    y = MIN(y, _tiledMap->getMapSize().height * _tiledMap->getTileSize().height - winSize.height / 2);
    CCPoint actualPosition = ccp(x, y);

    CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);

    return;    
}
