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

    _dPad = SimpleDPad::create();
    _dPad->setPosition(ccp(64.0, 64.0));
    _dPad->setOpacity(100); /* ÉèÖÃÍ¸Ã÷¶È0~255 */
    this->addChild(_dPad);
    
    return true;
}