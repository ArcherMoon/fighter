#ifndef __SIMPLEDPAD_H__
#define __SIMPLEDPAD_H__

#include "cocos2d.h"

class SimpleDPad : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate
{
public:
	SimpleDPad(void);
	~SimpleDPad(void);

    CREATE_FUNC(SimpleDPad);

    virtual bool init();  

    /* 实现CCNode的两个方法，在进入场景时注册touch代理，退出场景时注销touch代理 */
    void onEnterTransitionDidFinish();
    void onExit();


    /* 实现CCTouchDelegate的方法 */
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
    float _radius;  /* 虚拟方向键半径 */
    
private:

};

#endif
