#include "pch.h"
//#define NC_wheel_data_EXPORTS

#include<iostream>
#include "read_dxf.h"
using namespace std;

/******************************* read_dxf函数 **************************************/
read_dxf::read_dxf(const string& filename):
	pos(0)
{
	//打开文件
	inputFile.open(filename);
	if (!inputFile.is_open())
	{
		terminate();
	}
	//定位到实体段
	pos = find_part("ENTITIES");
	//寻找目标对象并存储
	find_Line(all_line);
	find_Circle(all_circle);
	find_Arc(all_arc);
	//关闭文件
	inputFile.close();
}


void read_dxf::get_all_line(vector<dxf_line*>& all_line_in)
{
	all_line_in = all_line;
}



void read_dxf::get_all_circle(vector<dxf_circle*>& all_circle_in)
{
	all_circle_in = all_circle;
}

void read_dxf::get_all_arc(vector<dxf_arc*>& all_arc_in)
{
	all_arc_in = all_arc;
}

read_dxf::~read_dxf()
{
	for (size_t i = 0; i < all_line.size(); i++)
	{
		delete all_line[i];
	}
	for (size_t i = 0; i < all_arc.size(); i++)
	{
		delete all_arc[i];
	}
	for (size_t i = 0; i < all_circle.size(); i++)
	{
		delete all_circle[i];
	}
	all_line.clear();
	all_circle.clear();
	all_arc.clear();
}



streampos read_dxf::find_part(const string& name)
{
	//文件打开成功
	if(inputFile.is_open())
	{
		string temp;
		// 逐行读取文件内容
		while (getline(inputFile, temp))
		{
			//读到标志开始处
			if (temp == "  0")
			{
				getline(inputFile, temp);
				//dxf文件读取到最后
				if (temp == "EOF")
				{
					return -1;
				}
				//读到段开始位置
				else if(temp == "SECTION")
				{
					getline(inputFile, temp);
					getline(inputFile, temp);
					//判断段名是目标段
					if (temp == name)
					{
						//获取当前位置指针
						streampos ans = inputFile.tellg();
						return ans;
					}
				}
			}
		}
	}
	return -1;
}

streampos read_dxf::find_group(streampos position, const string& name)
{
	if (inputFile.is_open())
	{
		string temp;
		//通过指针跳到目标位置
		inputFile.seekg(position);
		// 逐行读取文件内容
		while (getline(inputFile, temp))
		{
			
			if (temp == "  0")
			{
				getline(inputFile, temp);
				//dxf文件读取到段尾
				if (temp == "ENDSEC")
				{
					return -1;
				}
				if (temp == name)
				{
					//获取当前位置指针
					streampos ans = inputFile.tellg();
					return ans;
				}

			}
		}
	}
	return -1;
}

streampos read_dxf::find_AcDb(streampos position, const string& name)
{
	if (inputFile.is_open())
	{
		string temp;

		inputFile.seekg(position);
		// 逐行读取文件内容
		while (getline(inputFile, temp))
		{

			//dxf文件读取到段尾
			if (temp == "ENDSEC")
			{
				return -1;
			}
			//找到目标AcDb
			if (temp == "100")
			{
				getline(inputFile, temp);
				if (temp == name)
				{
					//获取当前位置指针
					streampos ans = inputFile.tellg();
					return ans;
				}
			}
		}
	}
	return -1;
}


void read_dxf::find_Line(vector<dxf_line*>& all_line)
{
	streampos temp = pos;
	dxf_line* temp_ptr = nullptr;
	
	while (true)
	{
		//寻找LINE的位置
		temp = find_group(temp, "LINE");
		if (temp == -1)
		{
			break;
		}
		//寻找AcDbLine的位置
		temp = find_AcDb(temp, "AcDbLine");
		if (temp == -1)
		{
			break;
		}
		//获取一个直线
		temp_ptr = take_a_Line(temp);
		if (temp == -1)
		{
			break;
		}
		if (temp_ptr != nullptr)
		{
			all_line.push_back(temp_ptr);
		}
	}
}

void read_dxf::find_Circle(vector<dxf_circle*>& all_circle)
{
	streampos temp = pos;
	dxf_circle* temp_ptr = nullptr;

	while (true)
	{
		//寻找CIRCLE的位置
		temp = find_group(temp, "CIRCLE");
		if (temp == -1)
		{
			break;
		}
		//寻找AcDbCircle的位置
		temp = find_AcDb(temp, "AcDbCircle");
		if (temp == -1)
		{
			break;
		}
		//获取一个圆
		temp_ptr = take_a_Circle(temp);
		if (temp == -1)
		{
			break;
		}
		if (temp_ptr != nullptr)
		{
			all_circle.push_back(temp_ptr);
		}
	}
}

void read_dxf::find_Arc(vector<dxf_arc*>& all_arc)
{
	streampos temp = pos;
	dxf_circle* temp_ptr = nullptr;
	dxf_arc* temp_ptr1 = nullptr;
	while (true)
	{
		//寻找ARC的位置
		temp = find_group(temp, "ARC");
		if (temp == -1)
		{
			break;
		}
		//寻找AcDbCircle的位置
		temp = find_AcDb(temp, "AcDbCircle");
		if (temp == -1)
		{
			break;
		}
		//获取一个临时圆
		temp_ptr = take_a_Circle(temp);
		if (temp == -1)
		{
			break;
		}
		//寻找AcDbArc的位置
		temp = find_AcDb(temp, "AcDbArc");
		if (temp == -1)
		{
			break;
		}
		//获取一个圆弧
		temp_ptr1 = take_a_Arc(temp);
		if (temp == -1)
		{
			break;
		}

		if (temp_ptr != nullptr && temp_ptr1 != nullptr)
		{
			//将圆赋值到圆弧的基类数据里
			*temp_ptr1 = *temp_ptr;
			//删除临时圆
			delete temp_ptr;
			all_arc.push_back(temp_ptr1);
		}
	}
}


