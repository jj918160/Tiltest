//
//  A_statPath.h
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#ifndef __Tiltest__A_statPath__
#define __Tiltest__A_statPath__

#include <stdio.h>
#include "cocos2d.h"
#include "PathArithmetic.h"
USING_NS_CC;
class PointNode:public Ref{
    CC_SYNTHESIZE(float, _x, X);
    CC_SYNTHESIZE(float, _y, Y);
    CC_SYNTHESIZE(float, _f, F);//F＝G＋H
    CC_SYNTHESIZE(float, _g, G);//距离起点的距离
    CC_SYNTHESIZE(float, _h, H);//距离终点的距离
public:
    static PointNode*create(float x,float y)
    {
        PointNode *pRet = new(std::nothrow) PointNode();
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
        parent=nullptr;
        return true;
    }
public:
    PointNode*parent;
};


class A_starPath:public Ref{
private:
    Vector<PointNode*> _openDate;//开启列表
    Vector<PointNode*> _closeDate;//关闭列表，表示无效点，到过的点
    Vector<PointNode*> _pathNode;
   
   
    
public:
 
    //这里的坐标一律使用的是网格Gid坐标而非像素坐标
    //寻路函数，返回最短路径
    Vector<PointNode*>getPath(Vec2 form,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize);
    //递归寻路，mapsize是map的GID坐标，是整数，tileNodeSize是瓦片格的单元大小，方便该方法适应不同类型的地图
    bool findValidGird(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize);
    //判断该点是否可通过
    bool isCheck(Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize);
    //斜角判断
    bool isCheck(Vec2 pointparent,Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize);
    
    bool hascp(PointNode*p);

    PointNode* find_nearnest();
    //没有路径，攻击初始化函数
    Vec2 nopath_try_find(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize);
//    
//    Vector<PointNode*> nopath_find_path(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize);
//    
};


#endif /* defined(__Tiltest__A_statPath__) */
