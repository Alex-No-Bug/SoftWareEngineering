// File to read and write.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"
using namespace std;
#include <string>
#include <fstream>

//��Ϣ
class Message
{
  public:
    // 0|12|12|12121|i love you

    Message(string s)
    {
        for (int i = 0; i < 30; i++)
            launchTime[i] = 0;
        int i = 0;
        flag = s[i++];
        //1
        i++;
        string temp = "";
        while (s[i] != '|')
        {
            temp += s[i];
            i++;
        }
        sender = atoi(temp.c_str());

        //2.
        i++;
        temp = "";
        while (s[i] != '|')
        {
            temp += s[i];
            i++;
        }
        receiver = atoi(temp.c_str());
        //3.
        i++;
        temp = "";
        while (s[i] != '|')
        {
            temp = temp + s[i];
            i++;
        }

        int k = 0;
        while (temp[k] != 0)
        {
            launchTime[k] = temp[k];
            k++;
        }

        //4.
        i++;
        message = "";
        while (s[i] != '\0')
        {
            message += s[i++];
        }
    }

    char flag;
    int sender;
    int receiver;
    char launchTime[30];
    string message;
};

void writeFile(string file, Message m)
{

    string Flag = "";
    Flag.push_back(m.flag);
    string Sender = to_string(m.sender);
    string Receiver = to_string(m.receiver);
    string Time = m.launchTime;
    Time = Time + "\n";
    string text = m.message + "\n";

    //����ofstream��Ĺ��캯������һ���ļ���������������ļ�
    fstream f("E:\\a.txt", ios::app);

    if (!f)
    {
        cout << "�ļ����ܴ�" << endl;
    }
    else
    {
        string Massage_a[5];
        Massage_a[0] = Flag;
        Massage_a[1] = Sender;
        Massage_a[2] = Receiver;
        Massage_a[3] = Time;
        Massage_a[4] = text;
        for (int i = 0; i < 5; i++)
        {
            if (i == 4)
                f << Massage_a[i];
            // ����������ļ�
            else
                f << Massage_a[i] << "    "; //վ���ڴ����̨�ĽǶ�
        }
        f.close();

     
		// fstream f2("E:\\a.txt");
        // //    f2.seekg(7, ios::cur);//���ļ��Ķ�ָ��ӵ�ǰλ�������1234���ֽ�
        // //����ifstream��Ĺ��캯������һ���ļ�����������
        // if (!f2)
        // {
        //     cout << "�ļ����ܴ�" << endl;
        // }
        // else
        // {
		// 	char buffer[256];
		// 	ifstream in("E://a.txt");
		// 	if (!in.is_open())
		// 	{
		// 		cout << "Error opening file"; exit(1);
		// 	}
		// 	while (!in.eof())
		// 	{
		// 		in.getline(buffer, 100);
		// 		cout << buffer << endl;
		// 	}
        // //����
        //   // f2.seekp(10); // move 10 bytes ahead from beginning
        //    //cout << "new position: " << f2.tellp();
        //     char buffer[800];
        //     f2.getline(buffer, 799, 0); //char ������
          
        //     // // �Ӵ����ļ�����
        //     cout << endl
        //          << "start:" << endl;
        //     f2 >> buffer;
		// 	buffer[199] = '\0';
		// 	cout <<"buffer[0]"<< buffer[0] << endl;
        //     cout << buffer << endl;
        //     cout << "over" << endl;
        //     // �ر��ļ�������
        //     f2.close();
        }
    }

    //ofstream file1;
    // if (!file1)
    // {
    // 	cout << "�ļ����ܴ�" << endl;
    // }
    // else
    // {
    // 	//open����ֻ���ļ���һ�������������Զ�/д��ͨ�ļ���
    // 	file1.open("d:\\mytest.txt");
    // 	//�൱��file1.open("d:\\mytest.txt",ios::out|ios::in,0);

    // 	//�ı��ļ���д:�ò�����(<<)���ļ����.
    // 	file1 << "д���ļ�����!" << endl;
    // 	file1.close();
    // }

    // ifstream file2("d:\\mytest.txt");
    // if (!file2)
    // {
    // 	cout << "�ļ����ܴ�" << endl;
    // }
    // else
    // {
    // 	char ch1[100];
    // 	//�ı��ļ��Ķ�:����ȡ��(>>)���ļ�����.
    // 	file2 >> ch1;

    // 	cout << ch1 << endl;
    // 	file2.close();
    // }
    //fclose(fp);


int main()
{
    Message m1("0|111|222|2018.5.8.12::23|520");
	Message m2("0|111|222|2018.5.8.12::23|520");

    string file = "E://a.txt";
    writeFile(file, m1);
	writeFile(file, m2);
    system("pause");
    return 0;
}
