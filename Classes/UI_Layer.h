//
//  UI_Layer.h
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//

#ifndef __Tiltest__UI_Layer__
#define __Tiltest__UI_Layer__

#include <stdio.h>
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;
class Animation_itools;
class UI_Layer : public Layer
{
public:
    Animation_itools *atools;
    CREATE_FUNC(UI_Layer);
    virtual bool init();
    void init_control();
    void update_gold(float dt);
    void update(float dt);
    Sprite*flag;
    bool canbuild;
    void create_message();
    void create_message(const std::string);
    void loading_animation();
};

#endif /* defined(__Tiltest__UI_Layer__) */
