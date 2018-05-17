
class FriList
{
public:
	std::string name = "";
	int onlineStatu = OFFLINE;

	char haveMsg = NO;                //是否有消息标识
	std::vector<std::string> msgList; //消息列表
	int msgSize = 0;

	std::vector<std::string> graphList; //图片列表
	int graphSize = 0;

	FriList()
	{
		// msgList.clear();
		// graphList.clear();
	}
	FriList(std::string Name)
	{
		name = Name;
	}
};
//一个好友的消息定义
//-------------------------------------------------------

class FriUnit
{
public:
	int size = 0;
	std::vector<FriList> friunit;

	// FriUnit()
	//{
	//  friunit.clear();
	//onlineStatu.clear();
	//}
	//改变好友状态的函数
	void change_on(std::string f_name);
	void change_off();
	void init(std::string msg);

	//用字符串初始化好友名单
	//字符串格式 首尾均有分隔符
	// |XXXX|YYYYY|ZZZZZ|.....|
	// |好友1| 好友2 |好友3|...|  用|分隔
	//设置默认在线状态为OFFLINE
	//size要++ onlineStatu也要push_back()

	void setOnlineStatu(std::string msg);
	//传入当前好友在线名单字符串
	//把在该字符串中的好友设置为ONLINE 不在的设置为OFFLINE
	//字符串格式同上 首尾均有分隔符

	void recvMsg(std::string msg);
	//传入一次问询结果的字符串
	//根据字符串内容来修改好友列表各个单元的值
	//字符串格式为
	// *发送者1*发送者1的消息*发送者2*发送者2的消息*
	// *为分隔符 且首尾都有*
	//若当前有A发来的消息 则在好友列表中找到A那个元素
	//haveMsg赋值为YES 把当前的消息push

	std::string getMsg(std::string sender);
	//得到当某个用户发过来的消息
	//当graphSize为0时 重置消息标志位
	//从后往前查
	//输出格式为 消息1||消息2....||

	std::string getGraph(std::string sender);
	//得到某个用户发过来的图片路径
	//如果为空 则返回'*'
	//如果为空且msgSize为0时 重置消息标志位
	//
};

void FriUnit::recvMsg(std::string msg)
{
	for (int i = 0; i < msg.size(); i++)
	{
		std::string user_name = "";
		//如果遇到'*'跳过
		if (msg[i] == '*' && i != (msg.size() - 1))
			i++;
		//
		while (msg[i] != '*')
		{
			user_name = user_name + msg[i];
			i++;
		}
		i++;
		cout << user_name << endl;
		//此时i=*
		std::string message = "";

		while (msg[i] != '*')
		{
		  message.push_back(msg[i]);
			i++;
		}
		cout << "分割出来的messsge："<<message << endl;
		//好友信息的vector找到这个人
		for (int index = 0; index < friunit.size(); index++)
		{
			if (user_name.compare(friunit[index].name) == 0)
			{
				cout << "找到此人:" <<message<< endl;
				friunit[index].msgList.push_back(message); //消息压栈
				cout<< "压入的消息为"<<friunit[index].msgList[0];
				friunit[index].haveMsg = YES;
				friunit[index].msgSize++;
			}
		}
	}
	cout << "recv成功" << endl;
}
std::string FriUnit::getMsg(std::string sender)
{
	std::string m = "";
	for (int index = 0; index < friunit.size(); index++)
	{ //在好友列表中找到此人
		if (sender.compare(friunit[index].name) == 0)
		{
			cout << "index" << index << endl;
			cout << "找到匹配的好友" << friunit[index].name << endl;
			cout << "消息个数" << friunit[index].msgList.size() << endl;
			cout << friunit[index].msgList[0] << endl;

			//消息逆序输出
			for (int i = friunit[index].msgList.size() - 1; i >= 0; i--)
				m = m + friunit[index].msgList[i] + "||";
			cout << "m" << m << endl;
			if (friunit[index].graphSize == 0)
			{
				friunit[index].haveMsg = YES;
			}
			return (m);
		}
	}
}

void FriUnit::init(std::string msg)
{
	//用字符串初始化好友名单
	//字符串格式 首尾均有分隔符
	// |XXXX|YYYYY|ZZZZZ|.....|
	// |好友1| 好友2 |好友3|...|  用|分隔
	//设置默认在线状态为OFFLINE
	//size要++ onlineStatu也要push_back()

	for (int index = 1; msg[index] != '\0'; index++)
	{
		if (msg[index] == '|' && msg[index + 1] != '\0')
			index++;
		std::string f_name = "";
		while (msg[index] != '|')
		{
			f_name = f_name + msg[index];
			index++;
		}
		FriList fr(f_name);
		fr.onlineStatu = OFFLINE;
		friunit.push_back(fr);
		size++;

		if (msg[index+1] != '\0')
			index++;
	}
	cout << "初始化成功" << endl;
}
void FriUnit::change_on(std::string f_name)
{
	for (int i = 0; i < friunit.size(); i++)
	{
		if (f_name.compare(friunit[i].name) == 0)
		{
			friunit[i].onlineStatu = ONLINE;
		}
	}
}
void FriUnit::change_off()
{
	for (int i = 0; i < friunit.size(); i++)
	{
		if (friunit[i].onlineStatu != ONLINE)
			friunit[i].onlineStatu = OFFLINE;
	}
}
void FriUnit::setOnlineStatu(std::string msg)
{ //传入当前好友在线名单字符串
  //把在该字符串中的好友设置为ONLINE 不在的设置为OFFLINE
  //字符串格式同上 首尾均有分隔符
  // |MM|LL|LL|LL|
	for (int index = 1; msg[index] != '\0'; index++)
	{
		if (msg[index] == '|' && msg[index + 1] != '\0')
			index++;
		std::string f_name = "";
		while (msg[index] != '|')
		{
			f_name = f_name + msg[index];
			index++;
		}
		change_on(f_name);
		if (msg[index] != '\0')
			index++;
	}
	change_off();
}