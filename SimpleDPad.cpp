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
        return true;
    }

    /* 在方向键圆之外的不处理，返回false，这样其他touch代理就能接着处理 */
    return false;
}

void SimpleDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{}