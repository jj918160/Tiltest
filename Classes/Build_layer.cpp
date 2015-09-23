//
//  Build_layer.cpp
//  Tiltest
//
//  Created by mac on 15-8-29.
//
//

#include "Build_layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;
Scene* Build_layer::createScene(){
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Build_layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    return scene;
    
}
 bool Build_layer::init(){
     if (!Layer::init()) {
         return false;
     }
     
     auto rootNode = CSLoader::createNode("buildLayer.csb");
     this->addChild(rootNode,0,1);
    // ListView*list=(ListView*)rootNode->getChildByTag(43);
     //ImageView*iv=(ImageView*)list->getChildByTag(49);
    // ImageView*wall=(ImageView*)iv->getChildByTag(51);
    // wall->loadTexture("wall.10.3.png");
     add_item(3);
     change_stage(1,100,"1035.0.png");
     change_stage(2,200,"756.0.png");
     change_stage(3,3000,"1342.0.png");
     change_stage(0,10,"wall.10.3.png");
   
     Button*back=(Button*)rootNode->getChildByTag(46);
  
     back->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
         if(type==Widget::TouchEventType::ENDED){
             Fight_Layer::t_type=Fight_Layer::touchType::move;
             Director::getInstance()->popScene();
         }
     });
   
//     ListView*list=(ListView*)rootNode->getChildByTag(43);
//     ImageView*iv=(ImageView*)list->getItem(0);
//     Button*bt1=(Button*)iv->getChildByTag(50);
//     bt1->addTouchEventListener([=](Ref*p,Widget::TouchEventType type)
//     {
//         if(type==Widget::TouchEventType::ENDED){
//             Fight_Layer::t_type=Fight_Layer::touchType::create_wall;
//             Director::getInstance()->popScene();
//         }
//
//     });
       addtouch_event(0,Fight_Layer::touchType::create_wall);
       addtouch_event(1,Fight_Layer::touchType::create_tower);
       addtouch_event(2,Fight_Layer::touchType::create_icetower);
       addtouch_event(3,Fight_Layer::touchType::create_firetower);
     
     
     return true;
}
void Build_layer::add_item(int num){
    for (int i=0; i<num; i++)
    {
        auto rootNode=(Node*)this->getChildByTag(1);
        ListView*list=(ListView*)rootNode->getChildByTag(43);
        ImageView*iv=(ImageView*)list->getChildByTag(49);
        ImageView*newimage=(ImageView*)iv->clone();
        ImageView*t=(ImageView*)newimage->getChildByTag(51);
        list->pushBackCustomItem(newimage);
    }

}
void Build_layer::change_stage(int num,int money,std::string picname){
    auto rootNode=(Node*)this->getChildByTag(1);
    ListView*list=(ListView*)rootNode->getChildByTag(43);
    ImageView*iv=(ImageView*)list->getItem(num);
    ImageView*t=(ImageView*)iv->getChildByTag(51);
    t->loadTexture(picname);
    Text*t2=(Text*)iv->getChildByTag(52);
    char mon[64];
    sprintf(mon,"%d",money);
    t2->setText(mon);
}

void Build_layer::addtouch_event(int index,Fight_Layer::touchType ptype){
    auto rootNode=this->getChildByTag(1);
    ListView*list=(ListView*)rootNode->getChildByTag(43);
    ImageView*iv=(ImageView*)list->getItem(index);
    Button*bt1=(Button*)iv->getChildByTag(50);
    bt1->addTouchEventListener([=](Ref*p,Widget::TouchEventType type)
                               {
                                   if(type==Widget::TouchEventType::ENDED){
                                       Fight_Layer::t_type=ptype;
                                       Director::getInstance()->popScene();
                                   }
                                   
                               });

}