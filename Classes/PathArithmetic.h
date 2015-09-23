//
//  PathArithmetic.h
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#ifndef __Tiltest__PathArithmetic__
#define __Tiltest__PathArithmetic__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
//代替Point，为了能放到Vector里面
class CustomPoint:public Ref{
    CC_SYNTHESIZE(float, _x, X);
    CC_SYNTHESIZE(float, _y, Y);
public:
    static CustomPoint*create(float x,float y)
    {
            CustomPoint *pRet = new(std::nothrow) CustomPoint();
            if (pRet && pRet->init(x,y))
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
    virtual bool init(float x,float y)
    {
        _x=x;
        _y=y;
        return true;
    }
};
//网格类，和tildmap的格子配合，判断是否可以通过
class Gird:public Ref{
    CC_SYNTHESIZE(float, _x, X);
    CC_SYNTHESIZE(float, _y, Y);
    CC_SYNTHESIZE(bool, _pass, Pass);
public:
    static Gird*create(float x,float y)
    {
        Gird *pRet = new(std::nothrow) Gird();
        if (pRet && pRet->init(x,y))
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
    virtual bool init(float x,float y)
    {
        _x=x;
        _y=y;
        _pass=true;
        return true;
    }
};
//A*实现类，它可以实现找到一个有效路径。
class PathArithmetic:public Ref{
private:
    Vector<CustomPoint*> _badPoint;//记录已经经过的点
    Vector<CustomPoint*> _pathPoint;//记录有效点
public:
  //这里的坐标一律使用的是网格Gid坐标而非像素坐标
    //寻路函数，返回最短路径
    Vector<CustomPoint*>getPath(Vec2 form,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize);
    //递归寻路，
    bool findValidGird(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize);
    //判断该点是否可通过
    bool isCheck(Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize);
    
};


#endif /* defined(__Tiltest__PathArithmetic__) */
