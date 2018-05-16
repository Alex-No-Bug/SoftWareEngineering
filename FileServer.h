/* �������˵��ļ���Ϣ */
#pragma once
#include "ConfigDefine.h"
#include "Message.h"
#include <string>
#include <cstdlib>//�������
class FileServer
{
public:
    unsigned long fileSize;
    unsigned long transCount;
    unsigned long lastTimeSize;
    char fileOrGra;//������
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
        //��ʱ=|
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
    //����һ���ļ�ȷ�ϱ���
    FileServer(int a){;}

    std:: string toString()
   { //�������¸�ʽ���ַ���
    //�ļ�ȷ�ϱ��ĸ�ʽ (������->�û�) F_C_M|sender|receiver|fileName|file_info
    //file_info��ʽ transCount|lastTimeSize|flagOrGra 
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
    //Ĭ�ϵ�ȱʡ·����EMPTY
    //����һ���û���
    //����һ���ļ�����Ϣ����
    //�����ǰû�и��û����ļ� �򷵻ؿ������
    {
        FileServer tempF(1);
        tempF.path = "EMPTY";
        if (size == 0)
            return tempF;
        //�����Ϣ����Ϊ�� ֱ�ӷ���һ���յ�FileServer
        //--------------------------------------------------------------

        for (int i = 0; i < size; i++)
        {
            if (fileCache.at(i).receiver == userName)
            {
                tempF = fileCache.at(i);
                //��ֵ����ȥ
                std::vector<FileServer>::iterator cur = fileCache.begin();
                fileCache.erase(cur + i);
                size--;
                //��װ����ɾ��һ����Ϣʱ��СҲҪͬ������
                break;
                //ֻ��һ���ļ� �ҵ����˳�
            }
        }
        return tempF;
    }
    
    //���û������ļ�ʱ Ҫ��ѯ���Ƿ�׼������
    //����Ը����� ������ǰ�ļ� ����������ļ����� ��ѯ��ʣ�µ��ļ�
    //ֱ��û�е�ǰ�û����ļ�

};
