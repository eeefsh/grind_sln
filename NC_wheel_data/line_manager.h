#pragma once
//#ifdef NC_wheel_data_EXPORTS
//#define NC_wheel_data_API __declspec(dllexport)
//#else
//#define NC_wheel_data_API __declspec(dllimport)
//#endif
#include"read_dxf.h"
#include"manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#define DXF_LINE 101.0
#define DXF_ARC 100.0

//线条管理
class line_data
{
public:
	/*存储数据，每列为一个数据
	第0行类型标记，圆弧:100.0，直线:101.0
			圆弧			直线
	第1行	圆心x			起点x
	第2行	圆心y			起点y
	第3行	圆心z			起点z
	第4行	半径r			终点x
	第5行	起始角度start	终点y
	第6行	结束角度end		终点z*/
	mat show_data;
	//返回值为直线或者圆弧的标记
	//ans返回数据vec(7)
	int read_data(size_t col, vec& ans);
	//获取圆弧参数
	//输入vec(7)
	bool get_arc_data(const vec& in, vec& c, double& r_l, double& start, double& end);
	//获取直线参数
	//输入vec(7)
	bool get_line_data(const vec& in, vec& start, vec& end);
};
class line_manager :
	private line_data
{
private:
	std::vector<dxf_arc*> all_arc;
	std::vector<dxf_line*> all_line;
	dxf_point min_xyz;
	bool shapes = 0;


public:

	line_manager(const std::string& filename);
	//获得所有直线
	void get_all_line(std::vector<dxf_line*>& all_line_in);
	//获得所有圆弧
	void get_all_arc(std::vector<dxf_arc*>& all_arc_in);
	//判断是封闭图形
	bool is_closed_shape();
	//判断是多个图形
	bool is_multiple_shapes();
	//转换线条反向
	void reverse_start_end();
	//直线倒圆角
	//void set_round(double r);
	/*获取离散点
	输入连续两点的距离d
	获取的mat数据，每列为一个点数据：
	第0行 切向x
	第1行 切向y
	第2行 切向z
	第3行 点x
	第4行 点y
	第5行 点z*/
	//void get_discrete_point(double d, mat& points);
	/*获取离散点
	输入圆弧平滑度e(平滑度越小，精度越高)，直线采样三个点，
	获取的mat数据，每列为一个点数据：
	第0行 切向x
	第1行 切向y
	第2行 切向z
	第3行 点x
	第4行 点y
	第5行 点z*/
	void get_curvature_point(double e, mat& points);
	//void show();
	//显示离散的点
	//输入点的距离d
	//void show_point(double d);
	//void show_point(double d);
	//显示离散的点
	//输入圆弧的平滑度
	//平滑度越小，精度越高
	//void show_point_e(double e);

	/*获取离散点
	输入连续两点的距离d
	获取的vec数据，每列为一个点数据：
	第0行 切向x
	第1行 切向y
	第2行 切向z
	第3行 点x
	第4行 点y
	第5行 点z*/
	void get_discrete_point(double d, std::vector<vec>& points);
	//积分取点
	//L比较距离
	//angle比较角度
	//末尾会补出一个点
	void get_integral_point(double L, double angle, std::vector<vec>& points);
	//L比较距离
	//angle比较角度
	//末尾会补出一个点
	//void show_point(double L, double angle);
private:
	//void _show_arc();
	//void _show_line();
private:
	//直线倒圆角
	//1、直线与圆弧相切不倒角
	//2、两个要倒圆角的线段之间的距离小于圆角半径不能倒角
	//3、
	void set_round(double r_l);
	//寻找图块原点
	void find_min_xyz(double x, double y, double z);
	//取所有点来寻找最小坐标边界
	void take_all_points();
	//移动图形左下角到原点
	void move_to_origin();
	//线段排序
	void sort();
	//把直线类型数据存储到vec
	void join_line(dxf_line* line, vec& v);
	//把圆弧类型数据存储到vec
	void join_arc(dxf_arc* arc, vec& v);
	//将图形数据存入矩阵
	void add_to_datamat();
	//输入矩阵和要取的第i列元素
	//返回该数据的起点坐标和终点坐标vec(6)
	vec get_extreme(int i, mat data_in);
	/*判断是不是相邻的线
	0：不相邻
	1：domain→value→
	2：value→domain→
	3：domain→value→domain
	4：domain→←value
	8：←value-domain→
	12：←value-domain→←value*/
	int is_in_domain(vec& domain, vec& value);
	//交换直线的起点和终点vec(7)
	void change_line(vec& line);
	//交换圆弧的起点角度和终点角度
	//角度正为逆时针，角度负为顺时针
	void change_arc(vec& arc);
	//离散直线为带向量的点
	//d为两点最小直线距离
	void discrete_line(vec line_in, double d, mat& mat_in);
	//离散圆弧为带向量的点
	//d为两点最小弧线距离
	void discrete_arc(vec arc_in, double d, mat& mat_in);
	//离散圆弧为带向量的点
	//angle为最小分度角
	void discrete_arc_angle(vec arc_in, double angle, mat& mat_in);
	//判断直线是一个点
	bool line_is_point(vec& line);
	//判断圆弧是一个点
	bool arc_is_point(vec& arc);
	//计算直线长度
	//vec(7)
	double line_L(vec& line);
	//计算圆弧总角度
	double arc_L(const vec& arc);

	double discrete_line2(const vec& line_in, const double& d, const double& offset, std::vector<vec>& point_in);
	double discrete_arc2(const vec& line_in, const double& d, const double& offset, std::vector<vec>& point_in);

	//判断两条直线满足倒圆角
	//vec(7)
	bool line_line_round_OK(vec& first, vec& second, double r_l);

};

