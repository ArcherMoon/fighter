#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "ActionSprite.h"

class Hero : public ActionSprite
{
public:
    virtual bool init();

    CREATE_FUNC(Hero);

private:

};

#endif
