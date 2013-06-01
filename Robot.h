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
    void knockout();

    CREATE_FUNC(Robot);
    /* ��һ�ξ���ʱ�� */
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);

private:

};

#endif
