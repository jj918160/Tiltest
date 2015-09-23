//
//  Fight_Layer.cpp
//  Tiltest
//
//  Created by mac on 15-8-24.
//
//
#include "UI_Layer.h"
#include "Player.h"
#include "First_stage.h"
#include "Fight_Layer.h"
//#include "Moster.h"
#include "PathArithmetic.h"
#include "A_statPath.h"
//#include "Wall.h"
//#include "Tower.h"
#include "Csv_Parser.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Fight_Layer::touchType Fight_Layer::t_type=Fight_Layer::touchType::move;

Vec2 Fight_Layer::converToint(Vec2 Worldpoint){
    CCLOG("-----");
    TMXTiledMap*map=static_cast<TMXTiledMap*>(this->getChildByTag(1));
    TMXLayer *la=map->getLayer("layer1");
    Point t1=la->getPositionAt(Vec2(0,0))+Vec2(map->getTileSize().width*_mscale/2,map->getTileSize().height*_mscale);
    Point t=map->convertToWorldSpace(t1);
//    CCLOG("world:%f,%f",Worldpoint.x,Worldpoint.y);
//      CCLOG("0,0:%f,%f",t.x,t.y);
    Vec2 offset=Worldpoint-t;
//    CCLOG("off:%f,%f",offset.x,offset.y);
    Size sm=map->getTileSize();
  //  CCLOG("cale:%f",_mscale);
    Size s=sm*_mscale;
    
    int x=offset.x/s.width+offset.y/s.height;
    int y=offset.y/s.height-offset.x/s.width;
//    CCLOG("x:%d,y:%d",x,y);
  //  CCLOG("-----");
    return Vec2(-y,-x);
}

Vec2 Fight_Layer::converintTofloat(Vec2 intpoint){
    
    TMXTiledMap*map=static_cast<TMXTiledMap*>(this->getChildByTag(1));
    TMXLayer *la=map->getLayer("layer1");
    //获取GID的像素坐标
    Point t2=la->getPositionAt(Vec2(intpoint.x,intpoint.y-1));
 //   Point offset=Vec2(map->getTileSize().width/2*_mscale,map->getTileSize().height/2*_mscale);
   
    //转换成模型坐标
    Point t1=this->convertToNodeSpace(la->convertToWorldSpace(t2));
    //CCLOG("t1.x%f,t1.y%f",t1.x,t1.y);
    return  t1;
}

