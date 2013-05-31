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
    _hero->setDesiredPosition(_hero->getPosition());

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
        /* 遍历所有机器人进行碰撞检测 */
        CCObject * pObject = NULL;
        CCARRAY_FOREACH(_robots, pObject)
        {
            Robot * robot = (Robot *)pObject;
            if (ActionStateKnockedOut == robot->getActionState())
            {
                continue;
            }
            /* 只有在同一水平线才进行碰撞检测(垂直相差10可以认为在同一水平线) */
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
    /* 执行移动动作 */
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
    /* robot存活计数 */
    int alive = 0;
    /* 遍历所有robots */
    CCObject * pObject = NULL;
    Robot * robot = NULL;
    CCARRAY_FOREACH(_robots, pObject)
    {
        robot = (Robot *)pObject;
        /* 更新robot的位置 */
        robot->update(delta);
        if (ActionStateKnockedOut == robot->getActionState())
        {
            continue;
        }
        alive++;
        if (CURTIME < robot->getNextDecisionTime())
        {
            /* 没到决策时间，换下一个robot */
            continue;
        }
        CCLOG("robot ai----%ld.", CURTIME);
        /* 超过决策时间才进行决策 */
       float distanceSQ = ccpDistanceSQ(_hero->getPosition(), robot->getPosition());
        /* robot与hero的距离小于50，attack或idle */
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
                        /* hero死亡则游戏结束,已经创建结束菜单则不再进入 */
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
    /* robot全灭则游戏结束，已经创建结束菜单则不再进入 */
    if (0 == alive &&  (NULL == _hud->getChildByTag(5)))
    {
        this->endGame();
    }
    
    return;
}

void GameLayer::endGame()
{
    /* 创建restart标签 */
    /* 创建标签 */
    CCLabelTTF *restartLabel = CCLabelTTF::create("RESTART", "Arial", 30);
    /* 创建菜单项 */
    CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(GameLayer::restartGame));
    /* 创建菜单 */
    CCMenu *menu = CCMenu::create(restartItem, NULL);
    menu->setPosition(CENTER);
    /* 设置tag，方便查找 */
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
    /* 设定hero移动范围 */
    float x = MIN(MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x), _tiledMap->getMapSize().width * _tiledMap->getTileSize().width - _hero->getCenterToSides());
    float y = MIN(MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y), _tiledMap->getTileSize().height * 3 + _hero->getCenterToBottom());
    _hero->setPosition(ccp(x, y));

    /* 设定robot移动范围 */

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

    /* 对所有精灵的z轴重新排序，决定绘图顺序 */
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
