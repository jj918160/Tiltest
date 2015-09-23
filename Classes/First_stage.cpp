//
//  First_stage.cpp
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "First_stage.h"
#include "Fight_Layer.h"
#include "UI_Layer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace ui;
USING_NS_CC;
Scene* Fitst_stage::createScene(){
   
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Fitst_stage::create();
   
    // add layer as a child to scene
    scene->addChild(layer);

//    auto m1=MenuItemImage::create("CG-1493.png", "CG-1494.png");
//    m1->setPosition(300,300);
//    m1->setCallback(CC_CALLBACK_1(Fitst_stage::callback1,layer));
//    
//    auto m2=MenuItemImage::create("CG-1493.png", "CG-1494.png");
//    m2->setPosition(400,300);
//    m2->setCallback(CC_CALLBACK_1(Fitst_stage::callback2,layer));
//    
//    auto m3=MenuItemImage::create("CG-1493.png", "CG-1494.png");
//    m3->setPosition(500,300);
//    m3->setCallback(CC_CALLBACK_1(Fitst_stage::callback3,layer));
//    
//    auto menu=Menu::create(m1,m2,m3,NULL);
//    scene->addChild(menu,5);
    
    return scene;

}
bool Fitst_stage::init(){
   if (!Layer::init())
    {
        return false;
    }
    
   
    
    loadmusic();
    Fight_Layer*fl=Fight_Layer::create();
    this->addChild(fl,0,1);
 
    UI_Layer*ui=UI_Layer::create();
    this->addChild(ui,1,2);
    
    Text*num_bo=(Text*)ui->getChildByTag(1)->getChildByTag(19);
    char bo[64];
       sprintf(bo,"第%d/%d波",fl->nowboshu,fl->boshu);
        num_bo->setText(bo);
    
    //初始化关卡关数
//    Fitst_stage*pa=(Fitst_stage*) this->getParent();
//    Text*num_bo=(Text*)rootNode->getChildByTag(19);
//    Fight_Layer*ft=(Fight_Layer*)pa->getChildByTag(1);
//    char bo[64];
//    sprintf(bo,"第%d/%d波",ft->nowboshu,ft->boshu);
//    num_bo->setText(bo);
    
    scheduleUpdate();
    return true;
}
void Fitst_stage::callback1(Ref* psender){
    Fight_Layer*f=static_cast<Fight_Layer*>(this->getChildByTag(1));
    f->callback1(psender);
}

void Fitst_stage::loadmusic(){
    SimpleAudioEngine::getInstance()->preloadEffect("barbarian_death_02.m4r");
    SimpleAudioEngine::getInstance()->preloadEffect(" training_finished_03.m4r");
    SimpleAudioEngine::getInstance()->preloadEffect("bullet2.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("bullet3.wav");
     SimpleAudioEngine::getInstance()->preloadEffect("fire.wav");
  SimpleAudioEngine::getInstance()->preloadEffect("bottle_break_04_lightning_01.m4r");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("fight.mp3");
}


void Fitst_stage::update(float dt){
    Fight_Layer*fl=static_cast<Fight_Layer*>(this->getChildByTag(1));
    if (fl->game_over) {
        CCLOG("you Lose");
        Label*lb=Label::createWithSystemFont("YOULOSE!", "Arial",48);
        lb->setPosition(480,320);
        addChild(lb);
        
        Label*ttback=Label::create("返回", "Helvetica_Blod", 23);
        MenuItemLabel *menuLabel=MenuItemLabel::create(ttback, this, menu_selector(Fitst_stage::back_game));
        menuLabel->setPosition(0,-200);
        
        Menu*menu=Menu::create(menuLabel,NULL);
      
        addChild(menu,100);
        
        Director::getInstance()->pause();

        
    }
    if (fl->game_win||(fl->vecofmon.size()==0&&fl->nowboshu>fl->boshu)) {
         CCLOG("you Win");
        Label*lb=Label::createWithSystemFont("YOUWIN!", "Arial",48);
        lb->setPosition(480,320);
        addChild(lb);

        Label*ttback=Label::create("返回", "Helvetica_Blod", 23);
        MenuItemLabel *menuLabel=MenuItemLabel::create(ttback, this, menu_selector(Fitst_stage::back_game));
        menuLabel->setPosition(0,-200);
        
        Menu*menu=Menu::create(menuLabel,NULL);
        
        addChild(menu,100);

         Director::getInstance()->pause();
    }
    
}


void Fitst_stage::back_game(Ref *sender){
    this->unscheduleAllSelectors();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5,Fitst_stage::createScene()));

}
 //void Fitst_stage::onEnterTransitionDidFinish(){
 //    Layer::onEnterTransitionDidFinish();
   
//}

//void Fitst_stage::callback2(Ref* psender){
//    Fight_Layer*f=static_cast<Fight_Layer*>(this->getChildByTag(1));
//    f->callback2(psender);
//}
//void Fitst_stage::callback3(Ref* psender){
//    Fight_Layer*f=static_cast<Fight_Layer*>(this->getChildByTag(1));
//    f->callback3(psender);
//}