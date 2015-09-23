//
//  Fire_Tower.h
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#ifndef __Tiltest__Fire_Tower__
#define __Tiltest__Fire_Tower__

#include <stdio.h>
#include "cocos2d.h"
#include "Moster.h"
#include "Tower.h"

USING_NS_CC;
class Csv_Parser;
class Gird;
class Fire_Tower:public Tower
{
public:
    CREATE_FUNC(Fire_Tower);
    int atk_num;
    //这两个数组记录地狱塔的攻击目标，第一个记录现在的目标，通过怪物数组更新
    Vector<monster*>atk_mubiao;
    virtual bool init();
    virtual void lv_up();
    virtual void update(float dt);
    void my_update(float dt);
     void music_update(float dt);
    virtual void attack(Vector<monster*>vecofm);
    

};
#endif /* defined(__Tiltest__Fire_Tower__) */