bool Fight_Layer::init(){
    if ( !Layer::init() )
    {
        return false;
    }
     SimpleAudioEngine::getInstance()->playBackgroundMusic("waite.mp3",true);
     game_over=false;
     game_win=false;
    totalhp=20;
    poutover=true;
    auto bg=Sprite::create("worldmap.png");
    bg->setAnchorPoint(Vec2(0.1,0.25));
    addChild(bg);
    
    Size winsize=Director::getInstance()->getVisibleSize();
    TMXTiledMap*map=TMXTiledMap::create("tmx_fight2.tmx");
    
    TMXLayer*layer=map->getLayer("layer1");
    tilesize=map->getTileSize();
    addChild(map,0,1);
    //加载数据
    onecolum=Csv_parser->read_csv_as_stringtoVector("stage_1.csv");
    ValueVector va=Csv_parser->read_vector(onecolum.at(1).asString());
    boshu=va.at(5).asInt();
    nowboshu=0;
    int bgx=va.at(1).asInt();
    int bgy=va.at(2).asInt();
    int edx=va.at(3).asInt();
    int edy=va.at(4).asInt();
    
    
    //初始化数据,添加精灵
    bornP=Vec2(bgx,bgy);
    destination=Vec2(edx,edy);
    auto mon_home=Sprite::create("76.0.png");
    Vec2 pb=converintTofloat(Vec2(bgx,bgy));
    //CCLOG("pp:x%f,pp:y%f",pp.x,pp.y);
    mon_home->setPosition(pb+Vec2(0,16));
    this->addChild(mon_home,bgx+bgy);
    
    
    auto mon_des=Sprite::create("towerbase.png");
    Vec2 pe=converintTofloat(Vec2(edx,edy));
    mon_des->setPosition(pe);
    auto d=Sprite::create("77.0.png");
    d->setPosition(mon_des->getContentSize().width/2,mon_des->getContentSize().height*2/3);
    mon_des->addChild(d);
    this->addChild(mon_des,edx+edy,99);
    //
    
    auto hpbk=Sprite::create("hp_back.png");
    hpbk->setPosition(96,128);
    mon_des->addChild(hpbk);
    
    auto hpft=Sprite::create("hp_now.png");
    hpft->setPosition(64,128);
    hpft->setAnchorPoint(Vec2(0,0.5));
    mon_des->addChild(hpft,0,1);

    //
    t_type=Fight_Layer::touchType::move;
    asptol=new A_starPath();

    this->setPosition(-map->getContentSize().width/4,-map->getContentSize().height/4);
    _mscale=1.f;
    
//初始化Gird数组
    Size mapsize=map->getMapSize();
    for (int i=0; i<mapsize.width; i++) {
        Vector<Gird*> temp;
        for (int j=0; j<mapsize.height; j++) {
            Gird*gd=Gird::create(i,j);
            temp.pushBack(gd);
        }
        _mapgid.push_back(temp);
    }

    
    
    //地图点击
    auto toucheve=EventListenerTouchOneByOne::create();
    toucheve->onTouchBegan=[&](Touch*ptouch,Event *pevent)
    {
        
        if (pevent->getCurrentTarget()->boundingBox().containsPoint(this->convertToNodeSpace(ptouch->getLocation())))
        {
           TMXTiledMap* temp=(TMXTiledMap*)this->getChildByTag(1);
            Size mapsize=temp->getMapSize();
            Point intpo=converToint(ptouch->getLocation());
          
            if (intpo.x>=0&&intpo.y>=0&&intpo.x<mapsize.width&&intpo.y<mapsize.height) {
                if (!_mapgid.at(intpo.x).at(intpo.y)->getPass()) {
                    return false;
                }
                if (t_type==Fight_Layer::touchType::create_wall) {
                    if (Player::getInstance()->money<10) {
                        UI_Layer*uil=(UI_Layer*)this->getParent()->getChildByTag(2);
                        uil->create_message("没有足够的金钱");
                        return false;
                    }
                    Player::getInstance()->money-=10;
                    createwall(intpo.x,intpo.y);
                    CCLOG("创建成功");
                    return true;
                }
                else if(t_type==Fight_Layer::touchType::create_tower&&intpo.x>=1&&intpo.y>=1&&intpo.x<mapsize.width-1&&intpo.y<mapsize.height-1){
                    if (Player::getInstance()->money<100) {
                        UI_Layer*uil=(UI_Layer*)this->getParent()->getChildByTag(2);
                        uil->create_message("没有足够的金钱");
                        return false;
                    }
                   
                    createtower(intpo.x,intpo.y);
                    return true;
                }
                else if(t_type==Fight_Layer::touchType::create_icetower&&intpo.x>=1&&intpo.y>=1&&intpo.x<mapsize.width-1&&intpo.y<mapsize.height-1){
                    if (Player::getInstance()->money<200) {
                        UI_Layer*uil=(UI_Layer*)this->getParent()->getChildByTag(2);
                        uil->create_message("没有足够的金钱");
                        return false;
                    }
                   
                    create_icetower(intpo.x,intpo.y);
                    return true;
                }
                else if(t_type==Fight_Layer::touchType::create_firetower&&intpo.x>=1&&intpo.y>=1&&intpo.x<mapsize.width-1&&intpo.y<mapsize.height-1){
                    if (Player::getInstance()->money<3000) {
                        UI_Layer*uil=(UI_Layer*)this->getParent()->getChildByTag(2);
                        uil->create_message("没有足够的金钱");
                        return false;
                    }
                    
                    create_firetower(intpo.x,intpo.y);
                    return true;
                }
            
            }
            else
            {
            t_type=Fight_Layer::touchType::move;
              CCLOG("不在地图上");
            return false;
            }
        }
        
        
        return false;
    };
    toucheve->onTouchMoved=[&](Touch*ptouch,Event *pevent)
    {
        
        if (pevent->getCurrentTarget()->boundingBox().containsPoint(this->convertToNodeSpace(ptouch->getLocation())))
        {
            TMXTiledMap* temp=(TMXTiledMap*)this->getChildByTag(1);
            Size mapsize=temp->getMapSize();
            Point intpo=converToint(ptouch->getLocation());
            
            if (intpo.x>=0&&intpo.y>=0&&intpo.x<mapsize.width&&intpo.y<mapsize.height) {
                if (!_mapgid.at(intpo.x).at(intpo.y)->getPass()) {
                    return;
                }
                if (t_type==Fight_Layer::touchType::create_wall) {
                    if (Player::getInstance()->money<10) {
                        UI_Layer*uil=(UI_Layer*)this->getParent()->getChildByTag(2);
                        uil->create_message("没有足够的金钱");
                        return ;
                    }
                    Player::getInstance()->money-=10;
                    createwall(intpo.x,intpo.y);
                    CCLOG("创建成功");
                    return;
                }
            }
        }
    
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(toucheve,layer);

  
   //地图缩放
    auto listener=EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan=[&](const std::vector<Touch*>&touches,Event *pevent)
    {
        Director*director=Director::getInstance();
        if (touches.size()>=2) {
            auto point1=director->convertToGL(touches.at(0)->getLocation());
            auto point2=director->convertToGL(touches.at(1)->getLocation());
            _distance=point1.getDistance(point2);
        }
    };
    listener->onTouchesMoved=[&](const std::vector<Touch*>&touches,Event *pevent)
    {
        CCLOG("scale%f",_mscale);
        CCLOG("_distance%f",_distance);
        Director*director=Director::getInstance();
        if (touches.size()>=2) {
            auto point1=director->convertToGL(touches.at(0)->getLocation());
            auto point2=director->convertToGL(touches.at(1)->getLocation());
            
            double new_distance=point1.getDistance(point2);
            float newscale=new_distance/_distance*_mscale;
            _distance=new_distance;
            if (newscale<2.f&&newscale>0.5f) {
                _mscale=newscale;
                this->setScale(_mscale);
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //地图移动
    auto lisone=EventListenerTouchOneByOne::create();
    lisone->onTouchBegan=[&](Touch*ptouch,Event *pevent)
    {
        if (t_type==Fight_Layer::touchType::move) {
            return true;
        }
        return false;
    };
    lisone->onTouchMoved=[&](Touch*ptouch,Event *pevent)
    {
      
        Vec2 point=this->getPosition()+ptouch->getDelta();
        
        CCLOG("px:%f,py:%f",point.x,point.y);
         Size vsize=Director::getInstance()->getVisibleSize();
        if (point.x<vsize.width/4&&point.y<vsize.height/4&&point.x>-vsize.width*0.75&&point.y>-vsize.height*0.75) {
              this->setPosition(point);
        }
        //this->setPosition(this->getPosition()+ptouch->getDelta());
       
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisone, this);
   
    scheduleUpdate();
      return true;
}
void Fight_Layer::createwall(int x,int y){
    Wall*wall=Wall::create();
    wall->wallchange(x, y, _mapgid);
   
    Vec2 pp=converintTofloat(Vec2(x,y));
    //CCLOG("pp:x%f,pp:y%f",pp.x,pp.y);
    wall->setPosition(pp);
    vecofw.pushBack(wall);

    this->addChild(wall,x+y);
    _mapgid.at(x).at(y)->setPass(false);
    
    for (auto i:vecofw) {
        if((i->x-x==1&&i->y-y==1)||(i->x-x==1&&i->y-y==0)||(i->x-x==0&&i->y-y==1)){
            //中间区域
            if (i->x>0&&i->y>0) {
                  i->changed(i->x, i->y, _mapgid);
            }
            //顶点直接
            
            //两边分情况考虑
        }
    }
    
    return;
}
void Fight_Layer::createtower(int x,int y)
{
    Tower*t=Tower::create();
    if (t->cancreate(x, y, _mapgid)) {
         Player::getInstance()->money-=100;
         Vec2 pp=converintTofloat(Vec2(x,y));
        t->setPosition(pp);
        this->addChild(t,x+y);
        t->x=x;
        t->y=y;
        vecoft.pushBack(t);
        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1;j++) {
                _mapgid.at(x+i).at(y+j)->setPass(false);
            }
        }

     }
    else {
        Label*lb=Label::createWithSystemFont("无法建造，请重新选择位置", "Arial",32);
        lb->setPosition(480,320);
        Node*pa=(Node*)this->getParent();
        pa->addChild(lb);
        lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
    }
}
void Fight_Layer::create_icetower(int x,int y)
{
    Tower*t=ice_Tower::create();

    if (t->cancreate(x, y, _mapgid)) {
         Player::getInstance()->money-=200;
        Vec2 pp=converintTofloat(Vec2(x,y));
        t->setPosition(pp);
        this->addChild(t,x+y);
        t->x=x;
        t->y=y;
        vecoft.pushBack(t);
        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1;j++) {
                _mapgid.at(x+i).at(y+j)->setPass(false);
            }
        }
        
    }
    else {
        Label*lb=Label::createWithSystemFont("无法建造，请重新选择位置", "Arial",32);
        lb->setPosition(480,320);
        Node*pa=(Node*)this->getParent();
        pa->addChild(lb);
        lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
    }
}


