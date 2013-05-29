#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "cocos2d.h"
#include "ActionSprite.h"

class Robot : public ActionSprite
{
public:
	Robot(void);
	~Robot(void);
    virtual bool init();

    CREATE_FUNC(Robot);

private:

};

#endif
