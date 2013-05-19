#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameScene::GameScene(void)
:_gameLayer(NULL)
{
}

GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
    if (!CCScene::init())
    {
        return false;
    }

    _gameLayer = GameLayer::create();
    this->addChild(_gameLayer, 0);
    _hudLayer = HudLayer::create();
    this->addChild(_hudLayer, 1);
    
    return true;
}

