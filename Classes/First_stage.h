//
//  First_stage.h
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//

#ifndef __Tiltest__First_stage__
#define __Tiltest__First_stage__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Fitst_stage : public Layer
{
public:

CREATE_FUNC(Fitst_stage);
static cocos2d::Scene* createScene();
virtual bool init();
    void callback1(Ref* psender);
    void loadmusic();
    void update(float dt);
    void back_game(Ref *sender);
//    void callback2(Ref* psender);
//    void callback3(Ref* psender);
  
};

#endif /* defined(__Tiltest__First_stage__) */
