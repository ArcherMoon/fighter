#ifndef __HUDLAYER_H__
#define __HUDLAYER_H__

#include "cocos2d.h"
#include "SimpleDPad.h"

class HudLayer : public cocos2d::CCLayer
{
public:
	HudLayer(void);
	~HudLayer(void);
    
    virtual bool init();  

    CREATE_FUNC(HudLayer);

    CC_SYNTHESIZE(SimpleDPad *, _dPad , DPad);

private:

};

#endif
