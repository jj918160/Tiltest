//
//  Player.h
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#ifndef __animate_homework__Player__
#define __animate_homework__Player__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
//网格类，和tildmap的格子配合，判断是否可以通过
//class Gird:public Ref{
//    CC_SYNTHESIZE(float, _x, X);
//    CC_SYNTHESIZE(float, _y, Y);
//    CC_SYNTHESIZE(bool, _pass, Pass);
//public:
//    static Gird*create(float x,float y)
//    {
//        Gird *pRet = new(std::nothrow) Gird();
//        if (pRet && pRet->init(x,y))
//        {
//            pRet->autorelease();
//            return pRet;
//        }
//        else
//        {
//            delete pRet;
//            pRet = NULL;
//            return NULL;
//        }
//        
//    }
//    virtual bool init(float x,float y)
//    {
//        _x=x;
//        _y=y;
//        _pass=true;
//        return true;
//    }
//    
//};

class Player{
public:

    //道具数组
    int money;
    int emage;
    int zhuanshi;
    
    virtual bool init();
    static Player* getInstance();
    Player();
    ~Player();
private:

    static Player* _cacheInstance; //cache instance
   
    //以及一堆自己的属性。
    
    
    
};

#endif /* defined(__animate_homework__Player__) */
