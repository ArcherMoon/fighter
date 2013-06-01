#ifndef __ACTION_SPRITE_H__
#define __ACTION_SPRITE_H__

#include "cocos2d.h"
#include "Defines.h"

class ActionSprite : public cocos2d::CCSprite
{
public:
    ActionSprite();
    ~ActionSprite();

    virtual void update(float delta);
    
    /* actions */
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, idleAction, IdleAction);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, attackAction, AttackAction);   
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, walkAction, WalkAction);   
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, hurtAction, HurtAction);  
    CC_SYNTHESIZE_RETAIN(cocos2d::CCAction *, knockedOutAction, KnockedOutAction);  
    

    /* action methods */
    void idle();        /* ���� */
    void attack();
    void walkWithDirection(cocos2d::CCPoint direction);
    void hurtWithDamage(float damage);
    virtual void knockout();

    /* ����״̬ */
    CC_SYNTHESIZE(ActionState,_actionState, ActionState);

    /* attributes */
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    CC_SYNTHESIZE(float, _hitPoints, HitPoints);
    CC_SYNTHESIZE(float, _damage,Damage);

    /* movement */
    CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);
    

    /* ���ں���sprite��ʵ�ʴ�С */
    CC_SYNTHESIZE( float, centerToSides, CenterToSides);
    CC_SYNTHESIZE( float, centerToBottom, CenterToBottom);

    /* ���ڽ�����ײ��� */
    CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);
    CC_SYNTHESIZE(BoundingBox, _hitBox, HitBox);
    /* ������ײ���� */
    BoundingBox createBoundingBoxWithOrigin(cocos2d::CCPoint origin, cocos2d::CCSize size);
    /* ���ݾ����λ�ú����ž�����Χ�е�ԭ��ʹ�С */
    void transformBoxes();
    void setPosition(cocos2d::CCPoint position);    /* �Լ�ʵ�ֵģ����Ƕ�ccnode����д */

private:

};
    
#endif
