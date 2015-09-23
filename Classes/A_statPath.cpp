//
//  A_statPath.cpp
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#include "A_statPath.h"
//判断该点是否可通过
bool A_starPath::isCheck(Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize){
    //越界返回false
    if (point.x<0||point.y<0||point.x>=mapsize.width||point.y>=mapsize.height) {
        return false;
    }
    //如果是走过的点，返回false
    for (auto t:_closeDate) {
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

bool A_starPath::isCheck(Vec2 parentpoint,Vec2 point,std::vector<Vector<Gird*>>gridVector,Size mapsize){
    //越界返回false
    if (point.x<0||point.y<0||point.x>=mapsize.width||point.y>=mapsize.height) {
        return false;
    }
    //如果是走过的点，返回false
    for (auto t:_closeDate) {
        if (t->getX()==point.x&&t->getY()==point.y) {
            return false;
        }
    }
    //如果不可通过，返回false
    Gird*gp=gridVector.at((int)point.x).at((int)point.y);
    Gird*pagp=gridVector.at((int)parentpoint.x).at((int)parentpoint.y);
    //非pass直接return false
    if (!gp->getPass()) {
        return false;
    }
     //直角直接添加
    if (gp->getX()==pagp->getX()||pagp->getY()==gp->getY()) {
            return true;
    }
    //斜角判断添加
    else{
        Gird*left=gridVector.at((int)point.x).at((int)parentpoint.y);
        Gird*right=gridVector.at((int)parentpoint.x).at((int)point.y);
    if (left->getPass()&&right->getPass()) {
        return true;
    }
    }
    return false;
}


//判断开启列表是否已经有P
bool A_starPath::hascp(PointNode*p){
    for (auto pp:_openDate){
        if (pp->getY()==p->getY()&&pp->getX()==p->getX()) {
            return true;
        }
    }
    return false;
}

PointNode* A_starPath::find_nearnest(){
    PointNode*temp;
    if (_openDate.empty()) {
        return nullptr;
    }
    temp=_openDate.front();
    if (_openDate.size()==1) {
        return temp;
    }
    for (auto p:_openDate) {
        if (p->getF()<temp->getF()) {
            temp=p;
        }
    }
    return temp;
}
//寻路，
bool A_starPath::findValidGird(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize){
    CCLOG("in");
    
    PointNode*beginPoint=PointNode::create(from.x, from.y);
    _openDate.pushBack(beginPoint);
    while (1)
    {
       
        PointNode *now=find_nearnest();
        _openDate.eraseObject(now);
        _closeDate.pushBack(now);
     CCLOG("x:%fy:%f",now->getX(),now->getY());
    //将可能成为下个点的8个点加入到开启列表
    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
         
            PointNode*cp=PointNode::create(now->getX()+j, now->getY()+i);
            //找到终点
            if (cp->getX()==to.x&&cp->getY()==to.y) {
                cp->parent=now;
                _openDate.pushBack(cp);
                CCLOG("find");
                return true;
            }
            
            //否则，判断，添加进去
            if (isCheck(Vec2(now->getX(),now->getY()),Vec2(cp->getX(),cp->getY()), gridVector, mapsize)) {
                cp->parent=now;
                //G等于父节点的G值+自己到父的G值
                //算法来自向量的反运算
              /* //直角地图
                cp->setG(sqrtf(pow(cp->getX()-cp->parent->getX(), 2)+pow(cp->getY()-cp->parent->getY(), 2))+cp->parent->getG());
                cp->setH(abs(to.x-cp->getX())+abs(to.y-cp->getY()));
                cp->setF(cp->getG()+cp->getH());
                */
               // 斜角地图
                 int a=cp->getX()-cp->parent->getX();
                 int b=cp->getY()-cp->parent->getY();
                 cp->setG(sqrtf(pow(tileNodesize.width/2*(a-b), 2)+pow(tileNodesize.height/2*(a+b), 2))+cp->parent->getG());
                 cp->setH(abs(to.x-cp->getX())+abs(to.y-cp->getY())*sqrtf(pow(tileNodesize.width,2)+pow(tileNodesize.height,2))/2);
                 cp->setF(cp->getG()+cp->getH());
                 
                 
                
                
                //如果开启列表里面没有，就添加
                if (!hascp(cp)) {
                      _openDate.pushBack(cp);
                }
                else
                {
                    float g1=cp->getG();//新的
                    float g2=0.f;//旧的
                    for (auto pp:_openDate){
                        if (pp->getY()==cp->getY()&&pp->getX()==cp->getX()) {
                            g2=cp->getG();
                            if (g1<g2)
                            {
                                pp->parent=now;
                            }
                        }
                }
                    
            }
        }
            
    
    }
        
    //循环搜索
    if (_openDate.empty()) {
        CCLOG("无路可走");
        return false;
    }
}
}
    return false;
}

