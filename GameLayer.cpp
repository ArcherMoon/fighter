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

    /* ���ر���ͼ */
    initTiledMap();

    /* ���ؾ��� */
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
    this->addChild(_actors, -5);

    /* ��ʼ��hero */
    this->initHero();

    /* ��ʼ��robots */
    this->initRobots();
    
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

void GameLayer::initRobots()
{
    /* ����50��robots */
    int robotCount = 50;
    _robots = CCArray::createWithCapacity(robotCount);
    _robots->retain();

    for (int i=0; i<robotCount; ++i)
    {
        Robot *robot = Robot::create();
        _actors->addChild(robot);
        _robots->addObject(robot);

        /* ���� λ����� */
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
    if (ActionStateAttack == _hero->getActionState())
    {
        /* �������л����˽�����ײ��� */
        CCObject * pObject = NULL;
        CCARRAY_FOREACH(_robots, pObject)
        {
            Robot * robot = (Robot *)pObject;
            if (ActionStateKnockedOut == robot->getActionState())
            {
                return;
            }
            /* ֻ����ͬһˮƽ�߲Ž�����ײ���(��ֱ���10������Ϊ��ͬһˮƽ��) */
            if (fabsf(_hero->getPosition().y - robot->getPosition().y) > 10)
            {
                return;
            }      
            if (_hero->getAttackBox().actual.intersectsRect(robot->getHitBox().actual))
            {
                robot->hurtWithDamage(_hero->getDamage());
            }
        }
    }
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

void GameLayer::reorderActors(void)
{
    CCObject * pObject = NULL;
    CCARRAY_FOREACH(_actors->getChildren(), pObject)
    {
        ActionSprite * sprite = (ActionSprite *)pObject;
        _actors->reorderChild(sprite, _tiledMap->getMapSize().height * _tiledMap->getTileSize().height - sprite->getPosition().y);
    }

    return;
}

void GameLayer::updatePositions()
{
    /* �趨�ƶ���Χ */
    float x = MIN(MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x), _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - _hero->getCenterToSides());
    float y = MIN(MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y), _tiledMap->getTileSize().height * 3 + _hero->getCenterToBottom());
    _hero->setPosition(ccp(x, y));

    /* �����о����z���������򣬾�����ͼ˳�� */
    this->reorderActors();

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
