//
//  XML_DOMParser.cpp
//  SQLtest
//
//  Created by mac on 15-8-19.
//
//

#include "XML_DOMParser.h"
#include "cocostudio/CocoStudio.h"
using namespace tinyxml2;

void XML_DOMParser::write_xml(){
    
    std::string filepath=FileUtils::getInstance()->getWritablePath()+"testplist.xml";
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    if (pdoc==NULL) {
        return ;
    }
    XMLDeclaration*pDel=pdoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (pDel==NULL) {
        return ;
    }
    //
    pdoc->LinkEndChild(pDel);
    
    
    XMLElement*plistElement=pdoc->NewElement("plist");
    plistElement->SetAttribute("version", "1.0");
    pdoc->LinkEndChild(plistElement);
    
    
    
    XMLElement* pDict=pdoc->NewElement("hero");
    
    plistElement->LinkEndChild(pDict);
    
    XMLElement*keyelement=pdoc->NewElement("姓名");
    keyelement->LinkEndChild(pdoc->NewText("船长"));
    pDict->LinkEndChild(keyelement);
    
    XMLElement*stringElement=pdoc->NewElement("属性");
    pDict->LinkEndChild(stringElement);
    
    XMLElement*hpelement=pdoc->NewElement("血量");
    hpelement->LinkEndChild(pdoc->NewText("100"));
    stringElement->LinkEndChild(hpelement);
    
    XMLElement*mpelement=pdoc->NewElement("蓝量");
    mpelement->LinkEndChild(pdoc->NewText("50"));
    stringElement->LinkEndChild(mpelement);
    
    XMLElement*atkelement=pdoc->NewElement("物理攻击");
    atkelement->LinkEndChild(pdoc->NewText("30"));
    stringElement->LinkEndChild(atkelement);
    
    XMLElement*skillelement=pdoc->NewElement("技能");
    //atkelement->LinkEndChild(pdoc->NewText("30"));
    stringElement->LinkEndChild(skillelement);
    
    XMLElement*s1element=pdoc->NewElement("寒冰箭");
    s1element->LinkEndChild(pdoc->NewText("atk"));
    s1element->LinkEndChild(pdoc->NewText("20"));
    skillelement->LinkEndChild(s1element);
    
    XMLElement*s2element=pdoc->NewElement("箭雨");
    s2element->LinkEndChild(pdoc->NewText("atk"));
    s2element->LinkEndChild(pdoc->NewText("30"));
    skillelement->LinkEndChild(s2element);
    
    XMLElement*s3element=pdoc->NewElement("光环");
    s3element->LinkEndChild(pdoc->NewText("atk+20"));
    skillelement->LinkEndChild(s3element);
    
    XMLElement*s4element=pdoc->NewElement("沉默");
    s4element->LinkEndChild(pdoc->NewText("magatk"));
    s4element->LinkEndChild(pdoc->NewText("+20"));
    skillelement->LinkEndChild(s4element);
    
    XMLElement*keyelement2=pdoc->NewElement("姓名");
    keyelement2->LinkEndChild(pdoc->NewText("小黑"));
    pDict->LinkEndChild(keyelement2);
    
    XMLElement*stringElement2=pdoc->NewElement("属性");
    // stringElement2->LinkEndChild(pdoc->NewText("90"));
    pDict->LinkEndChild(stringElement2);
    
    pdoc->SaveFile(filepath.c_str());
    CCLOG("%s",filepath.c_str());
    pdoc->Print();
    delete pdoc;
    
}

void XML_DOMParser::read_xml(){
    //和写入一样，获取文件路径
    std::string filepath=FileUtils::getInstance()->getWritablePath()+"testplist.xml";
    //新建一个xml文件类
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    //载入文件，此时该对象值已赋完毕
    pdoc->LoadFile(filepath.c_str());
    //获取根节点
    XMLElement*rootEle=pdoc->RootElement();
    //获取根节点的第一个xml属性
    const XMLAttribute*attribute=rootEle->FirstAttribute();
    CCLOG("name=%s,value=%s",attribute->Name(),attribute->Value());
    //获取version属性的值，该属性是个float类型
    float value=0.1;
    rootEle->QueryFloatAttribute("version",&value);
    //设置version的属性值
    rootEle->SetAttribute("version",1.4);
    //获取根节点的第一个子节点dict
    XMLElement*dictEle=rootEle->FirstChildElement();
    //获取dict的第一个子节点key
    XMLElement*keyEle=dictEle->FirstChildElement();
    CCLOG("%s,%s",keyEle->Name(),keyEle->GetText());
    //获取key的下一个兄弟节点str
    XMLElement*strEle=keyEle->NextSiblingElement();
    CCLOG("%s,%s",strEle->Name(),strEle->GetText());
    //获取str的子结点nul，如果为空，就返回
    XMLElement*nulxmlEle=strEle->FirstChildElement();
    if (NULL==nulxmlEle) {
        CCLOG("no");
    }else{
        CCLOG("%s,%s",nulxmlEle->Name(),nulxmlEle->GetText());
    }
    //获取nul的所有兄弟节点
    while (nulxmlEle->NextSiblingElement()) {
        XMLElement*nulEle=nulxmlEle->NextSiblingElement();
        CCLOG("%s,%s",nulEle->Name(),nulEle->GetText());
        nulxmlEle=nulEle;
    }
    //储存
    pdoc->SaveFile(filepath.c_str());
}

