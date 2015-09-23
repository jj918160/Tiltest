#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Animation_itools.h"
class monster;
class HelloWorld : public cocos2d::Layer
{
public:
    
     Animation_itools* atools;
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual bool init(const char* xmlfilename);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    //void load_animation();
   
    ValueVector init_vecvector(const std::string obj_l_name);
    Vector<FiniteTimeAction*> init_actioninterval(std::map<int,Vec2> mapintv,float speed);
    //int changedirection(Vec2 v1,Vec2 v2);
   // void change_animation();
    void test();
    
    Vec2 beginVec;
    std::map<int,Vec2> mapintv2;
    
    Vector<Sprite*>vecofm;
    void update(float dt);
    void create_monster(float dt);
    int hurder;
    
};

#endif // __HELLOWORLD_SCENE_H__
