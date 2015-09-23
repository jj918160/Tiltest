//
//  Player.cpp
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#include "Player.h"

using namespace std;
Player* Player::_cacheInstance=nullptr;


Player* Player::getInstance(){
    if (!_cacheInstance) {
        _cacheInstance=new Player();
       
    }
    
    return _cacheInstance;
}

bool Player::init(){
    money=1000;
    emage=1000;
    zhuanshi=3000;
 
    return true;
}


Player::Player(){
    init();
}
Player::~Player(){
    
}