void XML_DOMParser::find_base(tinyxml2::XMLElement*rootele,const char*string){
    XMLElement*temp=rootele->FirstChildElement();
    while (temp!=NULL)
    {   //如果相等，遍历（输出）该树
        if (*(temp->Name())==*string) {
            read_base(temp);
        }
        //查找以temp为根的树
        find_base(temp, string);
        //查找兄弟树
        temp=temp->NextSiblingElement();
    }
}
//文件根路径，和查找的对象string
void XML_DOMParser::find_xmlitoos(const char*filepath,const char*string){
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    pdoc->LoadFile(filepath);
    XMLElement*rootEle=pdoc->RootElement();
    const XMLAttribute*attribute=rootEle->FirstAttribute();
    find_base(rootEle,string);
}



void XML_DOMParser::read_base(tinyxml2::XMLElement*rootele)
{   //获取根节点的第一个子节点temp
    XMLElement*temp=rootele->FirstChildElement();
    //如果存在，执行遍历
    while (temp!=NULL)
    {
        CCLOG("%s,%s",temp->Name(),temp->GetText());
        //访问以temp为根节点的树
        read_base(temp);
        //访问temp的所有兄弟节点
        temp=temp->NextSiblingElement();
    }
}
//通过文件路径遍历文件
void XML_DOMParser::read_xmlitoos(const char*filepath){
    //新建文件类
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    //载入目标文件
    pdoc->LoadFile(filepath);
    //获取根节点
    XMLElement*rootEle=pdoc->RootElement();
    //const XMLAttribute*attribute=rootEle->FirstAttribute();
    //CCLOG("name=%s,value=%s",attribute->Name(),attribute->Value());
    //访问该节点
    read_base(rootEle);
}

cocos2d::ValueMap XML_DOMParser::read_xmlitoos_to_map(const char*filepath)
{
    ValueMap pmap;
    //新建文件类
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    //载入目标文件
    pdoc->LoadFile(filepath);
    //获取根节点
    XMLElement*rootEle=pdoc->RootElement();
    //const XMLAttribute*attribute=rootEle->FirstAttribute();
    //CCLOG("name=%s,value=%s",attribute->Name(),attribute->Value());
    //访问该节点
    if (rootEle->GetText()!=nullptr) {
        pmap[rootEle->Name()]=Value(rootEle->GetText());
    }
    else{
    pmap=read_base_to_map(rootEle);
    }
   // CCLOG("%s",pmap.begin()->first.c_str());
    return pmap;
}

cocos2d::ValueMap XML_DOMParser::read_base_to_map(tinyxml2::XMLElement*rootele)
{
    ValueMap pmap;
    //获取根节点的第一个子节点temp
    XMLElement*temp=rootele->FirstChildElement();
    //如果存在，执行遍历
    while (temp!=NULL)
    {
        if (temp->GetText()!=nullptr) {
            pmap[temp->Name()]=Value(temp->GetText());
          
        }
        else{
        ValueMap child_map;
        //访问以temp为根节点的树
        child_map=read_base_to_map(temp);
        //插入进去
        pmap[temp->Name()]=Value(child_map);
        }

        //访问temp的所有兄弟节点
        temp=temp->NextSiblingElement();
    }
    return pmap;
}




void XML_DOMParser::write_base(const char*filepath,ValueMap pmap)
{
    tinyxml2::XMLDocument*pdoc=new tinyxml2::XMLDocument();
    if (pdoc==NULL) {
        return ;
    }
    XMLDeclaration*pDel=pdoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    if (pDel==NULL) {
        return ;
    }
    pdoc->LinkEndChild(pDel);
    XMLElement*plistElement=pdoc->NewElement("plist");
    plistElement->SetAttribute("version", "1.0");
    pdoc->LinkEndChild(plistElement);
    for (auto i:pmap){
    XMLNode* pDict=pdoc->NewElement(i.first.c_str());
        write_base(i.second,pDict,pdoc);
    plistElement->LinkEndChild(pDict);
    }
    pdoc->SaveFile(filepath);
    delete pdoc;
    
}

void XML_DOMParser::write_base(Value vp,XMLNode*pa,tinyxml2::XMLDocument*pdoc)
{
    if (vp.getType()==Value::Type::MAP) {
        ValueMap pmap=vp.asValueMap();
        for (auto i:pmap) {
            XMLElement* pDict=pdoc->NewElement(i.first.c_str());
            write_base(i.second,pDict,pdoc);
                pa->LinkEndChild(pDict);
        }
    }
    else if(vp.getType()==Value::Type::STRING)
    {
        pa->LinkEndChild(pdoc->NewText(vp.asString().c_str()));
    }
}
