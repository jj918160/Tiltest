//
//  Wall.h
//  Tiltest
//
//  Created by mac on 15-8-25.
//
//

#ifndef __Tiltest__Wall__
#define __Tiltest__Wall__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Gird;
class Wall:public Sprite
{
public:
    int price;
    int lv;
    int hp;
    int x;
    int y;
    bool stageopen;
    std::string picname;
    int type;
    CREATE_FUNC(Wall);
    virtual bool init();
    void wallchange(int x,int y,std::vector<Vector<Gird*>> _mapgid);
    void changed(int x,int y,std::vector<Vector<Gird*>> _mapgid);
    
};
#endif /* defined(__Tiltest__Wall__) */
