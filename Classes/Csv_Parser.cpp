//
//  Csv_Parser.cpp
//  SQLtest
//
//  Created by mac on 15-8-20.
//
//
#include "cocos2d.h"
#include "Csv_Parser.h"
USING_NS_CC;

//将csv拆成一个二维数组
ValueVector Csv_Parser::read_csv_to_map(const char*filepath){
    FileUtils*fileitools=FileUtils::getInstance();
    std::string str=fileitools->getStringFromFile(filepath);
    std::string s;
    ValueVector sv;
    auto it=str.begin();
    for (;it!=str.end();it++) {
        if ((*it)!='\n') {
            s+=(*it);
        }
        else{
            ValueVector chvv;
            chvv=read_vector(s);
            sv.push_back(Value(chvv));
            s.clear();
        }
    }
    ValueVector chvv;
    chvv=read_vector(s);
    sv.push_back(Value(chvv));
       return sv;
}


cocos2d::ValueVector Csv_Parser::read_vector(std::string vc)
{
    std::string s;
    ValueVector sv;
    auto it=vc.begin();
    for (;it!=vc.end();it++) {
        if ((*it)!=','&&(*it)!='\n') {
            s+=(*it);
        }
        else{
            sv.push_back(Value(s));
            s.clear();
        }
    }
    sv.push_back(Value(s));
    return sv;
}

//将csv以行为单位拆成一个_array,每个元素是一行的那个string
__Array* Csv_Parser::read_csv_as_stringtoarray(const char*filepath)
{
    std::string str=FileUtils::getInstance()->getStringFromFile(filepath); //通过文件全路径创建字符集
    __String *contentstr=__String::create(str);//创建cocos2d的string
    __Array *rows=contentstr->componentsSeparatedByString("\n");   //根据“\n”分隔字符集
    return rows;
    
}
//将csv以行为单位拆成一个ValueVector,每个元素是一行的那个string
cocos2d::ValueVector Csv_Parser::read_csv_as_stringtoVector(const char*filepath)
{
    FileUtils*fileitools=FileUtils::getInstance();
    std::string str=fileitools->getStringFromFile(filepath);
    std::string s;
    ValueVector sv;
    auto it=str.begin();
    for (;it!=str.end();it++) {
        if ((*it)!='\n') {
            s+=(*it);
        }
        else{
            sv.push_back(Value(s));
            s.clear();
        }
    }
    //最后没有／n，需要再推入一次
    sv.push_back(Value(s));
    return sv;

}


//获取行列数
const Size Csv_Parser::getfileRowColNum(const char*filepath)
{
    ValueVector temp=read_csv_to_map(filepath);
    int row=temp.size();
    int col=temp.front().asValueVector().size();
    return Size(row,col);
}
//查找某行某列
const std::string Csv_Parser::getString(const char*filepath,int row,int iCol)
{
    ValueVector temp=read_csv_to_map(filepath);
    std::string str=temp.at(row).asValueVector().at(iCol).asString();
    return str;
}

//通过容器获取行列数
const Size Csv_Parser::getfileRowColNum(cocos2d::ValueVector &temp)
{
    int row=temp.size();
    int col=temp.front().asValueVector().size();
    return Size(row,col);
}
//通过容器查找某行某列，返回string
const std::string Csv_Parser::getString(cocos2d::ValueVector &temp,int row,int iCol)
{
    std::string str=temp.at(row).asValueVector().at(iCol).asString();
    return str;
}
//通过容器查找某行某列，返回Value
Value Csv_Parser::getValue(cocos2d::ValueVector &temp,int row,int iCol)
{
    Value value_t=temp.at(row).asValueVector().at(iCol);
    return value_t;
}
//获取某一行，返回value
Value Csv_Parser::get_line_Value(ValueVector &temp,int line)
{
    Value value_t=temp.at(line);
    return value_t;
    
}


