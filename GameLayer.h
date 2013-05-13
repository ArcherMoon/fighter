#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:

    virtual bool init();  
    void initTiledMap();

    CREATE_FUNC(GameLayer);
private:
    cocos2d::CCTMXTiledMap * _tiledMap;
};

#endif
