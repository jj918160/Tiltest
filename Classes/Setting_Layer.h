//
//  Setting_Layer.h
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#ifndef __animate_homework__Setting_Layer__
#define __animate_homework__Setting_Layer__

#include <stdio.h>
#include "cocos2d.h"

class Setting_Layer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setting_Layer);
    
   
    
   
};

#endif /* defined(__animate_homework__Setting_Layer__) */
