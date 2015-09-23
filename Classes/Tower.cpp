//
//  Tower.cpp
//  Tiltest
//
//  Created by mac on 15-8-25.
//
//

#include "Fight_Layer.h"
#include "Tower.h"
#include "PathArithmetic.h"
#include "Csv_Parser.h"
#include "cocostudio/CocoStudio.h"
#include "build_message_layer.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace ui;
bool Tower::init(){
    if (!Sprite::init()) {
        return false;
    }

    onecolum=Csv_parser->read_csv_as_stringtoVector("jianta.csv");
    max_lv=onecolum.size()-1;
  //  CCLOG("size:%zd",onecolum.size());
//    att_distance=200;
//    atk_intervel=30;
//    CD=atk_intervel;
//    atk=10.f;
//    hp=150;
//    lv=1;
    this->initWithFile("towerbase.png");
    auto base=Sprite::create("1025.0.png");
    base->setPosition(96,64);
    this->addChild(base,0,9);
    price=0;
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
        this->addChild(rootNode,20,1);
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
                    //Tower*tow=(Tower*)p;
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
   // touch->setSwallowTouches(true);
    //touch->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);
    return true;
}
bool Tower::cancreate(int x,int y,std::vector<Vector<Gird*>> _mapgid)
{
    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1;j++) {
            if (!_mapgid.at(x+i).at(y+j)->getPass()) {
                return false;
            }
        }
    }
    return true;
}

void Tower::attack(Vector<monster*>vecofm){
     scheduleUpdate();
  //  CCLOG("m:size:%zd",vecofm.size());
    for(auto i:vecofm)
    {
        if (i->getPosition().getDistance(this->getPosition())<=att_distance&&CD>=atk_intervel) {
          SimpleAudioEngine::getInstance()->playEffect("bullet2.wav");
            CD=0;
            auto sp=Sprite::create("2231.0.png");
            sp->setPosition(96,100);
            //粒子特效
            auto particle=ParticleFire::create();
            particle->setDuration(2);
            particle->setPosition(sp->getContentSize()/2);
            particle->setScale(0.5);
            sp->addChild(particle,3);
            //
            //CCLOG("fire");
            auto pa=this->getParent();
            Vec2 pot=this->convertToNodeSpace(pa->convertToWorldSpace(i->getPosition()));
           // CCLOG("fire");
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
            }),
                                          NULL));
            
        
            this->addChild(sp);
            return;
        }
    }
}
void Tower::update(float dt){
    if (CD<=atk_intervel) {
        CD++;
    }
}
void Tower::lv_up(){
    if(lv>=10){
        return;
    }

    lv++;
    ValueVector vv=Csv_parser->read_vector(onecolum.at(lv).asString());
    
    this->price=vv.at(6).asInt();
    
    this->hp=vv.at(1).asInt();
  
    this->atk=vv.at(2).asFloat();

    this->atk_intervel=vv.at(3).asInt();

    Sprite*sp=(Sprite*)this->getChildByTag(9);
   
    const char*str=vv.at(4).asString().c_str();
    picname=str;
    sp->initWithFile(str);

    this->att_distance=vv.at(5).asFloat();
   
}
