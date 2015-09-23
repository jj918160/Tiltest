#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Moster.h"
#include "Animation_itools.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //load_animation();
    hurder=1;
    TMXTiledMap*map=TMXTiledMap::create("test_1.tmx");
    addChild(map,0,1);
    
    ParticleSystem*p=ParticleSpiral::create();
    p->setSpeed(100);
    p->setDuration(5.f);
    p->setPositionType(ParticleSystem::PositionType::GROUPED);
    p->setPosition(100,500);
    p->setStartSize(10.f);
    p->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);
    
    addChild(p);
//    FREE,
//    RELATIVE,
//    GROUPED,
    
    
    ValueVector vv=init_vecvector("second_obj_layer");
    
  
    
    std::map<int,Vec2> mapintv;
    for (int i=0; i<vv.size(); i++) {
       ValueMap vmp=vv.at(i).asValueMap();
        float x=vmp.at("x").asFloat();
        float y=vmp.at("y").asFloat();
        int num=vmp.at("name").asInt();
        Vec2 pot=Vec2(x,y);
     //   CCLOG("x:%f,y:%f,num:%d",x,y,num);
        
        mapintv.insert(std::make_pair(num,pot));
        
        //CCLOG("out");
    }
    mapintv2=mapintv;
    
    Vec2 beginpoint=mapintv.at(1);
    beginVec=mapintv.at(1);
    
   // CCLOG("begin:x:%fy:%f",beginpoint.x,beginpoint.y);
    
    //sp->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("goright")));
auto sp=monster::create();
    Vector<FiniteTimeAction*>vai=init_actioninterval(mapintv,sp->speed);
    vai.pushBack(RemoveSelf::create());
    CCLOG("vai.size:%zd",vai.size());
    
    
    sp->runAction(Sequence::create(vai));
    sp->setPosition(beginpoint);
    this->addChild(sp);
    vecofm.pushBack(sp);
    
   // init_actioninterval(mapintv);
    schedule(schedule_selector(HelloWorld::create_monster), 1, 20, 1);
    scheduleUpdate();
    return true;
}

bool HelloWorld::init(const char* filename)
{
    //////////////////////////////
    // 1. super init first
    hurder++;
    if ( !Layer::init() )
    {
        return false;
    }
    //load_animation();
  
    
    TMXTiledMap*map=TMXTiledMap::create(filename);
    addChild(map,0,1);
    
    
    ValueVector vv=init_vecvector("second_obj_layer");
    
    
    
    std::map<int,Vec2> mapintv;
    for (int i=0; i<vv.size(); i++) {
        ValueMap vmp=vv.at(i).asValueMap();
        float x=vmp.at("x").asFloat();
        float y=vmp.at("y").asFloat();
        int num=vmp.at("name").asInt();
        Vec2 pot=Vec2(x,y);
        //   CCLOG("x:%f,y:%f,num:%d",x,y,num);
        
        mapintv.insert(std::make_pair(num,pot));
        
        //CCLOG("out");
    }
    mapintv2=mapintv;
    
    Vec2 beginpoint=mapintv.at(1);
    beginVec=mapintv.at(1);
    
    // CCLOG("begin:x:%fy:%f",beginpoint.x,beginpoint.y);
    
    //sp->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("goright")));
      auto sp=monster::create();
    
    Vector<FiniteTimeAction*>vai=init_actioninterval(mapintv,sp->speed);
    vai.pushBack(RemoveSelf::create());
    CCLOG("vai.size:%zd",vai.size());
    
  
    sp->runAction(Sequence::create(vai));
    sp->setPosition(beginpoint);
    this->addChild(sp);
    vecofm.pushBack(sp);
    
    // init_actioninterval(mapintv);
    schedule(schedule_selector(HelloWorld::create_monster), 1, 20, 1);
    scheduleUpdate();
    return true;
}


ValueVector HelloWorld::init_vecvector(const std::string obj_l_name){
    TMXTiledMap*map=static_cast<TMXTiledMap*>(this->getChildByTag(1));
    TMXObjectGroup*group=map->getObjectGroup(obj_l_name);
    ValueVector vv=group->getObjects();
    return vv;
}

Vector<FiniteTimeAction*> HelloWorld::init_actioninterval(std::map<int,Vec2> mapintv,float speed){
    Vector<FiniteTimeAction*>acv;
    auto it=mapintv.begin();
    for (;it!=mapintv.end();) {
        Vec2 v1=(Vec2)it->second;
        it++;
        if (it!=mapintv.end()) {
            Vec2 v2=(Vec2)it->second;
            FiniteTimeAction*move=MoveTo::create(v1.getDistance(v2)/speed, v2);
           // CCLOG("v1.x%f:v1.y%f,v2.x%f,v2.y%f,distance:%f",v1.x,v1.y,v2.x,v2.y,v1.getDistance(v2));
           
            acv.pushBack(CallFuncN::create([=](Node* pSender){
                monster*ms=static_cast<monster*>(pSender);
                ms->change_animation(v1,v2);
                
            }));
            acv.pushBack(move);
        }
    }
    return acv;
}

void HelloWorld::update(float dt){
    if (vecofm.size()==0) {
        Director::getInstance()->purgeCachedData();
       
        AnimationCache::getInstance()->destroyInstance();
        if (hurder%3==1) {
        this->removeAllChildren();
            init("test_2.tmx");}
        else if(hurder%3==2){
            this->removeAllChildren();
            init("text_3.tmx");
        }
        else if(hurder%3==0){
            this->removeAllChildren();
            init("test_1.tmx");}
    }
    for (auto i:vecofm) {
        if (!i->getParent()) {
            vecofm.eraseObject(i);
            CCLOG("size:%zd",vecofm.size());
        }
    }
    
}
void HelloWorld::create_monster(float dt){
    auto sp=monster::create();
     Vector<FiniteTimeAction*>vai=init_actioninterval(mapintv2,sp->speed);
      vai.pushBack(RemoveSelf::create());
    sp->runAction(Sequence::create(vai));
    
    sp->setPosition(beginVec);
    this->addChild(sp);
    vecofm.pushBack(sp);
}