//
//  Csv_Parser.h
//  SQLtest
//
//  Created by mac on 15-8-20.
//
//

#ifndef __SQLtest__Csv_Parser__
#define __SQLtest__Csv_Parser__

#include <stdio.h>
class Csv_Parser{
public:
    //读取一个文件，拆分行，每一行为一个元素,每个vector的元素是个vector
    cocos2d::ValueVector read_csv_to_map(const char*filepath);
    
    //读取一个文件，拆分行，每一行为一个元素,每个vector的元素是个string,返回一个__Array;
    cocos2d::__Array* read_csv_as_stringtoarray(const char*filepath);
    
    //读取一个文件，拆分行，每一行为一个元素,每个vector的元素是个string,返回一个ValueVector;
    cocos2d::ValueVector read_csv_as_stringtoVector(const char*filepath);
    
    //拆分一个字符串，
    cocos2d::ValueVector read_vector(std::string vc);
    //获取行列数，带解析
    const cocos2d::Size getfileRowColNum(const char*filepath);
   //查找某行某列，带解析
    const std::string getString(const char*filepath,int row,int iCol);
    //通过容器获取行列数
    const cocos2d::Size getfileRowColNum(cocos2d::ValueVector &temp);
    //通过容器查找某行某列,返回字符串
    const std::string getString(cocos2d::ValueVector &temp,int row,int iCol);
    //通过容器查找某行某列,返回Value
    cocos2d::Value getValue(cocos2d::ValueVector &temp,int row,int iCol);
    //获取某一行，返回value
    cocos2d::Value get_line_Value(cocos2d::ValueVector &temp,int line);
   
};
#endif /* defined(__SQLtest__Csv_Parser__) */
