//
//  build_message_layer.cpp
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//

#include "build_message_layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "UI_Layer.h"
using namespace ui;
//塔
build_message_layer* build_message_layer::create(Tower*t)
{
    build_message_layer *pRet = new(std::nothrow) build_message_layer();
    if (pRet && pRet->init(t))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool build_message_layer::init(Tower*t){
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("message.csb");
    this->addChild(rootNode,0,1);
    load_tower(t);
        //初始化按钮
    Button*bt=(Button*)rootNode->getChildByTag(27);
    
      bt->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
          if (type==Widget::TouchEventType::BEGAN) {
            
          }
          //升级按钮
         else if(type==Widget::TouchEventType::ENDED){
             Player*p=Player::getInstance();
             if (p->money<t->price) {
                 //没有足够的金钱升级
                 //这个界面是挂在主场景上的
                 UI_Layer*uir=(UI_Layer*)this->getParent()->getChildByTag(2);
                 uir->create_message("没有足够的金钱升级");
                   this->runAction(RemoveSelf::create());
             }
             else if(t->lv>=t->max_lv){
                 //已经到达等级上限
                 UI_Layer*uir=(UI_Layer*)this->getParent()->getChildByTag(2);
                 uir->create_message("已经到达等级上限");

                 this->runAction(RemoveSelf::create());
             }
             else{
             p->money-=t->price;
             t->lv_up();
            this->runAction(RemoveSelf::create());
             }
        }
                      });
    
    Button*bt2=(Button*)rootNode->getChildByTag(52);
    
    bt2->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            this->runAction(RemoveSelf::create());
        }
    });

    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[&](Touch*touch,Event*event){
        Node* rootNode=static_cast<Node*>(this->getChildByTag(1));
        //加载图片
        ImageView*pic=(ImageView*)rootNode->getChildByTag(26);
        if (Rect(100,100,760,440).containsPoint(touch->getLocation())) {

           return true;
        }
        this->runAction(RemoveSelf::create());
        _eventDispatcher->removeEventListener(listener);
                return false;
    };
    
    listener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
 
    

    
    return true;
}
//怪
build_message_layer* build_message_layer::create(monster*mon)
{
    build_message_layer *pRet = new(std::nothrow) build_message_layer();
    if (pRet && pRet->init(mon))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool build_message_layer::init(monster*mon){
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}

//墙
build_message_layer* build_message_layer::create(Wall*wall)
{
    build_message_layer *pRet = new(std::nothrow) build_message_layer();
    if (pRet && pRet->init(wall))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool build_message_layer::init(Wall*wall){
    if (!Layer::init()) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("message.csb");
    this->addChild(rootNode,0,1);
    load_wall(wall);
    
    //初始化按钮
    Button*bt=(Button*)rootNode->getChildByTag(27);
    
    bt->setVisible(false);
    
    Button*bt2=(Button*)rootNode->getChildByTag(52);
    
    bt2->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::ENDED){
            this->runAction(RemoveSelf::create());
        }
    });
    
    
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[&](Touch*touch,Event*event){
        Node* rootNode=static_cast<Node*>(this->getChildByTag(1));
        //加载图片
        ImageView*pic=(ImageView*)rootNode->getChildByTag(26);
        if (Rect(100,100,760,440).containsPoint(touch->getLocation())) {
            return true;
        }
        this->runAction(RemoveSelf::create());
        _eventDispatcher->removeEventListener(listener);
        return false;
    };
    
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void build_message_layer::load_tower(Tower*t){
    
    Node* rootNode=static_cast<Node*>(this->getChildByTag(1));
    //加载图片
    ImageView*tower_pic=(ImageView*)rootNode->getChildByTag(47);
    tower_pic->loadTexture(t->picname);
    //加载等级：
    Text*test1=(Text*)rootNode->getChildByTag(50);
    char name[64];
    sprintf(name,"箭塔(等级%d)",t->lv);
    test1->setText(name);
    //加载血条和伤害条以及文字
    //血量文字:
    Text*t_hp=(Text*)rootNode->getChildByTag(48);
    char name1[64];
    sprintf(name1,"血量:%d",t->hp);
    t_hp->setText(name1);
    //伤害文字
    Text*t_atk=(Text*)rootNode->getChildByTag(49);
    char name2[64];
    sprintf(name2,"伤害:%f",t->atk);
    t_atk->setText(name2);
    //攻击范围文字
    Text*fanwei=(Text*)rootNode->getChildByTag(39);
    char name3[64];
    sprintf(name3,"%d",(int)t->att_distance);
    fanwei->setText(name3);
    //升级所需金钱
    Text*money=(Text*)rootNode->getChildByTag(28);
    char name4[64];
    sprintf(name4,"%d",t->price);
    money->setText(name4);
    //加载血量条：
    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(45);
    lb1->setPercent(t->hp/10.f);
    //加载伤害：
    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(46);
    lb2->setPercent(t->atk*2);

}

void build_message_layer::load_wall(Wall*wall){
    Node* rootNode=static_cast<Node*>(this->getChildByTag(1));
    //加载图片
    ImageView*tower_pic=(ImageView*)rootNode->getChildByTag(47);
    tower_pic->loadTexture(wall->picname);
    //加载等级：
    Text*test1=(Text*)rootNode->getChildByTag(50);
    char name[64];
    sprintf(name,"墙(等级%d)",wall->lv);
    test1->setText(name);
    //加载血条和伤害条以及文字
    //血量文字:
    Text*t_hp=(Text*)rootNode->getChildByTag(48);
    char name1[64];
    sprintf(name1,"血量:%d",wall->hp);
    t_hp->setText(name1);
    //伤害文字
    Text*t_atk=(Text*)rootNode->getChildByTag(49);
    t_atk->setVisible(false);
    //攻击范围文字
    Text*fanwei=(Text*)rootNode->getChildByTag(39);
    fanwei->setVisible(false);
    //升级所需金钱
    Text*money=(Text*)rootNode->getChildByTag(28);
    money->setVisible(false);
        //加载血量条：
    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(45);
    lb1->setPercent(100);
    //加载伤害：
    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(46);
    lb2->setVisible(false);


}