//寻路函数，返回最短路径,Gid
Vector<PointNode*> A_starPath::getPath(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize){
    if (!_openDate.empty()) {
        _openDate.clear();
    }
    if (!_closeDate.empty()) {
        _closeDate.clear();
    }
    if (!_pathNode.empty()) {
        _pathNode.clear();
    }
    if(findValidGird(from, to, gridVector,mapsize,tileNodesize)){
        CCLOG("path have been found");
        auto temp=_openDate.back();
        while (temp->parent) {
            _pathNode.pushBack(temp);
            temp=temp->parent;
        }
      }
    _pathNode.reverse();
    return _pathNode;
}
//
Vec2 A_starPath::nopath_try_find(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize){
    //创建起点Node
    PointNode*beginPoint=PointNode::create(from.x, from.y);
    //CCLOG("x:%f,y:%f",from.x,from.y);
   
    //寻找最近障碍节点
   // CCLOG("nopath_try_find");
    while (gridVector.at(beginPoint->getX()).at(beginPoint->getY())->getPass()) {
        Vec2 temp(0,0);
        float juli=10000;
        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1; j++) {
                //寻找离终点最近的。
//                if (beginPoint->getX()+i>mapsize.width||beginPoint->getY()>=mapsize.height||beginPoint->getX()+i<0||beginPoint->getY()<0) {
//                    break;
     //           }
                if (i!=0&&j!=0) {
                    break;
                }
                float dis=Vec2(beginPoint->getX()+i, beginPoint->getY()+j).getDistance(to);
            if(dis<juli){
                    temp.x=beginPoint->getX()+i;
                    temp.y=beginPoint->getY()+j;
                    juli=dis;
                }
            }
        }
        
        beginPoint->setX(temp.x);
        beginPoint->setY(temp.y);
       // CCLOG("begin:%f,%f",temp.x,temp.y);
    }
    // CCLOG("nopath_try_find2");
    //返回找到的障碍节点
    return Vec2(beginPoint->getX(),beginPoint->getY());
}
//Vector<PointNode*> A_starPath::nopath_find_path(Vec2 from,Vec2 to,std::vector<Vector<Gird*>>gridVector,Size mapsize,Size tileNodesize){
//    
//    
//    Vec2 no_point=nopath_try_find(from,to,gridVector,mapsize,tileNodesize);
//   // _attNode.pushBack(PointNode::create(no_point.x, no_point.y));
//    CCLOG("no_point:%f,%f",no_point.x,no_point.y);
//    //找路
//    if (findValidGird(no_point,to,gridVector,mapsize,tileNodesize)) {
//        return getPath(no_point, to, gridVector, mapsize, tileNodesize);
//    }
//    else{
//        if (!_openDate.empty()) {
//            _openDate.clear();
//        }
//        if (!_closeDate.empty()) {
//            _closeDate.clear();
//        }
//        if (!_pathNode.empty()) {
//            _pathNode.clear();
//        }
//        nopath_find_path(no_point,to,gridVector,mapsize,tileNodesize);
//    }
//}
//
