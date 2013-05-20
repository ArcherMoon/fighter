#include "SimpleDPad.h"

using namespace cocos2d;

SimpleDPad::SimpleDPad(void)
{}

SimpleDPad::~SimpleDPad(void)
{}
    
bool SimpleDPad::init()
{
    /* 加载虚拟方向键图片 */
    if (!initWithFile("pd_dpad.png"))
    {
        return false;
    }

    _radius = 64.0;
  
    return true;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
    /* 注册touch代理,nPriority不能相同，越大的在数组中的排位越靠后 */
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);

    return;
}
void SimpleDPad::onExit()
{
    /* 注销touch代理 */
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    return;
}

bool SimpleDPad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    /* 在方向键圆之内的处理，返回true，这样其他touch代理就不能处理 */
    CCPoint location = pTouch->getLocation();
    float distanceSQ = ccpDistanceSQ(location, this->getPosition());
    if (distanceSQ <= _radius * _radius)
    {
        CCLOG("receive touch");
        this->updateDirectionForTouchLocation(location);
        _isHeld = true;
        return true;
    }

    /* 在方向键圆之外的不处理，返回false，这样其他touch代理就能接着处理 */
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
    /* 把触摸点转换为方向 */
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

    /* 由代理处理方向 */
    _delegate->didChangeDirectionTo(_direction);

    return;
}
