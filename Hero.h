#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "ActionSprite.h"

class Hero : public ActionSprite
{
public:
	Hero(void);
	~Hero(void);
    virtual bool init();
    void knockout();

    CREATE_FUNC(Hero);

private:

};

#endif
