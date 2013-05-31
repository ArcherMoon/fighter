#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "SimpleDPad.h"
#include "HudLayer.h"

class GameLayer : public cocos2d::CCLayer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);
    
    virtual bool init();  
    void initTiledMap();
    void updateRobots(float delta);
    void endGame();
    void restartGame();
    virtual void update(float delta);
    void updatePositions();
    /* ʹheroʼ��λ����Ļ���� */
    void setViewpointCenter(cocos2d::CCPoint position);  

    CREATE_FUNC(GameLayer);
    
    void initHero();
    void initRobots();
    void reorderActors(void);
        
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    /* ʵ�ִ���SimpleDPadDelegate�еķ��� */
    void didChangeDirectionTo(cocos2d::CCPoint direction);
    void simpleDPadTouchEnded();

    CC_SYNTHESIZE(HudLayer *, _hud, Hud);
    
private:
    cocos2d::CCTMXTiledMap * _tiledMap;     /* ������ͼ */
    cocos2d::CCSpriteBatchNode * _actors;    /* ���о��� */
    Hero * _hero;                                         /* ����Ӣ�� */
    cocos2d::CCArray * _robots;                 /* ���������� */
};

#endif
