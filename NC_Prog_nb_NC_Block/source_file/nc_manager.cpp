#include "..\pch.h"
#define NC_Prog_nb_NC_Block_EXPORTS
#include "nc_manager.h"

#pragma region 变量管理器类函数

#pragma region 变量类定义函数

#pragma region 构造函数
nc_var::nc_var()
{
	m_type = 0;
	m_num = 0;
}
nc_var::nc_var(int num, int type)
{
	m_num = num;
	m_type = type;
}
#pragma endregion

#pragma region 子函数
int nc_var::type()
{
	return m_type;
}
int nc_var::size()
{
	return m_num;
}
void nc_var::set(int num, int type)
{
	m_num = num;
	m_type = type;
}
#pragma endregion

#pragma endregion

#pragma region 变量类指针存储队列queue类

#pragma region 构造函数
nc_var_queue::nc_var_queue()
{
	clear();
}
nc_var_queue::~nc_var_queue()
{
	//clear();
}
#pragma endregion

#pragma region 子函数
void nc_var_queue::clear()
{
	while (!que.empty())
	{
		delete que.front();
		que.pop();
	}
}
void nc_var_queue::pop()
{
	que.pop();
}
void nc_var_queue::push(nc_var* A)
{
	que.push(A);
}
nc_var* nc_var_queue::front()
{
	return que.front();
}
nc_var* nc_var_queue::back()
{
	return que.back();
}
bool nc_var_queue::empty()
{
	return que.empty();
}
int nc_var_queue::size()
{
	return que.size();
}
#pragma endregion

#pragma endregion

#pragma region 变量分配类函数

nc_manager::nc_manager()
{
	//1 初始化成员
	usable_var.clear();
	used_var.clear();
	pro_now_index = 0;

	//2 预存一个主程序变量列队
	used_var.push_back(new nc_var_queue);

	//3 设置可用变量空间
	var_qujian();

	//4 随机排列所有变量，排入未使用队列中
	srand(5);
	//random_qujian();
}

nc_manager::~nc_manager()
{
	while (pro_now_index > 0)
	{
		while (!used_var[pro_now_index]->empty())
		{
			usable_var.push(used_var[pro_now_index]->front());
			used_var[pro_now_index]->pop();
		}
		pro_now_index--;
	}
	while (!used_var[pro_now_index]->empty())
	{
		usable_var.push(used_var[pro_now_index]->front());
		used_var[pro_now_index]->pop();
	}
	while (!usable_var.empty())
	{
		delete usable_var.front();
		usable_var.pop();
	}
	
}

void nc_manager::reset()
{
	while (pro_now_index > 0)
	{
		while (!used_var[pro_now_index]->empty())
		{
			usable_var.push(used_var[pro_now_index]->front());
			used_var[pro_now_index]->pop();
		}
		pro_now_index--;
	}
	while (!used_var[pro_now_index]->empty())
	{
		usable_var.push(used_var[pro_now_index]->front());
		used_var[pro_now_index]->pop();
	}
	while (!usable_var.empty())
	{
		delete usable_var.front();
		usable_var.pop();
	}

	//1 初始化成员
	usable_var.clear();
	used_var.clear();
	pro_now_index = 0;

	//2 预存一个主程序变量列队
	used_var.push_back(new nc_var_queue);

	//3 设置可用变量空间
	var_qujian();

	//4 随机排列所有变量，排入未使用队列中
	srand(5);
	//random_qujian();
}

#pragma region 输入区域
void nc_manager::var_qujian()
{
	//输入at变量编号的区间

	//add_qujian(1,400, 0);
	//add_qujian(656, 999, 0);
	//add_qujian(1009, 1402, 0);
	add_qujian(1408, 1746, 0);
	
	

	//输入#变量编号的区间
	//add_qujian(30, 399, 1);
}
#pragma endregion

#pragma region 子函数
void nc_manager::prog_start()
{
	//delete:(的数量增加，对应标示变量改变
	pro_now_index++;
	//已用编号的指针需装入的队列改变
	used_var.push_back(new nc_var_queue);
}
void nc_manager::prog_end()
{
	//若有子程序
	if (pro_now_index != 0)
	{
		//释放变量
		var_release();
		//(的数量减少
		pro_now_index--;
	}
	else
	{
		//报错
	}
}

void nc_manager::apply_var_num(int& type, int& num)
{
	//有可分配编号
	if (!usable_var.empty())
	{
		//将未使用队列中第一个变量放入当前程序的已使用变量队列
		nc_var* A = usable_var.front();
		usable_var.pop();
		used_var[pro_now_index]->push(A);

		//返回变量号
		type = A->type();
		num = A->size();

	}
	//返回0，表示分配完毕
	else
	{
		type = 0;
		num = 0;
	}
}
#pragma endregion

#pragma region 辅助函数
void nc_manager::add_qujian(int lower, int upper, int type)
{
	//防type输入错误
	if (type == 0 || type == 1)
	{
		//[a,b]内所有元素的指针装入队列
		for (int i = lower; i <= upper; i++)
		{
			nc_var* p = new nc_var(i, type);
			usable_var.push(p);
		}
	}
}
void nc_manager::random_qujian()
{
	//临时vec
	vector<nc_var*> vec_var;
	vec_var.clear();
	int max = usable_var.size();
	//队列元素装入vec
	while ((!usable_var.empty()))
	{
		vec_var.push_back(usable_var.front());
		usable_var.pop();
	}
	//vec内元素随机交换
	for (int i = 0; i < max; i++)
	{
		//0到max-1随机数
		int m = rand() % max;
		nc_var* p;
		p = vec_var[m];
		vec_var[m] = vec_var[i];
		vec_var[i] = p;
	}
	//vec元素装入队列
	usable_var.clear();
	while (!vec_var.empty())
	{
		usable_var.push(vec_var.back());
		vec_var.pop_back();
	}
}
void nc_manager::var_release()
{
	//释放当前子程序变量

	//将释放的变量 移到 未使用变量的列队
	while (!used_var[pro_now_index]->empty())
	{
		usable_var.push(used_var[pro_now_index]->front());
		used_var[pro_now_index]->pop();
	}
	//删除当前子程序 变量队列 内存空间
	delete used_var[pro_now_index];

	//删除当前子程序 列队
	used_var.pop_back();
}
#pragma endregion

#pragma endregion

#pragma endregion
