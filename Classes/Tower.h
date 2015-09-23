//
//  Tower.h
//  Tiltest
//
//  Created by mac on 15-8-25.
//
//

#ifndef __Tiltest__Tower__
#define __Tiltest__Tower__

#include <stdio.h>
#include "cocos2d.h"
#include "Moster.h"
USING_NS_CC;
class Csv_Parser;
class Gird;
class Tower:public Sprite
{
public:
    int price;
    int max_lv;
    int lv;
    int hp;
    float att_distance;
    float atk;
    int atk_intervel;
    int CD;
    int x;
    int y;
    //读取配置表
     Csv_Parser*Csv_parser;
     ValueVector onecolum;
        bool stageopen;
    std::string picname;
    int type;
    CREATE_FUNC(Tower);
    virtual bool init();
    bool cancreate(int x,int y,std::vector<Vector<Gird*>> _mapgid);
    virtual void attack(Vector<monster*>vecofm);
    bool can_attack();
    //void attack_update(float dt);
   virtual void update(float dt);
    virtual void lv_up();
    
};

#endif /* defined(__Tiltest__Tower__) */
