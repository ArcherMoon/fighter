#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"
#include "Hero.h"

class GameLayer : public cocos2d::CCLayer
{
public:

    virtual bool init();  
    void initTiledMap();

    CREATE_FUNC(GameLayer);

    void initHero();
private:
    cocos2d::CCTMXTiledMap * _tiledMap;     /* ������ͼ */
    cocos2d::CCSpriteBatchNode * _actors;    /* ���о��� */
    Hero * _hero;                                         /* ����Ӣ�� */
};

#endif
