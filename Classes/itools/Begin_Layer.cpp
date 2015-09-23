//
//  Begin_Layer.cpp
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//
#include "First_stage.h"
#include "Begin_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
Scene* Begin_Layer::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Begin_Layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Begin_Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
     SimpleAudioEngine::getInstance()->preloadEffect("loading_screen.m4r");
    auto  rootNode=CSLoader::createNode("begin.csb");
    addChild(rootNode,0,1);
    rootNode->getChildByTag(20)->setVisible(false);
    Sprite*sp=static_cast<Sprite*>(rootNode->getChildByTag(23));
    sp->setOpacity(0);
   // this->addChild(sp);
    
    sp->runAction(Sequence::create(DelayTime::create(0.5),FadeIn::create(1.f),DelayTime::create(1.f),FadeOut::create(1.f),CallFuncN::create([=](Node* pSender){
        sp->setVisible(false);
          SimpleAudioEngine::getInstance()->playEffect("loading_screen.m4r");
     ImageView*bg=static_cast<ImageView*>(rootNode->getChildByTag(20));
        bg->setVisible(true);
        scheduleUpdate();
    })
                                   , NULL));
    
    
    
    return true;
}

void Begin_Layer::update(float dt){
    Node*rootNode=this->getChildByTag(1);
     ImageView*sp=static_cast<ImageView*>(rootNode->getChildByTag(20));
    Slider*sld=(Slider*)sp->getChildByTag(22);
    if (sld->getPercent()>=100) {
        Director::getInstance()->replaceScene(Fitst_stage::createScene());
    }
    sld->setPercent(sld->getPercent()+1);
}
