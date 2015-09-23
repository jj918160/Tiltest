//
//  Moster.cpp
//  Tiltest
//
//  Created by mac on 15-8-13.
//
//
#include "SimpleAudioEngine.h"
#include "Moster.h"
#include "A_statPath.h"
#include "Fight_Layer.h"
#include "Player.h"
using namespace CocosDenshion;

//void monster::load_animation(){
//    
//    
//}

bool monster::init(){
    if (!Sprite::init()) {
        return false;
    }

    befired=false;
    spd_cutcd=0;
    speed_cut=false;
    boshu=0;
    speed=100;
    hp=0;
    max_hp=1;
   // load_animation();
    
    a=Animate::create(AnimationCache::getInstance()->getAnimation("goright"));
    runAction(a);
    
    auto hpbk=Sprite::create("hp_back.png");
    hpbk->setPosition(32,64);
    this->addChild(hpbk);
    
    auto hpft=Sprite::create("hp_now.png");
    hpft->setPosition(0,64);
    hpft->setAnchorPoint(Vec2(0,0.5));
    this->addChild(hpft,0,1);
    
    scheduleUpdate();
    return true;
}
void monster::change_animation(Vec2 v1,Vec2 v2){
    
    float absx=abs((float)(v2.x-v1.x));
     float absy=abs((float)(v2.y-v1.y));
    DirecTion temp=_direction;
    DirecTion temp2;
    if (absx>=absy&&v2.x>=v1.x) {
        temp2=DirecTion::right;
    }
    //左
    else if (absx>=absy&&v2.x<v1.x) {
        temp2=DirecTion::left;
        //CCLOG("left");
    }
    //上
    
    else if (absx<absy&&v2.y>=v1.y) {
        
        temp2=DirecTion::up;
      
        // CCLOG("up");
    }
    //下
    else if (absx<absy&&v2.y<v1.y) {
        temp2=DirecTion::down;
        //CCLOG("down");
    }
    if (temp==temp2) {
        return;
    }
    
    stopAction(a);
    //CCLOG("in");
    if (absx>=absy&&v2.x>=v1.x) {
        a=Animate::create(AnimationCache::getInstance()->getAnimation("goright"));
        _direction=DirecTion::right;
        runAction(a);
       // CCLOG("right");
    }
    //左
    else if (absx>=absy&&v2.x<v1.x) {
        a=Animate::create(AnimationCache::getInstance()->getAnimation("goleft"));
        _direction=DirecTion::left;
        runAction(a);
//CCLOG("left");
    }
    //上
   
    else if (absx<absy&&v2.y>=v1.y) {
       a=Animate::create(AnimationCache::getInstance()->getAnimation("goup"));
        _direction=DirecTion::up;
        runAction(a);
       // CCLOG("up");
    }
    //下
    else if (absx<absy&&v2.y<v1.y) {
        a=Animate::create(AnimationCache::getInstance()->getAnimation("godown"));
       _direction=DirecTion::down;
        runAction(a);
      //CCLOG("down");
    }
}
//无障碍情况
Vector<FiniteTimeAction*> monster::init_actioninterval(Vector<PointNode*>vpn,float speed){
    Vector<FiniteTimeAction*>acv;
    for(auto it:vpn)
    {
        if (it->parent) {
         
            TMXTiledMap* tilmap=(TMXTiledMap*)this->getParent()->getChildByTag(1);
          
            Size size=tilmap->getTileSize();
           
             Vec2 v1t(it->parent->getX(),it->parent->getY());
             Vec2 v2t(it->getX(),it->getY());
           
            TMXLayer *pp=tilmap->getLayer("layer1");
       
            Vec2 v1(pp->getPositionAt(v1t)+size/2);
            Vec2 v2(pp->getPositionAt(v2t)+size/2);
//            CCLOG("qidianint%f,%f",v2t.x,v2t.y);
//            CCLOG("zhongdianint%f,%f",v1t.x,v1t.y);
//            CCLOG("qidian:%f,%f",v2.x,v2.y);
//            CCLOG("zongdian:%f,%f",v1.x,v1.y);
//            CCLOG("time:%f",v1.getDistance(v2)/speed);
//            CCLOG("speed:%f",speed);
//            CCLOG("distance:%f",v1.getDistance(v2));
             FiniteTimeAction*move=MoveTo::create(v1.getDistance(v2)/speed, v2);
              acv.pushBack(CallFuncN::create([=](Node* pSender){
                monster*ms=static_cast<monster*>(pSender);
                int zrd=v2t.x+v2t.y;
                ms->setZOrder(zrd);
                ms->change_animation(v1,v2);
                
            }));
            acv.pushBack(move);
        }
    }
    return acv;
}