void Fight_Layer::create_firetower(int x,int y)
{
    Tower*t=Fire_Tower::create();
    if (t->cancreate(x, y, _mapgid)) {
        Player::getInstance()->money-=3000;
        Vec2 pp=converintTofloat(Vec2(x,y));
        t->setPosition(pp);
        this->addChild(t,x+y);
        t->x=x;
        t->y=y;
        vecoft.pushBack(t);
        for (int i=-1; i<=1; i++) {
            for (int j=-1; j<=1;j++) {
                _mapgid.at(x+i).at(y+j)->setPass(false);
            }
        }
        
    }
    else {
        Label*lb=Label::createWithSystemFont("无法建造，请重新选择位置", "Arial",32);
        lb->setPosition(480,320);
        Node*pa=(Node*)this->getParent();
        pa->addChild(lb);
        lb->runAction(Sequence::create(FadeOut::create(2),RemoveSelf::create(), NULL));
    }
}

//void Fight_Layer::callback2(Ref* psender){
//    t_type=Fight_Layer::touchType::create_wall;
//}
//void Fight_Layer::callback3(Ref* psender){
//     t_type=Fight_Layer::touchType::create_tower;
//}
void Fight_Layer::callback1(Ref* psender){
    if (!poutover) {
        CCLOG("请等待");
        return;
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic("fight.mp3",true);
    TMXTiledMap* map=(TMXTiledMap*)this->getChildByTag(1);
    Size mapsize=map->getMapSize();
    TMXLayer *pp=map->getLayer("layer1");
    Size tilesize=map->getTileSize();
    beginpoint=Vec2(pp->getPositionAt(bornP)+tilesize/2);
   
    path_vector=asptol->getPath(bornP,destination,_mapgid, mapsize,tilesize);
    //拆迁
    while (path_vector.size()<=1) {
        CCLOG("path_vector.size():%zd",path_vector.size());
        CCLOG("vecof:%zd,%zd",vecoft.size(),vecofw.size());
        Vec2 zhanai=asptol->nopath_try_find(bornP,destination,_mapgid, mapsize,tilesize);
         CCLOG("chaiqian2");
       //强制拆迁
        for (auto i:vecofw) {
            if (i->x==zhanai.x&&i->y==zhanai.y) {
                _mapgid.at(zhanai.x).at(zhanai.y)->setPass(true);
                vecofw.eraseObject(i);
                   SimpleAudioEngine::getInstance()->playEffect("caiqiang.wav");
                i->runAction(RemoveSelf::create());
            }
        }
        for (auto j:vecoft) {
            if (abs(j->x-zhanai.x<=1)&&abs(j->y-zhanai.y<=1)) {
                for (int o=-1; o<=1; o++) {
                    for (int p=-1; p<=1; p++) {
                        _mapgid.at(j->x+o).at(j->y+p)->setPass(true);
                    }
                }
                 SimpleAudioEngine::getInstance()->playEffect("caiqiang.wav");
                j->runAction(RemoveSelf::create());
                vecoft.eraseObject(j);
            }
        }
         path_vector=asptol->getPath(bornP,destination,_mapgid, mapsize,tilesize);
        
    }
  
    
   // path_vector=asptol->nopath_find_path(bornP, destination, _mapgid, mapsize, tilesize);
    //att_vector=asptol->getattacknode();
    
       // asptol->clear_att();
  //  CCLOG("pnt:size%zd",path_vector.size());
    nowboshu++;
    if (nowboshu<=boshu) {
          ValueVector va=Csv_parser->read_vector(onecolum.at(nowboshu+2).asString());
        float time=va.at(4).asFloat();
        int number=va.at(2).asInt();
        CCLOG("boshu:%d,time:%f,number:%d",nowboshu,time,number);
          schedule(schedule_selector(Fight_Layer::create_monster), time, number-1, 0.5);
          poutover=false;
        t_type=Fight_Layer::touchType::move;
        scheduleOnce(schedule_selector(Fight_Layer::putoutover), 1+(number-1)*time);
      }
}
void Fight_Layer::putoutover(float dt){
       SimpleAudioEngine::getInstance()->playBackgroundMusic("waite.mp3",true);
    poutover=true;
}
void Fight_Layer::create_monster(float dt){
 
    ValueVector va=Csv_parser->read_vector(onecolum.at(nowboshu+2).asString());
    auto sp=monster::create();
    sp->setScale(0.7,0.7);
    sp->setPosition(beginpoint);
    sp->speed=va.at(3).asFloat();
    sp->hp=va.at(5).asInt();
    sp->max_hp=sp->hp;
    sp->boshu=va.at(0).asInt();

    
    vecofmon.pushBack(sp);
    //下兵
     SimpleAudioEngine::getInstance()->playEffect("training_finished_03.m4r");
    
    this->addChild(sp,1);
   
   // CCLOG("speed:%f,hp:%d",sp->speed,sp->hp);
    //如果没有找到路

//    if (att_vector.size()>1) {
//        CCLOG("no");
//        Vector<FiniteTimeAction*>vai=sp->init_actioninterval_nopath(path_vector, att_vector, sp->speed);
//        vai.pushBack(RemoveSelf::create());
//        vai.pushBack(CallFuncN::create([=](Node* pSender){
//            monster*s=(monster*)pSender;
//            vecofmon.eraseObject(s);
//            // CCLOG("size:%zd",vecofmon.size());
//            
//        }));
//        sp->runAction(Sequence::create(vai));
//
//    }
//    else
//    {
    
    Vector<FiniteTimeAction*>vai=sp->init_actioninterval(path_vector,sp->speed);
    vai.pushBack(RemoveSelf::create());
    vai.pushBack(CallFuncN::create([=](Node* pSender){
        this->getChildByTag(99)->getChildByTag(1)->setScaleX(--totalhp/20.f);
        SimpleAudioEngine::getInstance()->playEffect("bottle_break_04_lightning_01.m4r");
        monster*s=(monster*)pSender;
        vecofmon.eraseObject(s);
       // CCLOG("size:%zd",vecofmon.size());
        if (totalhp<=0) {
            game_over=true;
        }
    }));
    ActionInterval *ac=Sequence::create(vai);
    Speed*spd=Speed::create(ac,1.0);
    spd->setTag(10);
    sp->runAction(spd);
   // sp->runAction(Sequence::create(vai));
    }
   
    
//}

void Fight_Layer::update(float dt)
{
    if (vecofmon.empty()||vecoft.empty()) {
        return;
    }
    for(auto a:vecoft){
        a->attack(vecofmon);
    }
    if (nowboshu>=boshu&&vecofmon.size()<=0&&poutover) {
        game_win=true;
    }
}

//void Fight_Layer::nopath(monster*mon){
//    if (path_vector.empty()) {
//        
//        Vec2 int_bein=converToint(this->convertToWorldSpace(mon->getPosition()));
//        PointNode*nowint=PointNode::create(int_bein.x,int_bein.y);
//        path_vector.pushBack(nowint);
//       
//        for (int i=int_bein.x; i>destination.x; i--) {
//            
//                    }
//        
//       
//       
//     
//        
//        
//        CCLOG("vector->size:%zd",path_vector.size());
//        }
//    for (auto mon:vecofmon){
//         Vector<FiniteTimeAction*>vai=mon->init_actioninterval(path_vector,mon->speed);
//         vai.pushBack(CallFuncN::create([=](Node* pSender){
//            monster*ms=static_cast<monster*>(pSender);
//           
//            ms->fight_animation();
//            
//        }));
//        
//        
//        
//          mon->runAction(Sequence::create(vai));
//    }
//}


