#include "ActionSprite.h"


using namespace cocos2d;

ActionSprite::ActionSprite()
{
}

ActionSprite::~ActionSprite()
{
}

void ActionSprite::idle()
{
    this->stopAllActions();
    this->runAction(idleAction);

    return;
}