//有障碍的情况
//Vector<FiniteTimeAction*> monster::init_actioninterval_nopath(Vector<PointNode*>path,Vector<PointNode*>attack,float speed){
//      Vector<FiniteTimeAction*>acv;
//    while (attack.size()>=1) {
//        PointNode*t1=attack.front();
//        attack.eraseObject(t1);
//         PointNode*t2=attack.front();
//        TMXTiledMap* tilmap=(TMXTiledMap*)this->getParent()->getChildByTag(1);
//        Size size=tilmap->getTileSize();
//        //获取两个点
//        Vec2 v1t(t1->getX(),t1->getY());
//        Vec2 v2t(t2->getX(),t2->getY());
//        TMXLayer *pp=tilmap->getLayer("layer1");
//        //转换为像素坐标
//        Vec2 v1(pp->getPositionAt(v1t)+size/2);
//        Vec2 v2(pp->getPositionAt(v2t)+size/2);
//        
//        FiniteTimeAction*move=MoveTo::create(v2.getDistance(v1)/speed,v2);
//        acv.pushBack(move);
//        
//        acv.pushBack(CallFuncN::create([=](Node* pSender){
//            monster*ms=static_cast<monster*>(pSender);
//            int zrd=v2t.x+v2t.y;
//            ms->setZOrder(zrd);
//            ms->change_animation(v1,v2);
//           // ms->fight_animation();
//            
//        }));
//        acv.pushBack(move);
//        
//        acv.pushBack(CallFuncN::create([=](Node* pSender){
//            monster*ms=static_cast<monster*>(pSender);
//            int zrd=v2t.x+v2t.y;
//            ms->setZOrder(zrd);
//            ms->fight_animation();
//            
//        }));
//        acv.pushBack(DelayTime::create(2.f));
//    }
//  
//    //将后续的点加入数组
//    for(auto it:path)
//    {
//        if (it->parent) {
//            
//            TMXTiledMap* tilmap=(TMXTiledMap*)this->getParent()->getChildByTag(1);
//            
//            Size size=tilmap->getTileSize();
//            
//            Vec2 v1t(it->parent->getX(),it->parent->getY());
//            Vec2 v2t(it->getX(),it->getY());
//            
//            TMXLayer *pp=tilmap->getLayer("layer1");
//            
//            Vec2 v1(pp->getPositionAt(v1t)+size/2);
//            Vec2 v2(pp->getPositionAt(v2t)+size/2);
//            FiniteTimeAction*move=MoveTo::create(v1.getDistance(v2)/speed, v2);
//            acv.pushBack(CallFuncN::create([=](Node* pSender){
//                monster*ms=static_cast<monster*>(pSender);
//                int zrd=v2t.x+v2t.y;
//                ms->setZOrder(zrd);
//                ms->change_animation(v1,v2);
//                
//            }));
//            acv.pushBack(move);
//        }
//    }
//    return acv;
//}




void monster::update(float dt){
    if (speed_cut) {
        this->setColor(Color3B(0,0,255));
    if (spd_cutcd>0) {
        spd_cutcd--;
    }
    else{
        this->setColor(Color3B(255,255,255));
        Speed*spd=(Speed*)this->getActionByTag(10);
        spd->setSpeed(speed_cut);
        this->speed_cut=false;
        }
    }
    if (this->hp<=0) {
        Player::getInstance()->money+=this->boshu*30;
        Fight_Layer*fl=(Fight_Layer*)this->getParent();
        //播放音效
        SimpleAudioEngine::getInstance()->playEffect("barbarian_death_02.m4r");
        fl->vecofmon.eraseObject(this);
        this->runAction(RemoveSelf::create());
    }
}
//void monster::fight_animation(){
//    this->stopAction(a);
//    switch (_direction) {
//        case DirecTion::down:
//             a=Animate::create(AnimationCache::getInstance()->getAnimation("attdown"));
//            break;
//        case DirecTion::left:
//             a=Animate::create(AnimationCache::getInstance()->getAnimation("attleft"));
//            break;
//        case DirecTion::right:
//             a=Animate::create(AnimationCache::getInstance()->getAnimation("attright"));
//            break;
//        case DirecTion::up:
//             a=Animate::create(AnimationCache::getInstance()->getAnimation("attup"));
//            break;
//            
//        default:
//            break;
//    }
//    this->runAction(a);
//}
