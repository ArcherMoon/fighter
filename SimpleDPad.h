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

    /* ʵ��CCNode�������������ڽ��볡��ʱע��touch�����˳�����ʱע��touch���� */
    void onEnterTransitionDidFinish();
    void onExit();


    /* ʵ��CCTouchDelegate�ķ��� */
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
    float _radius;  /* ���ⷽ����뾶 */
    
private:

};

#endif
