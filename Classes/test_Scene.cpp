//
//  test_Scene.cpp
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//

#include "test_Scene.h"
#include "Moster.h"
#include "PathArithmetic.h"
#include "A_statPath.h"
Scene* tese_Scene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = tese_Scene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool tese_Scene::init(const char* xmlfilename){
    if ( !Layer::init() )
    {
        return false;
    }
    TMXTiledMap*map=TMXTiledMap::create("test_1.tmx");
    addChild(map,0,1);

    //Size mapsize=map->getMapSize();

    //for (int i=0; i<mapsize.width; i++) {
        //Vector<Gird*> temp;
      //  for (int j=0; j<mapsize.height; j++) {
           // Gird*gd=Gird::create(i,j);
            //temp.pushBack(gd);
      //  }
        //_mapgid.push_back(temp);
   // }
    //Vector<CustomPoint*>usev;
   // usev=patol->getPath(Vec2(0,0), Vec2(10,10), _mapgid,mapsize);
//    for (auto i:usev) {
//        CCLOG("x:%f,y:%f",i->getX(),i->getY());
//    }
    
    
    return true;
}
bool tese_Scene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    bornP=Vec2(2,2);
    destination=Vec2(18,2);
    
    TMXTiledMap*map=TMXTiledMap::create("test_2.tmx");
    addChild(map,0,1);
    
    patol=new PathArithmetic();
    asptol=new A_starPath();
    
    Size mapsize=map->getMapSize();
    for (int i=0; i<mapsize.width; i++) {
    Vector<Gird*> temp;
      for (int j=0; j<mapsize.height; j++) {
     Gird*gd=Gird::create(i,j);
    temp.pushBack(gd);
      }
    _mapgid.push_back(temp);
     }

//    Vector<CustomPoint*>usev;
//    usev=patol->getPath(Vec2(0,0), Vec2(10,10), _mapgid,mapsize);
//       for (auto i:usev) {
//            CCLOG("x:%f,y:%f",i->getX(),i->getY());
//        }
//    Vector<PointNode*>pnt;
//    pnt=asptol->getPath(Vec2(2,2),Vec2(15,15),_mapgid, mapsize);
//    
//           for (auto i:pnt) {
//                CCLOG("x:%f,y:%f",i->getX(),i->getY());
//            }

// B星系统
//    auto listener=EventListenerTouchOneByOne::create();
//    listener->onTouchBegan=[=](Touch*ptouch,Event*pevent){
//       
//        Size tilesize=map->getTileSize();
//        Vec2 t=ptouch->getLocationInView();
//        Vec2 map_p((int)(t.x/tilesize.width),(int)(t.y/tilesize.height));
//        if (!_mapgid.at(map_p.x).at(map_p.y)->getPass()) {
//            CCLOG("不能重复建造");
//            return true;
//        }
//        
//        Rect re(0,0,48,64);
//        auto sp=Sprite::create("guy.png", re);
//        sp->setScale(tilesize.width/64, tilesize.height/64);
//               TMXLayer *pp=map->getLayer("first_layer");
//        sp->setPosition(pp->getPositionAt(map_p)+tilesize/2);
//        this->addChild(sp);
//        //置为障碍。
//        _mapgid.at(map_p.x).at(map_p.y)->setPass(false);
//        Vector<CustomPoint*>usev;
//        usev=patol->getPath(Vec2(0,0), Vec2(0,10), _mapgid,mapsize);
//        if (usev.empty()) {
//            CCLOG("没路可走");
//        }
//        CCLOG("---begin-----");
//        for (auto i:usev) {
//            
//            CCLOG("x:%f,y:%f",i->getX(),i->getY());
//        }
//            CCLOG("----end----");
//      
//        return true;
//    };
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    //     A星系统
        auto listener=EventListenerTouchOneByOne::create();
        listener->onTouchBegan=[=](Touch*ptouch,Event*pevent){
    
            Size tilesize=map->getTileSize();
            Vec2 t=ptouch->getLocationInView();
            Vec2 map_p((int)(t.x/tilesize.width),(int)(t.y/tilesize.height));
            if (!_mapgid.at(map_p.x).at(map_p.y)->getPass()) {
                CCLOG("不能重复建造");
                return true;
            }
    
            Rect re(0,0,48,64);
            auto sp=Sprite::create("guy.png", re);
            sp->setScale(tilesize.width/64, tilesize.height/64);
                   TMXLayer *pp=map->getLayer("first_layer");
            sp->setPosition(pp->getPositionAt(map_p)+tilesize/2);
            this->addChild(sp);
            //置为障碍。
            _mapgid.at(map_p.x).at(map_p.y)->setPass(false);
            //A*测试代码
//            Vector<PointNode*>usev;
//            usev=asptol->getPath(bornP, destination, _mapgid,mapsize);
//            if (usev.empty()) {
//                CCLOG("没路可走");
//            }
//            CCLOG("---begin-----");
//            for (auto i:usev) {
//    
//                CCLOG("x:%f,y:%f",i->getX(),i->getY());
//            }
//                CCLOG("----end----");
          
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //添加控制按钮
    auto m1=MenuItemImage::create("CG-1493.png", "CG-1494.png");
    m1->setPosition(300,300);
    m1->setCallback(CC_CALLBACK_1(tese_Scene::callback1,this));
    
  
  
    auto menu=Menu::create(m1,NULL);
    this->addChild(menu,5);
    
    return true;
}
void tese_Scene::callback1(Ref* psender){
    TMXTiledMap* map=(TMXTiledMap*)this->getChildByTag(1);
    Size mapsize=map->getMapSize();
    TMXLayer *pp=map->getLayer("first_layer");
    Size tilesize=map->getTileSize();
    beginpoint=Vec2(pp->getPositionAt(bornP)+tilesize/2);
    path_vector=asptol->getPath(bornP,destination,_mapgid, mapsize,tilesize);
    CCLOG("pnt:size%zd",path_vector.size());
    schedule(schedule_selector(tese_Scene::create_monster), 0.5, 15, 1);
}
void tese_Scene::create_monster(float dt){
 
    auto sp=monster::create();
    sp->setPosition(beginpoint);
    this->addChild(sp);

    

 
    Vector<FiniteTimeAction*>vai=sp->init_actioninterval(path_vector,sp->speed);
    
    vai.pushBack(RemoveSelf::create());
    sp->runAction(Sequence::create(vai));
  
 
    
    

}

tese_Scene::~tese_Scene(){
    patol->release();
    patol=nullptr;
    asptol->release();
    asptol=nullptr;
}