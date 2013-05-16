#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Hero.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);
    
    virtual bool init();  
    void initTiledMap();

    CREATE_FUNC(GameLayer);

    void initHero();
    
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    cocos2d::CCTMXTiledMap * _tiledMap;     /* 背景地图 */
    cocos2d::CCSpriteBatchNode * _actors;    /* 所有精灵 */
    Hero * _hero;                                         /* 精灵英雄 */
};

#endif
