#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Robot.h"
#include "Defines.h"

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

    /* 初始化robots */
    this->initRobots();
    
    /* 使能触摸 */
    this->setTouchEnabled(true);

    /* 定时器更新update方法 */
    this->scheduleUpdate();
    
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

void GameLayer::initRobots()
{
    /* 创建50个robots */
    int robotCount = 50;
    _robots = CCArray::createWithCapacity(robotCount);
    _robots->retain();

    for (int i=0; i<robotCount; ++i)
    {
        Robot *robot = Robot::create();
        _actors->addChild(robot);
        _robots->addObject(robot);

        /* 设置 位置随机 */
        int minX = SCREEN.width + robot->getCenterToSides();
        int maxX = _tiledMap->getMapSize().width *_tiledMap->getTileSize().width - robot->getCenterToSides();
        int minY = robot->getCenterToBottom();
        int maxY = 3*_tiledMap->getTileSize().height + robot->getCenterToBottom();

        robot->setScaleX(-1);
        robot->setPosition(ccp(RANDOM_RANGE(minX, maxX), RANDOM_RANGE(minY, maxY)));
        robot->idle();        
    }
    
    
    return;
}

void  GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    _hero->attack();
    return;
}

void  GameLayer::didChangeDirectionTo(CCPoint direction)
{
    /* 执行移动动作 */
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
    /* 设定移动范围 */
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
