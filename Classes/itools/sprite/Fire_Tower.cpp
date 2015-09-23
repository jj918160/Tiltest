//
//  Fire_Tower.cpp
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//
#include "Fire_Bullet.h"
#include "Fire_Tower.h"
#include "Csv_Parser.h"
#include "cocostudio/CocoStudio.h"
#include "build_message_layer.h"
#include "ui/CocosGUI.h"
#include "Fight_Layer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace ui;
 bool Fire_Tower::init(){
         if (!Sprite::init()) {
             return false;
         }
         onecolum=Csv_parser->read_csv_as_stringtoVector("huota.csv");
         max_lv=2;
         this->initWithFile("towerbase.png");
         auto base=Sprite::create("1342.0.png");
         base->setPosition(96,64);
         this->addChild(base,0,9);
         lv_up();
         stageopen=false;
         auto touch=EventListenerTouchOneByOne::create();
         touch->onTouchBegan=[&](Touch*ptouch,Event*pevent){
             if (stageopen) {
                 stageopen=false;
                 this->removeChildByTag(1);
             }
             if (this->getBoundingBox().containsPoint(((Node*)this->getParent())->convertToNodeSpace(ptouch->getLocation()))){
                 return true;
             }
             return false;
         };
         touch->onTouchEnded=[&](Touch*ptouch,Event*pevent)
         {
             auto rootNode = CSLoader::createNode("Node.csb");
             this->addChild(rootNode,0,1);
             Button*bt1=(Button*)rootNode->getChildByTag(4)->getChildByTag(7);
             Button*bt2=(Button*)rootNode->getChildByTag(4)->getChildByTag(8);
             bt1->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
                 switch (type) {
                     case Widget::TouchEventType::BEGAN:
                     {
                         auto bt=build_message_layer::create(this);
                         Node*t=(Node*)this->getParent()->getParent();
                         t->addChild(bt);
                         break;
                     }
                     default:
                         break;
                 }
             });
             bt2->addTouchEventListener([&](Ref*p,Widget::TouchEventType type){
                 switch (type) {
                     case Widget::TouchEventType::BEGAN:
                     {
                         
                         Fight_Layer*pa=(Fight_Layer*)this->getParent();
                         pa->vecoft.eraseObject(this);
                         this->runAction(RemoveSelf::create());
                         for(int i=-1;i<=1;i++)
                             for(int j=-1;j<=1;j++){
                                 pa->_mapgid.at(x+i).at(y+j)->setPass(true);
                             }
                     }
                         break;
                     default:
                         break;
                 }
             });
             stageopen=true;
         };
         _eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);
         scheduleUpdate();
         schedule(schedule_selector(Fire_Tower::my_update),0.02);
         schedule(schedule_selector(Fire_Tower::music_update),1);
         return true;
}
void Fire_Tower::update(float dt){
        Fight_Layer*pa=(Fight_Layer*)this->getParent();
        for (auto i:pa->vecofmon) {
            if (i->getPosition().getDistance(this->getPosition())<=att_distance&&atk_mubiao.size()<atk_num&&!i->befired) {
                i->befired=true;
                atk_mubiao.pushBack(i);
            }
        }
    
    if (!atk_mubiao.empty()) {
        
        CCLOG("zi:%zd",atk_mubiao.size());
        for (auto mon:atk_mubiao) {
            mon->hp-=this->atk;
            if (mon->hp<=0) {
                mon->hp=0;
            }
            float scale=mon->hp/mon->max_hp;
            mon->getChildByTag(1)->setScaleX(scale);
            //目标脱离条件
            if (mon->hp<=0||mon->getPosition().getDistance(this->getPosition())>att_distance) {
                mon->befired=false;
                atk_mubiao.eraseObject(mon);
            }
           
                                        }
        }
    }



void Fire_Tower::lv_up(){
    if(lv>=2){
        return;
    }
    lv++;
    ValueVector vv=Csv_parser->read_vector(onecolum.at(lv).asString());
    
    this->hp=vv.at(1).asInt();
    
    this->atk=vv.at(2).asFloat();
    
    this->atk_intervel=vv.at(3).asInt();
    
    Sprite*sp=(Sprite*)this->getChildByTag(9);
    
    const char*str=vv.at(4).asString().c_str();
    picname=str;
    sp->initWithFile(str);
    
    this->att_distance=vv.at(5).asFloat();
    this->atk_num=vv.at(6).asInt();
    this->price=vv.at(7).asInt();
}

void Fire_Tower::attack(Vector<monster*>vecofm){
    
}
void Fire_Tower::my_update(float dt){
    for(auto i:atk_mubiao){
        auto sp=Sprite::create("fire0.png");
        sp->setAnchorPoint(Vec2(0,0.5));
        Size sz=this->getContentSize();
        sp->setPosition(sz.width/2,sz.height-20);
        //设置长度
        sp->setScaleX(i->getPosition().getDistance(this->getPosition())/sp->getContentSize().width);
        //设置角度
        Vec2 off=i->getParent()->convertToWorldSpace(i->getPosition())-this->convertToWorldSpace(sp->getPosition());
        //i->getPosition()-(this->getPosition()+sp->getPosition());
        float rad=off.getAngle();
        float degre=CC_RADIANS_TO_DEGREES(rad);
        CCLOG("rad:%f",rad);
        CCLOG("degre:%f",degre);
        
        sp->setRotation(-degre);
        this->addChild(sp);
        sp->runAction(Sequence::create(DelayTime::create(0.02),RemoveSelf::create(), NULL));
    }
}
void Fire_Tower::music_update(float dt){
    if (!atk_mubiao.empty()) {
        SimpleAudioEngine::getInstance()->playEffect("bullet3.wav");
    }
}


