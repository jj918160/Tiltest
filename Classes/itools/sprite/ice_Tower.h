//
//  ice_Tower.h
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#ifndef __Tiltest__ice_Tower__
#define __Tiltest__ice_Tower__

#include <stdio.h>
#include "cocos2d.h"
#include "Moster.h"
#include "Tower.h"
USING_NS_CC;
class Csv_Parser;
class Gird;
class ice_Tower:public Tower
{
public:
    CREATE_FUNC(ice_Tower);
    float speed_cut;
     virtual bool init();
   virtual void attack(Vector<monster*>vecofm);
   virtual void lv_up();
    void speed_up(float dt);
};

#endif /* defined(__Tiltest__ice_Tower__) */
