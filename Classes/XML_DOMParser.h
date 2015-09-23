//
//  XML_DOMParser.h
//  SQLtest
//
//  Created by mac on 15-8-19.
//
//

#ifndef __SQLtest__XML_DOMParser__
#define __SQLtest__XML_DOMParser__

#include <stdio.h>
#include "tinyxml2/tinyxml2.h"
class XML_DOMParser{
public:
    //写入temp
    void write_xml();
    //读取temp
    void read_xml();
    //工具函数。
    
    void read_xmlitoos(const char*filepath);
    
    void read_base(tinyxml2::XMLElement*rootele);
    
    void find_base(tinyxml2::XMLElement*rootele,const char*string);
    
    void find_xmlitoos(const char*filepath,const char*string);
    
    void write_base(const char*filepath,cocos2d::ValueMap pmap);
    
    void write_base(cocos2d::Value vp,tinyxml2::XMLNode*pa,tinyxml2::XMLDocument*pdoc);
    
    cocos2d::ValueMap read_xmlitoos_to_map(const char*filepath);
    
    cocos2d::ValueMap read_base_to_map(tinyxml2::XMLElement*rootele);

    
    
};
#endif /* defined(__SQLtest__XML_DOMParser__) */
