//
//  Begin_Layer.h
//  Tiltest
//
//  Created by mac on 15-8-30.
//
//

#ifndef __Tiltest__Begin_Layer__
#define __Tiltest__Begin_Layer__

#include <stdio.h>
#include "cocos2d.h"

class Begin_Layer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Begin_Layer);
    
    virtual void update(float dt);
    
 
};

#endif /* defined(__Tiltest__Begin_Layer__) */
