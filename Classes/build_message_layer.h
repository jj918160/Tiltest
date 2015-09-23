//
//  build_message_layer.h
//  Tiltest
//
//  Created by mac on 15-8-28.
//
//

#ifndef __Tiltest__build_message_layer__
#define __Tiltest__build_message_layer__

#include <stdio.h>
#include "Wall.h"
#include "Tower.h"
#include "Moster.h"
#include "cocos2d.h"

USING_NS_CC;

class build_message_layer : public Layer
{
public:
    static build_message_layer*create(Tower*);
    virtual bool init(Tower*);
    
    static build_message_layer*create(Wall*);
    virtual bool init(Wall*);
    
    static build_message_layer*create(monster*);
    virtual bool init(monster*);
    
    void load_tower(Tower*);
    void load_wall(Wall*);
    
};

#endif /* defined(__Tiltest__build_message_layer__) */
