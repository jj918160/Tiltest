//
//  ice_Tower.cpp
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#include "ice_Tower.h"
#include "Csv_Parser.h"
#include "cocostudio/CocoStudio.h"
#include "build_message_layer.h"
#include "ui/CocosGUI.h"
#include "Fight_Layer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace ui;
bool ice_Tower::init(){
    if (!Sprite::init()) {
        return false;
    }
    
    onecolum=Csv_parser->read_csv_as_stringtoVector("bingta.csv");
    max_lv=7;
    this->initWithFile("towerbase.png");
    auto base=Sprite::create("756.0.png");
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
     //touch->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);
    return true;

}

//发射子弹打怪
void ice_Tower::attack(Vector<monster*>vecofm){
    scheduleUpdate();
    //  CCLOG("m:size:%zd",vecofm.size());
    for(auto i:vecofm)
    {
        if (i->getPosition().getDistance(this->getPosition())<=att_distance&&CD>=atk_intervel) {
      SimpleAudioEngine::getInstance()->playEffect("bullet3.wav");
            CD=0;
            auto sp=Sprite::create("2231.0.png");
            sp->setPosition(96,100);
            //粒子特效
            ParticleFire* particle=ParticleFire::create();
            particle->setStartColor(Color4F(0,0,1,1));
            particle->setEndColor(Color4F(0,0,1,1));
            particle->setDuration(2);
            particle->setPosition(sp->getContentSize()/2);
            particle->setScale(0.5);
            sp->addChild(particle,3);
            //
            auto pa=this->getParent();
            Vec2 pot=this->convertToNodeSpace(pa->convertToWorldSpace(i->getPosition()));
            //消失
            
            sp->runAction(Sequence::create(MoveTo::create(0.2,pot),
                                           RemoveSelf::create(),NULL));
            //减血
            
            i->runAction(Sequence::create(DelayTime::create(0.1),
                                          CallFuncN::create([=](Node* pSender){
                monster*m=(monster*)pSender;
                m->hp-=this->atk;
                if (m->hp<=0) {
                    m->hp=0;
                }
                float scale=m->hp/m->max_hp;
                m->getChildByTag(1)->setScaleX(scale);
                Speed*spd=(Speed*)i->getActionByTag(10);
                spd->setSpeed(speed_cut);
                m->speed_cut=true;
                m->spd_cutcd=this->lv*10;
            }),
                                          NULL));
            
            
            this->addChild(sp);
            return;
        }
    }
}

void ice_Tower::lv_up(){
    if(lv>=7){
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
    this->speed_cut=vv.at(6).asFloat();
    this->price=vv.at(7).asInt();
    
}

