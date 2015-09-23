//
//  Moster.h
//  Tiltest
//
//  Created by mac on 15-8-13.
//
//

#ifndef __Tiltest__Moster__
#define __Tiltest__Moster__

#include <stdio.h>
#include "Animation_itools.h"
#include "cocos2d.h"
USING_NS_CC;
class PointNode;
enum class DirecTion{
    right,
    left,
    up,
    down
};
class Fire_Bullet;
class monster:public Sprite{
public:
    //和火塔有关的
    bool befired;
    //和冰塔有关的
    int spd_cutcd;
    bool speed_cut;
    //和塔有关的
    int boshu;
    float speed;
    float max_hp;
    int hp;
    Animation_itools *atools;
    virtual bool init();
    CREATE_FUNC(monster);
   // void load_animation();
    void change_animation(Vec2 v1,Vec2 v2);
    Vector<FiniteTimeAction*> init_actioninterval(Vector<PointNode*>vpn,float speed);
   // Vector<FiniteTimeAction*> init_actioninterval_nopath(Vector<PointNode*>path,Vector<PointNode*>attack,float speed);
    Action*a;
    void update(float dt);
    DirecTion _direction;
   
    // void fight_animation();
};
#endif /* defined(__Tiltest__Moster__) */
