#ifndef __SIMPLEDPAD_H__
#define __SIMPLEDPAD_H__

#include "cocos2d.h"

class SimpleDPadDelegate
{
public:
    virtual void didChangeDirectionTo(cocos2d::CCPoint direction) = 0;
    virtual void simpleDPadTouchEnded() = 0;
};

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

    /* �ɴ������SimpleDPad���ĵ���㷽�� */
    void updateDirectionForTouchLocation(cocos2d::CCPoint location);

    CC_SYNTHESIZE(SimpleDPadDelegate *, _delegate, Delegate);
    CC_SYNTHESIZE(bool,  _isHeld, IsHeld);

protected:
    float _radius;  /* ���ⷽ����뾶 */
    cocos2d::CCPoint _direction;    /* �ƶ����� */
    
private:

};

#endif
