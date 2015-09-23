//
//  Wall.cpp
//  Tiltest
//
//  Created by mac on 15-8-25.
//
//

#include "Wall.h"
#include "PathArithmetic.h"
#include "Fight_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "build_message_layer.h"
#include "ui/CocosGUI.h"
using namespace ui;
bool Wall::init(){
    if (!Sprite::init()) {
        return false;
    }
    price=10;
    picname="wall.10.3.png";
    hp=200;
    lv=1;
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
        bt2->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
            switch (type) {
                case Widget::TouchEventType::BEGAN:
                {
                    this->runAction(RemoveSelf::create());
                    Fight_Layer*pa=(Fight_Layer*)this->getParent();
                    Wall*wal=(Wall*)p;
                    pa->vecofw.eraseObject(wal);
                    pa->_mapgid.at(x).at(y)->setPass(true);
                    
                }
                    break;
                default:
                    break;
            }
        });

        
        stageopen=true;
    };
    touch->setSwallowTouches(true);
 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch,this);
    return true;
}
void Wall::wallchange(int x,int y,std::vector<Vector<Gird*>> _mapgid)
{
    if (_mapgid.at(x).at(y)->getPass()==false) {
//        //无法建造，二重保险，一般不触发
//            Label*lb=Label::createWithSystemFont("无法建造，请重新选择位置", "Arial",32);
//            lb->setPosition(480,320);
//            Node*pa=(Node*)this->getParent()->getParent();
//            pa->addChild(lb);
//            lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));

        return;
    }
    //两个边上
    this->x=x;
    this->y=y;
    if (x==0||y==0) {
        initWithFile("wall.10.3.png");
    }
    else
    {
        changed(x,y,_mapgid);
    }
}
void Wall::changed(int x,int y,std::vector<Vector<Gird*>> _mapgid){
    //都无墙
    if (_mapgid.at(x).at(y-1)->getPass()&&_mapgid.at(x-1).at(y)->getPass()) {
        initWithFile("wall.10.3.png");
    }
    //都有墙
    else if (!_mapgid.at(x).at(y-1)->getPass()&&!_mapgid.at(x-1).at(y)->getPass()) {
        initWithFile("wall.10.0.png");
    }
    //y-1有，x-1没有
    else if (!_mapgid.at(x-1).at(y)->getPass()&&_mapgid.at(x).at(y-1)->getPass()) {
        initWithFile("wall.10.1.png");
        setFlippedX(true);
    }
    //y-1没有，x-1有
    else if (_mapgid.at(x-1).at(y)->getPass()&&!_mapgid.at(x).at(y-1)->getPass()) {
        initWithFile("wall.10.1.png");
    }

}
