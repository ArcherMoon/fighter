#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "SimpleDPad.h"

class GameLayer : public cocos2d::CCLayer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);
    
    virtual bool init();  
    void initTiledMap();
    void updateRobots(float delta);
    virtual void update(float delta);
    void updatePositions();
    /* 使hero始终位于屏幕中心 */
    void setViewpointCenter(cocos2d::CCPoint position);  

    CREATE_FUNC(GameLayer);
    
    void initHero();
    void initRobots();
    void reorderActors(void);
        
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    /* 实现代理SimpleDPadDelegate中的方法 */
    void didChangeDirectionTo(cocos2d::CCPoint direction);
    void simpleDPadTouchEnded();
    
private:
    cocos2d::CCTMXTiledMap * _tiledMap;     /* 背景地图 */
    cocos2d::CCSpriteBatchNode * _actors;    /* 所有精灵 */
    Hero * _hero;                                         /* 精灵英雄 */
    cocos2d::CCArray * _robots;                 /* 机器人数组 */
};

#endif
