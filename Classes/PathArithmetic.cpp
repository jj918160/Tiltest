//
//  PathArithmetic.cpp
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#include "PathArithmetic.h"



//判断该点是否可通过
bool PathArithmetic::isCheck(Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize){
    //越界返回false
    if (point.x<0||point.y<0||point.x>=mapsize.width||point.y>=mapsize.height) {
        return false;
    }
    //如果是走过的点，返回false
    for (auto t:_badPoint) {
        if (t->getX()==point.x&&t->getY()==point.y) {
            return false;
        }
    }
   //如果不可通过，返回false
    Gird*gp=gridVector.at((int)point.x).at((int)point.y);
    if (gp->getPass()) {
        return true;
    }
    return false;
}
//递归寻路，
bool PathArithmetic::findValidGird(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize){
    CustomPoint*beginPoint=CustomPoint::create(from.x, from.y);
    _badPoint.pushBack(beginPoint);
    CCLOG("size:%d",_badPoint.size());
 //储存可能成为下个点的8个点
    Vector<CustomPoint*> nextpoints;
    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
            CustomPoint*cp=CustomPoint::create(from.x+j, from.y+i);
            if (isCheck(Vec2(cp->getX(),cp->getY()), gridVector, mapsize)) {
                nextpoints.pushBack(cp);
            }
            if (cp->getX()==to.x&&cp->getY()==to.y) {
                             _pathPoint.pushBack(cp);
                            return true;
            }

            //nextpoints.pushBack(CustomPoint::create(from.x+j, from.y+i));
        }
    }
 //剔除无效点
//    for (auto temp:nextpoints) {
//        //如果是终点，return true
//        if (temp->getX()==to.x&&temp->getY()==to.y) {
//             _pathPoint.pushBack(temp);
//            return true;
//        }
//        if (!isCheck(Vec2(temp->getX(), temp->getY()), gridVector, mapsize)) {
//            nextpoints.eraseObject(temp);
//        }
//    }
//然后进行排序
    std::sort(nextpoints.begin(), nextpoints.end(), [=](const Ref*obj1,const Ref*obj2){
        CustomPoint*cp1=(CustomPoint*)obj1;
        CustomPoint*cp2=(CustomPoint*)obj2;
        Vec2 p1(cp1->getX(),cp1->getY());
        Vec2 p2(cp2->getX(),cp2->getY());
        //只需判断离终点近即可
        double r1=p1.getDistance(to);
        double r2=p2.getDistance(to);
       /*斜角
        int a1=p1.x-to.x;
        int b1=p1.y-to.y;
        int a2=p2.x-to.x;
        int b2=p2.y-to.y;
        double r1=sqrtf(pow(tileNodesize.width/2*(a1-b1), 2)+pow(tileNodesize.height/2*(a1+b1), 2));
        double r2=sqrtf(pow(tileNodesize.width/2*(a2-b2), 2)+pow(tileNodesize.height/2*(a2+b2), 2));
        */
        
        
        return r1<r2?-1:0;
    });
     for (auto pi:nextpoints)
     {
         CCLOG("nextsortx:%f,nextsorty:%f",pi->getX(),pi->getY());
     }
    
    
    
//递归搜索
    if (nextpoints.empty()) {
        return false;
    }
    for (auto pi:nextpoints)
    {
        if (findValidGird(Vec2(pi->getX(),pi->getY()),to,gridVector,mapsize))
        {
            _pathPoint.pushBack(pi);
        return true;
        }
    }
  
    return false;
}
//寻路函数，返回最短路径
Vector<CustomPoint*> PathArithmetic::getPath(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize){
    if (!_pathPoint.empty()) {
        _pathPoint.clear();
    }
    if (!_badPoint.empty()) {
        _badPoint.clear();
    }
    findValidGird(from, to, gridVector,mapsize);
    _pathPoint.reverse();
    return _pathPoint;
}

