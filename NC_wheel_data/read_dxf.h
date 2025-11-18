#pragma once
//#ifdef NC_wheel_data_EXPORTS
//#define NC_wheel_data_API __declspec(dllexport)
//#else
//#define NC_wheel_data_API __declspec(dllimport)
//#endif
#include <fstream>
#include <string>
#include <vector>
/// <summary>
/// 说明：
///		读取dxf格式文件中的圆、圆弧和直线
/// 
/// ***********************************************
/// 第1次编辑
/// 时间：2023-10-18
/// 编辑：龚权新
/// 文件：
///		read_dxf.h
///		read_dxf.cpp
/// ***********************************************

/// </summary>


class dxf_point;
class dxf_line;
class dxf_circle;
class dxf_arc;


//读dxf文件
class read_dxf
{
private:
	//目标文件
	std::ifstream inputFile;
	//文件内容位置指针
	std::streampos pos;

	std::vector<dxf_line*> all_line;
	std::vector<dxf_circle*> all_circle;
	std::vector<dxf_arc*> all_arc;

public:
	read_dxf(const std::string& filename);
	//获得所有直线
	void get_all_line(std::vector<dxf_line*>& all_line_in);
	//获得所有圆
	void get_all_circle(std::vector<dxf_circle*>& all_circle_in);
	//获得所有圆弧
	void get_all_arc(std::vector<dxf_arc*>& all_arc_in);
	~read_dxf();

private:
	//查找目标段的位置
	std::streampos find_part(const std::string& name);
	//从指定位置查找目标组码位置
	std::streampos find_group(std::streampos position, const std::string& name);
	//从指定位置查找目标AcDb位置
	std::streampos find_AcDb(std::streampos position, const std::string& name);

private:
	//查找所有直线
	void find_Line(std::vector<dxf_line*>& all_line_in);
	//查找所有圆
	void find_Circle(std::vector<dxf_circle*>& all_circle);
	//查找所有圆弧
	void find_Arc(std::vector<dxf_arc*>& all_arc);

private:
	//取一个直线
	dxf_line* take_a_Line(std::streampos& position);
	//取一个圆
	dxf_circle* take_a_Circle(std::streampos& position);
	//取一个圆弧
	dxf_arc* take_a_Arc(std::streampos& position);
};

//dxf点
class dxf_point
{
	
protected:
	double _c[3];
public:
	dxf_point(double x_in, double y_in, double z_in);
	dxf_point();
	//获得_c数组指针
	//0:x  1:y  2:z
	double* get_c_ptr();
	//设置坐标值
	//0:x  1:y  2:z
	double& set_c(int size_n);
	void print();
};

//dxf直线
class dxf_line
{
private:
	//直线起点
	dxf_point start;
	//直线终点
	dxf_point end;
public:
	dxf_line(dxf_point start_in, dxf_point end_in);
	dxf_point* get_start();
	dxf_point* get_end();
	void print();
};

//dxf圆
class dxf_circle
{
protected:
	//圆心
	dxf_point center;
	//半径
	double r_l;
public:
	dxf_circle(dxf_point center_in, double r_in);
	dxf_point* get_center();
	double get_r();
	void print();
};

//dxf圆弧
class dxf_arc :
	protected dxf_circle
{
private:
	//起始角度
	double start;
	//结束角度
	double end;
public:
	dxf_arc(double start_in, double end_in);
	double get_start();
	double get_end();
	dxf_point* get_center();
	double get_r();
	void print();
private:
	// 重载赋值运算符=，将基类对象赋值给派生类对象的基类成员
	dxf_arc& operator=(const dxf_circle& base) {
		// 将基类对象的数据复制到派生类对象的基类成员
		dxf_circle::operator=(base);
		return *this;
	}
	friend class read_dxf;
};