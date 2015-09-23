//
//  Setting_Layer.cpp
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#include "Setting_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;
//using namespace cocostudio::timeline;
using namespace CocosDenshion;
Scene* Setting_Layer::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Setting_Layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Setting_Layer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
 
    auto rootNode = CSLoader::createNode("MainScene2.csb");
    
    addChild(rootNode,0,1);
    
    Button*bt=(Button*)rootNode->getChildByTag(13);
    bt->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
         if(type==Widget::TouchEventType::BEGAN){
             SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
         }
        else if(type==Widget::TouchEventType::ENDED){
          
            UserDefault::getInstance()->setFloatForKey("music", SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
            UserDefault::getInstance()->setFloatForKey("effict", SimpleAudioEngine::getInstance()->getEffectsVolume());
            
                CCUserDefault::sharedUserDefault()->flush();
           
            
              log("%s", FileUtils::getInstance()->getWritablePath().c_str());
            
            CCLOG("xml:%s",UserDefault::getInstance()->getXMLFilePath().c_str());
            Director::getInstance()->popScene();
        }
    });
    
    
    
    CheckBox*cb1=(CheckBox*)rootNode->getChildByTag(1);
    
    cb1->addEventListener([=](Ref*p,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
                break;
            case CheckBox::EventType::UNSELECTED:
                 SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
                break;
            default:
                break;
        }
    });
    if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        cb1->setSelected(false);
    }

 
    
    CheckBox*cb2=(CheckBox*)rootNode->getChildByTag(6);
    
    cb2->addEventListener([=](Ref*p,CheckBox::EventType type){
        switch (type) {
            case CheckBox::EventType::SELECTED:
                SimpleAudioEngine::getInstance()->setEffectsVolume(100);
                break;
            case CheckBox::EventType::UNSELECTED:
                SimpleAudioEngine::getInstance()->setEffectsVolume(0);
                break;
            default:
                break;
        }
    });

    if (SimpleAudioEngine::getInstance()->getEffectsVolume()==0) {
        cb2->setSelected(false);
    }
    
     Slider*sd1=(Slider*)rootNode->getChildByTag(3);
    
    sd1->addEventListener([=](Ref*p,Slider::EventType type){
        if(type==Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            float t=sd1->getPercent()/100.f;
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(t);
        }
    });
    sd1->setPercent( SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()*100);
    
    Slider*sd2=(Slider*)rootNode->getChildByTag(4);
    
    sd2->addEventListener([=](Ref*p,Slider::EventType type){
        if(type==Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
              float t=sd2->getPercent()/100.f;
            SimpleAudioEngine::getInstance()->setEffectsVolume(t);
        }
    });
 sd2->setPercent( SimpleAudioEngine::getInstance()->getEffectsVolume()*100);
    
    
    return true;
}




