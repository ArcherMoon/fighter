#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

class GameScene : public cocos2d::CCScene
{
public:
    GameScene(void);
    ~GameScene(void);

    virtual bool init();  

    CREATE_FUNC(GameScene);
    
    CC_SYNTHESIZE(GameLayer *, _gameLayer, GameLayer);
};

#endif
