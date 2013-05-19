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
        return true;
    }

    /* �ڷ����Բ֮��Ĳ���������false����������touch������ܽ��Ŵ��� */
    return false;
}

void SimpleDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{}

void SimpleDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{}