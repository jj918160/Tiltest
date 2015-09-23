//
//  Fire_Bullet.h
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#ifndef __Tiltest__Fire_Bullet__
#define __Tiltest__Fire_Bullet__

#include <stdio.h>
#include "cocos2d.h"
class monster;
using namespace::cocos2d;
class Fire_Bullet:public Sprite{
public:
   
    static Fire_Bullet* create(monster*mubiao) ;
    virtual bool init(monster*mubiao);
    monster*att;
    void update(float dt);
};
#endif /* defined(__Tiltest__Fire_Bullet__) */
