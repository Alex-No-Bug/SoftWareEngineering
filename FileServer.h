/* 服务器端的文件信息 */
#pragma once
#include "ConfigDefine.h"
#include "Message.h"
#include <string>
#include <cstdlib>//必须包含
class FileServer
{
public:
    unsigned long fileSize;
    unsigned long transCount;
    unsigned long lastTimeSize;
    char fileOrGra;//种类标记
    std:: string fileName;
    std:: string path;
    std:: string sender;
    std:: string receiver;

    FileServer(Message fileCheckMsg)
    {
        sender=fileCheckMsg.sender;
        receiver=fileCheckMsg.receiver;
        int index=0;
        while(fileCheckMsg.message[index]!='|')
        {
            fileName=fileName+fileCheckMsg.message[index];
            index++;
        }
        //此时=|
        index++;
        std::string number="";
        while(fileCheckMsg.message[index]!='|')
        {
            number=number+fileCheckMsg.message[index];
            index++;
        }
         transCount=atol(number.c_str());
         //index=|
         index++;
         number="";
        while(fileCheckMsg.message[index]!='|')
        {
            number=number+fileCheckMsg.message[index];
            index++;
        }
          lastTimeSize =atol(number.c_str());
          //index==|
          index++;
          fileOrGra=fileCheckMsg.message[index];
    }
    //传入一个文件确认报文
    FileServer(int a){;}

    std:: string toString()
   { //生成如下格式的字符串
    //文件确认报文格式 (服务器->用户) F_C_M|sender|receiver|fileName|file_info
    //file_info格式 transCount|lastTimeSize|flagOrGra 
    //FILE_CHECK_MSGfileName|file_info
    std::string message="";
    message.push_back(FILE_CHECK_MSG);
    message=message+sender+receiver+fileName+to_string(fileSize)+"|"+std::to_string(lastTimeSize)+"|";
    message.push_back(fileOrGra);
   }s
};

class FileList 
{
public:
    unsigned int size;
    std:: vector<FileServer> fileCache;

    void push_cache(FileServer f)
    {
        fileCache.push_back(f);
        size++;
    }

    FileServer check(std::string userName)
    //默认的缺省路径是EMPTY
    //传入一个用户名
    //返回一个文件的信息即可
    //如果当前没有该用户的文件 则返回空类对象
    {
        FileServer tempF(1);
        tempF.path = "EMPTY";
        if (size == 0)
            return tempF;
        //如果消息缓存为空 直接返回一个空的FileServer
        //--------------------------------------------------------------

        for (int i = 0; i < size; i++)
        {
            if (fileCache.at(i).receiver == userName)
            {
                tempF = fileCache.at(i);
                //赋值传出去
                std::vector<FileServer>::iterator cur = fileCache.begin();
                fileCache.erase(cur + i);
                size--;
                //封装类中删除一条消息时大小也要同步更新
                break;
                //只找一个文件 找到就退出
            }
        }
        return tempF;
    }
    
    //向用户发送文件时 要先询问是否准备接收
    //若不愿意接收 则丢弃当前文件 如果有其他文件待发 则询问剩下的文件
    //直到没有当前用户的文件

};
