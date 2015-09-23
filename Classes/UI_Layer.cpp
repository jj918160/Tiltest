//
//  UI_Layer.cpp
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//
#include "Setting_Layer.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
#include"First_stage.h"
#include "Fight_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Build_layer.h"
using namespace ui;
bool UI_Layer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("Layer.csb");
    this->addChild(rootNode,0,1);
    loading_animation();
    init_control();
    
    flag=Sprite::create("2780.0.png");
    flag->setPosition(860,60);
    Sprite*temp=Sprite::create();
    temp->setPosition(flag->getContentSize()/2);
    flag->addChild(temp,0,1);
    this->addChild(flag,0);
    scheduleUpdate();
    schedule(schedule_selector(UI_Layer::update_gold),1/60);
    return true;
}
void UI_Layer::loading_animation(){
    AnimationCache*ac=AnimationCache::getInstance();
    Animation*godown=atools->makeAnimationfrommixpicture("liyb.png", 4, 4, 1, 1, 4, 1);
    ac->addAnimation(godown, "godown");
    Animation*goleft=atools->makeAnimationfrommixpicture("liyb.png", 4, 4, 1, 2, 4, 2);
    ac->addAnimation(goleft, "goleft");
    Animation*goright=atools->makeAnimationfrommixpicture("liyb.png", 4, 4, 1, 3, 4, 3);
    ac->addAnimation(goright, "goright");
    Animation*goup=atools->makeAnimationfrommixpicture("liyb.png", 4, 4, 1, 4, 4, 4);
    ac->addAnimation(goup, "goup");
    
    Animation*attdown=atools->makeAnimationfrommixpicture("guy_melee.png", 4, 4, 1, 1, 4, 1);
    ac->addAnimation(attdown, "attdown");
    Animation*attleft=atools->makeAnimationfrommixpicture("guy_melee.png", 4, 4, 1, 2, 4, 2);
    ac->addAnimation(attleft, "attleft");
    Animation*attright=atools->makeAnimationfrommixpicture("guy_melee.png", 4, 4, 1, 3, 4, 3);
    ac->addAnimation(attright, "attright");
    Animation*attup=atools->makeAnimationfrommixpicture("guy_melee.png", 4, 4, 1, 4, 4, 4);
    ac->addAnimation(attup, "attup");
    
    
    Animation*fire=atools->makeAnimationfromPlist("fire.plist", "fire_%d.png",5,0,0.2,true,-1);
    ac->addAnimation(fire,"fire");

}
void UI_Layer::init_control(){
    //建筑按钮
    
    Button*bt1=(Button*)this->getChildByTag(1)->getChildByTag(20);
    bt1->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        //放兵完毕，并且场上没兵，才能建筑
       // if (fl->poutover&&fl->vecofmon.empty()) {
        //if(type==Widget::TouchEventType::ENDED){
            
            // SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        //}
         if(type==Widget::TouchEventType::ENDED){
           
            Fitst_stage*pa=(Fitst_stage*) this->getParent();
            Fight_Layer*fl=static_cast<Fight_Layer*>(pa->getChildByTag(1));
             if (fl->poutover&&fl->vecofmon.empty()){
                Director::getInstance()->pushScene(Build_layer::createScene());
            }
            else{
                create_message();
            }
        }
       // }
//        else{
//            Label*lb=Label::createWithSystemFont("出兵中，请等待", "Arial",32);
//            lb->setPosition(480,320);
//            this->addChild(lb);
//            lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
//        }
    });
    
    //测试按钮＋
    Button*bt3=(Button*)this->getChildByTag(1)->getChildByTag(22);
    bt3->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        //放兵完毕，并且场上没兵，才能建筑
       // if (fl->poutover&&fl->vecofmon.empty()) {
        if(type==Widget::TouchEventType::BEGAN){
            // SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        }
        else if(type==Widget::TouchEventType::ENDED){
            Player*p=Player::getInstance();
            p->zhuanshi-=10;
            p->money+=1000;
            
                   }
       // }
    });
    

    
    
    //出兵按钮
    Button*bt2=(Button*)this->getChildByTag(1)->getChildByTag(21);
    bt2->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::BEGAN){
           // SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        }
        else if(type==Widget::TouchEventType::ENDED){
          //
            Fitst_stage*pa=(Fitst_stage*) this->getParent();
            pa->callback1(pa);
            Text*num_bo=(Text*)this->getChildByTag(1)->getChildByTag(19);
            Fight_Layer*ft=(Fight_Layer*)pa->getChildByTag(1);
            char bo[64];
            sprintf(bo,"第%d/%d波",ft->nowboshu,ft->boshu);
            num_bo->setText(bo);
        }
    });
    
   //设置按钮
     Button*bt4=(Button*)this->getChildByTag(1)->getChildByTag(16);
    bt4->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::BEGAN){
        Director::getInstance()->pushScene(Setting_Layer::createScene());
        }
    });
        
}
void UI_Layer::update_gold(float dt){
   // CCLOG("in1");
    Player*p=Player::getInstance();
    //CCLOG("in1");
    auto rootNode=(Node*)this->getChildByTag(1);
    //CCLOG("in1");
    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(8);
    lb1->setPercent(p->money/100);
   // CCLOG("in1");
    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(11);
    lb2->setPercent(p->emage/100);
   // CCLOG("in1");
    Text*tz=(Text*)rootNode->getChildByTag(15);
    char num[64];
    sprintf(num,"%d",p->zhuanshi);
    tz->setText(num);
   // CCLOG("in1");
    Text*tq=(Text*)rootNode->getChildByTag(9);
    char num2[64];
    sprintf(num2,"%d/10000",p->money);
    tq->setText(num2);
    //CCLOG("in1");
    Text*ts=(Text*)rootNode->getChildByTag(12);
    char num3[64];
    sprintf(num3,"%d/10000",p->emage);
    ts->setText(num3);
   // CCLOG("in1");
}
void UI_Layer::update(float dt){
    Fight_Layer*pa=(Fight_Layer*) this->getParent()->getChildByTag(1);
    //有怪的时候不支持建设
  
    if (pa->t_type==Fight_Layer::touchType::move) {
        Sprite*sp=(Sprite*)flag->getChildByTag(1);
        sp->init();
    }
    else if (pa->t_type==Fight_Layer::touchType::create_wall) {
        Sprite*sp=(Sprite*)flag->getChildByTag(1);
       // sp->init();
        sp->setScale(1,1);
        sp->initWithFile("wall.10.3.png");
    }
    else if (pa->t_type==Fight_Layer::touchType::create_tower) {
        Sprite*sp=(Sprite*)flag->getChildByTag(1);
       // sp->init();
        sp->setScale(0.5,0.5);
        sp->initWithFile("1025.0.png");
    }
    else if (pa->t_type==Fight_Layer::touchType::create_icetower) {
        Sprite*sp=(Sprite*)flag->getChildByTag(1);
        // sp->init();
        sp->setScale(0.5,0.5);
        sp->initWithFile("756.0.png");
    }
    else if (pa->t_type==Fight_Layer::touchType::create_firetower) {
        Sprite*sp=(Sprite*)flag->getChildByTag(1);
        // sp->init();
        sp->setScale(0.5,0.5);
        sp->initWithFile("1342.0.png");
    }

}

void UI_Layer::create_message(){
    Label*lb=Label::createWithSystemFont("出兵中，城主请稍后", "Arial",32);
                lb->setPosition(480,320);
                this->addChild(lb);
                lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
}
void UI_Layer::create_message(const std::string str){
    Label*lb=Label::createWithSystemFont(str,"Arial",32);
    lb->setPosition(480,320);
    this->addChild(lb);
    lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
}