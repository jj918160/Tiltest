//
//  Build_layer.h
//  Tiltest
//
//  Created by mac on 15-8-29.
//
//

#ifndef __Tiltest__Build_layer__
#define __Tiltest__Build_layer__

#include <stdio.h>
#include "cocos2d.h"
#include "Fight_Layer.h"
USING_NS_CC;

class Build_layer:public Layer{
public:
   CREATE_FUNC(Build_layer);
   virtual bool init();
   static Scene* createScene();
    void add_item(int num);
    void change_stage(int num,int money,std::string picname);
    void addtouch_event(int index,Fight_Layer::touchType ptype);
};
#endif /* defined(__Tiltest__Build_layer__) */
