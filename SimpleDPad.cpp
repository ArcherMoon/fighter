#include "SimpleDPad.h"

using namespace cocos2d;

SimpleDPad::SimpleDPad(void)
{}

SimpleDPad::~SimpleDPad(void)
{}
    
bool SimpleDPad::init()
{
    /* �������ⷽ���ͼƬ */
    if (!initWithFile("pd_dpad.png"))
    {
        return false;
    }

    _radius = 64.0;
  
    return true;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
    /* ע��touch����,nPriority������ͬ��Խ����������е���λԽ���� */
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

    return;
}
void SimpleDPad::onExit()
{
    /* ע��touch���� */
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    return;
}

bool SimpleDPad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    /* �ڷ����Բ֮�ڵĴ�������true����������touch����Ͳ��ܴ��� */
    CCPoint location = pTouch->getLocation();
    float distanceSQ = ccpDistanceSQ(location, this->getPosition());
    if (distanceSQ <= _radius * _radius)
    {
        CCLOG("receive touch");
        this->updateDirectionForTouchLocation(location);
        _isHeld = true;
        return true;
    }

    /* �ڷ����Բ֮��Ĳ���������false����������touch������ܽ��Ŵ��� */
    return false;
}

void SimpleDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = pTouch->getLocation();
    this->updateDirectionForTouchLocation(location);

    return;
}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    _isHeld = false;
    _delegate->simpleDPadTouchEnded();

    return;
}

void SimpleDPad::updateDirectionForTouchLocation(cocos2d::CCPoint location)
{
    /* �Ѵ�����ת��Ϊ���� */
    float radians = ccpToAngle(ccpSub(location, this->getPosition()));
    float degrees = -1 * CC_RADIANS_TO_DEGREES(radians);

    if (degrees <= 22.5 && degrees >= -22.5)
    {
        /* right */
        _direction = ccp(1.0, 0.0);  
    }
    else if (degrees > 22.5 && degrees < 67.5)
    {
        /* bottomright  */
        _direction = ccp(1.0, -1.0);  
    }
    else if (degrees >= 67.5 && degrees <= 112.5)
    {
        /* bottom */
        _direction = ccp(0.0, -1.0);  
    }
    else if (degrees > 112.5 && degrees <157.5)
    {
        /* bottomleft */
        _direction = ccp(-1.0, -1.0);  
    }
     else if (degrees >= 157.5 || degrees <= -157.5)
    {
        /* left */
        _direction = ccp(-1.0, 0.0);  
    }
    else if (degrees > -157.5 && degrees < -112.5)
    {
        /* topleft */
        _direction = ccp(-1.0, 1.0);  
    }
    else if (degrees >= -112.5 && degrees <= -67.5)
    {
        /* top */
        _direction = ccp(0.0, 1.0);  
    }
    else if (degrees > -67.5 && degrees < -22.5)
    {
        /* topright */
        _direction = ccp(1.0, 1.0);  
    }

    /* �ɴ������� */
    _delegate->didChangeDirectionTo(_direction);

    return;
}
