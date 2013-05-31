#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Robot.h"
#include "Defines.h"
#include "GameScene.h"

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
    _hero->setDesiredPosition(_hero->getPosition());

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
        robot->setDesiredPosition(robot->getPosition());
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
                continue;
            }
            /* ֻ����ͬһˮƽ�߲Ž�����ײ���(��ֱ���10������Ϊ��ͬһˮƽ��) */
            if (fabsf(_hero->getPosition().y - robot->getPosition().y) > 10)
            {
                continue;
            }      
            if (_hero->getAttackBox().actual.intersectsRect(robot->getHitBox().actual))
            {
                CCLOG("hero hit ----");
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

void GameLayer::updateRobots(float delta)
{
    int randomChoice = 0;
    /* robot������ */
    int alive = 0;
    /* ��������robots */
    CCObject * pObject = NULL;
    Robot * robot = NULL;
    CCARRAY_FOREACH(_robots, pObject)
    {
        robot = (Robot *)pObject;
        /* ����robot��λ�� */
        robot->update(delta);
        if (ActionStateKnockedOut == robot->getActionState())
        {
            continue;
        }
        alive++;
        if (CURTIME < robot->getNextDecisionTime())
        {
            /* û������ʱ�䣬����һ��robot */
            continue;
        }
        CCLOG("robot ai----%ld.", CURTIME);
        /* ��������ʱ��Ž��о��� */
       float distanceSQ = ccpDistanceSQ(_hero->getPosition(), robot->getPosition());
        /* robot��hero�ľ���С��50��attack��idle */
        if (distanceSQ <= 50*50)
        {
            robot->setNextDecisionTime(CURTIME + FRANDOM_RANGE(0.1, 0.5)*1000);
            randomChoice = RANDOM_RANGE(0,  1);
            if (0 == randomChoice)
            {
                /* attack */
                if (_hero->getPosition().x > robot->getPosition().x)
                {
                    robot->setScaleX(1.0);
                }
                else
                {
                    robot->setScaleX(-1.0);
                }
                
                robot->attack();
                if (ActionStateAttack == robot->getActionState())
                {
                    if (fabsf(_hero->getPosition().y - robot->getPosition().y) > 10)
                    {
                        return;
                    }      
                    if (robot->getAttackBox().actual.intersectsRect(_hero->getHitBox().actual))
                    {
                        _hero->hurtWithDamage(robot->getDamage());
                        /* hero��������Ϸ����,�Ѿ����������˵����ٽ��� */
                        if ((ActionStateKnockedOut == _hero->getActionState()) && (NULL == _hud->getChildByTag(5)) )
                        {
                            this->endGame();
                        }
                    }
                }
    
            }
            else
            {
                /* idle */
               robot->idle();
            }
        }
        else if (distanceSQ <= SCREEN.width * SCREEN.width)
        {
            robot->setNextDecisionTime(CURTIME + FRANDOM_RANGE(0.5, 1.0)*1000);
            randomChoice = RANDOM_RANGE(0,  2);
            if (0 == randomChoice)
            {
                /* walk */
                CCPoint moveDirection = ccpNormalize(ccpSub(_hero->getPosition(), robot->getPosition()));
                robot->walkWithDirection(moveDirection);
            }
            else
            {
                /* idle */
                robot->idle();
            }            
        }
    }
    /* robotȫ������Ϸ�������Ѿ����������˵����ٽ��� */
    if (0 == alive &&  (NULL == _hud->getChildByTag(5)))
    {
        this->endGame();
    }
    
    return;
}

void GameLayer::endGame()
{
    /* ����restart��ǩ */
    /* ������ǩ */
    CCLabelTTF *restartLabel = CCLabelTTF::create("RESTART", "Arial", 30);
    /* �����˵��� */
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(GameLayer::restartGame));
    /* �����˵� */
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition(CENTER);
    /* ����tag��������� */
    menu->setTag(5);
    _hud->addChild(menu, 5);
    
    return;
}

void GameLayer::restartGame()
{
    CCDirector::sharedDirector()->replaceScene(GameScene::create());
    return;
}

void GameLayer::update(float delta)
{
    _hero->update(delta);
    this->updateRobots(delta);
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
    /* �趨hero�ƶ���Χ */
    float x = MIN(MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x), _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - _hero->getCenterToSides());
    float y = MIN(MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y), _tiledMap->getTileSize().height * 3 + _hero->getCenterToBottom());
    _hero->setPosition(ccp(x, y));

    /* �趨robot�ƶ���Χ */

    CCObject *pObject = NULL;
    Robot *robot = NULL;
    CCARRAY_FOREACH(_robots, pObject)
    {
        robot = (Robot *)pObject;
        if (ActionStateKnockedOut == robot->getActionState())
        {
            continue;
        }
        x = MIN(MAX(robot->getCenterToSides(), robot->getDesiredPosition().x), _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - robot->getCenterToSides());
        y = MIN(MAX(robot->getCenterToBottom(), robot->getDesiredPosition().y), _tiledMap->getTileSize().height * 3 + robot->getCenterToBottom());
        robot->setPosition(ccp(x, y));
    }

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
