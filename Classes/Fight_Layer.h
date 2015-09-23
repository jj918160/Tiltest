//
//  Fight_Layer.h
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#ifndef __Tiltest__Fight_Layer__
#define __Tiltest__Fight_Layer__

#include <stdio.h>
#include "PathArithmetic.h"
#include "A_statPath.h"
#include "Moster.h"
#include "Tower.h"
#include "ice_Tower.h"
#include "Fire_Tower.h"
#include "Wall.h"
#include "cocos2d.h"
USING_NS_CC;
class Csv_Parser;
class A_starPath;

class Fight_Layer : public Layer
{
public:

    CREATE_FUNC(Fight_Layer);
    
   // static cocos2d::Scene* createScene();
    virtual bool init();
    int totalhp;
    float _distance;
    float _mscale;
    Size tilesize;
    
    Vec2 converToint(Vec2 point);
    //Gid转模型坐标
    Vec2 converintTofloat(Vec2 point);
    std::vector<Vector<Gird*>> _mapgid;
    void createwall(int x,int y);
    void createtower(int x,int y);
     void create_icetower(int x,int y);
    void create_firetower(int x,int y);
    A_starPath* asptol;
    Vector<PointNode*> path_vector;
   //Vector<PointNode*> att_vector;
    Vec2 beginpoint;
    Vec2 bornP;
    Vec2 destination;
    void callback1(Ref* psender);
//    void callback2(Ref* psender);
//    void callback3(Ref* psender);
    void create_monster(float dt);
    void putoutover(float dt);
    void update(float dt);
    
    Csv_Parser*Csv_parser;
    ValueVector onecolum;
    void initstage();
    //波数
    int boshu;
    int nowboshu;
    bool poutover;
    //记录点击状态
    enum class touchType{
        create_wall,
        create_tower,
        move,
        create_icetower,
        create_firetower
    };
    static touchType t_type;
    Vector<monster*>vecofmon;
    Vector<Tower*>vecoft;
    Vector<Wall*>vecofw;
 
    bool game_over;
    bool game_win;
   // void nopath(monster*mon);
};

#endif /* defined(__Tiltest__Fight_Layer__) */
