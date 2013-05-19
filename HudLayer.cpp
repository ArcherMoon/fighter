#include "HudLayer.h"

using namespace cocos2d;

HudLayer::HudLayer(void)
{
}

HudLayer:: ~HudLayer(void)
{
}
    
bool HudLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    return true;
}