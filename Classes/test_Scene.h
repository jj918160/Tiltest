//
//  test_Scene.h
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#ifndef __Tiltest__test_Scene__
#define __Tiltest__test_Scene__

#include <stdio.h>
#include "PathArithmetic.h"
#include "A_statPath.h"
#include "cocos2d.h"
USING_NS_CC;

class PathArithmetic;
class A_starPath;


class tese_Scene : public Layer
{
public:
    static tese_Scene* create()
    {
        tese_Scene *pRet = new(std::nothrow) tese_Scene();
        if (pRet && pRet->init())
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

    static cocos2d::Scene* createScene();
    virtual bool init(const char* xmlfilename);
    virtual bool init();
    
    PathArithmetic*patol;
    A_starPath* asptol;
    std::vector<Vector<Gird*>> _mapgid;
    ~tese_Scene();
    void callback1(Ref* psender);
    void create_monster(float dt);

    Vector<PointNode*> path_vector;
    Vec2 beginpoint;
    Vec2 bornP;
    Vec2 destination;
};


#endif /* defined(__Tiltest__test_Scene__) */
