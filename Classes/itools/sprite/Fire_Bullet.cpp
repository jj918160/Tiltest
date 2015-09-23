//
//  Fire_Bullet.cpp
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#include "Fire_Bullet.h"
#include "Moster.h"
 Fire_Bullet* Fire_Bullet::create(monster*mubiao)
{

    Fire_Bullet *pRet = new(std::nothrow) Fire_Bullet();
    if (pRet && pRet->init(mubiao))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Fire_Bullet::init(monster*mubiao){
    if (!Sprite::init()) {
        return false;
    }
    
    this->initWithFile("fire0.png");
    this->setAnchorPoint(Vec2(0,0.5));
    this->att=mubiao;
    scheduleUpdate();
    return true;
}

void Fire_Bullet::update(float dt){
    
    //设置长度
    this->setScaleX(att->getPosition().getDistance(this->getPosition())/this->getContentSize().width);
    //设置角度
    float arc=this->getPosition().getAngle(att->getPosition());
    
    float degre=CC_RADIANS_TO_DEGREES(arc);
  
    this->setRotation(degre);
  
}