dxf_line* read_dxf::take_a_Line(streampos& position)
{
	string temp;
	dxf_point start(0, 0, 0);
	dxf_point end(0, 0, 0);
	if (inputFile.is_open())
	{
		inputFile.seekg(position);
		//存储开始点
		for (size_t i = 0; i < 3; i++)
		{
			getline(inputFile, temp);
			getline(inputFile, temp);
			start.set_c(i) = stod(temp);
		}
		//存储结束点
		for (size_t i = 0; i < 3; i++)
		{
			getline(inputFile, temp);
			getline(inputFile, temp);
			end.set_c(i) = stod(temp);
		}
		position = inputFile.tellg();
		return new dxf_line(start, end);
	}
	return nullptr;
}

dxf_circle* read_dxf::take_a_Circle(streampos& position)
{
	string temp;
	dxf_point center(0, 0, 0);
	double r_l;
	if (inputFile.is_open())
	{
		inputFile.seekg(position);
		//存储圆心
		for (size_t i = 0; i < 3; i++)
		{
			getline(inputFile, temp);
			getline(inputFile, temp);
			center.set_c(i) = stod(temp);
		}
		//存储半径
		getline(inputFile, temp);
		getline(inputFile, temp);
		r_l = stod(temp);
		position = inputFile.tellg();
		return new dxf_circle(center, r_l);
	}
	return nullptr;
}

dxf_arc* read_dxf::take_a_Arc(streampos& position)
{
	string temp;
	double start;
	double end;
	if (inputFile.is_open())
	{
		inputFile.seekg(position);
		//存储起始角度
		getline(inputFile, temp);
		getline(inputFile, temp);
		start = stod(temp);
		//存储结束角度
		getline(inputFile, temp);
		getline(inputFile, temp);
		end = stod(temp);

		return new dxf_arc(start, end);
	}
	return nullptr;
}

/**************************** read_dxf函数 **************************************/


/**************************** dxf_line函数 **************************************/
dxf_line::dxf_line(dxf_point start_in, dxf_point end_in):
	start(start_in),
	end(end_in)
{
}

dxf_point* dxf_line::get_start()
{
	return &start;
}

dxf_point* dxf_line::get_end()
{
	return &end;
}

void dxf_line::print()
{
	cout <<"Line："
		<< "Start = " << start.get_c_ptr()[0] << "  " << start.get_c_ptr()[1] << "  " << start.get_c_ptr()[2] << ", "
		<< "End = " << end.get_c_ptr()[0] << "  " << end.get_c_ptr()[1] << "  " << end.get_c_ptr()[2] << endl;
}

/**************************** dxf_line函数 **************************************/


/**************************** dxf_circle函数 **************************************/
dxf_circle::dxf_circle(dxf_point center_in = {0, 0, 0}, double r_in = 0) :
	center(center_in),
	r_l(r_in)
{
}

dxf_point* dxf_circle::get_center()
{
	return &center;
}

double dxf_circle::get_r()
{
	return r_l;
}

void dxf_circle::print()
{
	cout << "Circle："
		<< "Center = " << center.get_c_ptr()[0] << "  " << center.get_c_ptr()[1] << "  " << center.get_c_ptr()[2] << ", "
		<< "R = " << r_l << endl;
}

/**************************** dxf_circle函数 **************************************/


/**************************** dxf_circle函数 **************************************/
dxf_arc::dxf_arc(double start_in = 0, double end_in = 0):
	start(start_in),
	end(end_in)
{
}

double dxf_arc::get_start()
{
	return start;
}

double dxf_arc::get_end()
{
	return end;
}

dxf_point* dxf_arc::get_center()
{
	return dxf_circle::get_center();
}

double dxf_arc::get_r()
{
	return dxf_circle::get_r();
}

void dxf_arc::print()
{
	cout <<"Arc："
		<< "Center = " << center.get_c_ptr()[0] << "  " << center.get_c_ptr()[1] << "  " << center.get_c_ptr()[2] << ", "
		<< "R = " << r_l << ", "
		<< "Start = " << start << ", " 
		<< "End = " << end << endl;
	
}

/**************************** dxf_circle函数 **************************************/


/**************************** dxf_point函数 **************************************/
dxf_point::dxf_point(double x_in = 0, double y_in = 0, double z_in = 0) :
	_c{ x_in, y_in, z_in }
{
}

dxf_point::dxf_point():
	_c{ 0, 0, 0 }
{
}

double* dxf_point::get_c_ptr()
{
	return _c;
}

double& dxf_point::set_c(int size_n)
{
	return _c[size_n];
}

void dxf_point::print()
{
	cout << "Point：X = " << _c[0] << ", " << "Y = " << _c[1] << ", " << "Z = " << _c[2] << endl;
}

/**************************** dxf_point函数 **************************************/