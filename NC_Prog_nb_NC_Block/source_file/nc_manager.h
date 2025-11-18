#pragma once
#include <queue>
using std::queue;
#include "cstdlib"
#include <vector>
using std::vector;

#ifdef NC_Prog_nb_NC_Block_EXPORTS
#define NC_Prog_nb_NC_Block_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_API __declspec(dllimport)
#endif




//变量实体类
/*
	定义一种变量，同时具有两种性质——编号数值和编号类型；
	为了同时分配at变量和#变量，故在此将其统一；
	可增加不同的编号类型，以适应不同数据结构的机床
*/
class nc_var
{
private:
	//0代表@变量，1代表#变量
	int m_type;
	//变量号
	int m_num;

public:
	//构造函数
	nc_var();
	//a:大小(>0);b:类型(0;at 1:#)
	nc_var(int num, int type);
	//返回类成员的性质：0代表at变量，1代表#变量,默认at变量
	int type();
	//返回类成员的大小，默认
	int size();
	//设置类成员的性质：a:编号 b:0 at;1 #
	void set(int num, int type);
};

/*
定义一个先进先出的,能存取变量的指针的数据结构；
定义出该类则可将其装入其它顺序容器达成嵌套使用
*/
class nc_var_queue
{
private:
	//变量指针的存储队列
	queue<nc_var*> que;

public:
	//构造函数
	nc_var_queue();
	~nc_var_queue();

	//基础功能函数
public:
	//队列中元素个数
	int size();
	//初始化Nc_var对象队列
	void clear();
	//队首元素出列
	void pop();
	//元素加入队尾
	void push(nc_var* A);
	//查询队首元素
	nc_var* front();
	//查询队尾元素
	nc_var* back();
	//空判定，true空 false非空
	bool empty();
};

//编号分配类
/*给定闭区间和类型，执行成员函数allot(int& num, int& type)一次，
* 得到一个在闭区间内随机/不随机的不重复变量的编号和类型
*/
class NC_Prog_nb_NC_Block_API nc_manager
{
private:
	//未使用变量的列队
	nc_var_queue usable_var;
	//已使用变量的情况，第一个为主程序使用的，后面为子程序使用的
	vector<nc_var_queue*> used_var;
	//当前使用的程序index，主程序为0
	unsigned int pro_now_index;

	//基础函数
private:
	//设置变量空间
	//输入1:闭区间下限 2;闭区间上限 3:变量类型;0 at,1 #
	void add_qujian(int lower, int upper, int type);
	//输入的区间数据，生成初始化的队列
	void var_qujian();
	//将初始化队列打乱，随机排列
	void random_qujian();
	//释放当前子程序变量
	void var_release();

public:
	//构造函数，初始化可用编号队列
	nc_manager();

	//析构函数
	~nc_manager();

	//重置管理器
	void reset();

	//申请变量 0是@，1是#
	void apply_var_num(int& type, int& num);

	//子程序开始信号
	void prog_start();

	//子程序结束信号
	void prog_end();
};

/*
	变量管理器
	1、一种机床有一个变量管理器
	2、每一级程序都有一个自己的变量管理器
	3、主程序直接项机床的变量管理器第一个申请内存
	4、子程序根据其调用顺序依次申请内存
	5、程序由其变量管理器向机床的变量管理器申请内存，并且存放在子程序各自的变量管理器中。
	6、使用时，程序由其自己的变量管理器对自己内部的变量分配内存。
	7、程序运行完时，变量管理器归还内存。


*/
