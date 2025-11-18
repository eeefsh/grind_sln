#pragma once
#include "wheel_define.h"
#include <vector>
#include <string>
#include "wheel_database.h"
#include "manager_h/MA_010401_Cal_ZuoBiaoBianHuan.h"
#include <map>

#pragma region 自定义点数据
namespace wheel_namespace
{

	//存储vec(3)
	//列：x,y,z
	class vec_point
	{
	private:
		unsigned int size_n;
		mat show_data;
	public:

		vec_point();
		void push_back(const vec& val);
		unsigned int size();
		void clear();
		void insert_back(std::vector<vec>& val);
		void insert_back(vec_point& val);
		//整体变换
		//传入3阶矩阵
		vec_point& transformation(mat& val);
		vec operator[](unsigned int index);
		//反向排序
		void resort();
	};
}
#pragma endregion

namespace wheel_namespace
{
	//接口类
	class port_getData
	{
	public:
		virtual void get_data(wheel_database_namespace::wheel_data& data) {};
		//virtual void get_data(wheel_database_namespace::wheel_data& data, wheel_database_namespace::shalun_data_namespace::dxf_dir& dir) {}
		virtual double get_T() { return double(); }
		virtual void turn_over() {}
		virtual void get_outline(mat& val) {}
		//获取文件路径
		virtual void get_dir(std::string& filename) {}

	public:
		virtual ~port_getData() {}
	};

	//回转体外轮廓类
	//1、对轮廓线有序点进行获取
	//2、轮廓反转功能
	class NC_wheel_data_API RotateOutline :
		virtual public port_getData
	{
	protected:
		//外轮廓点
		vec_point outline;
		//正面1 反面0
		bool flag;
	public:
		RotateOutline();

		//获取外轮廓点
		//vec(3) x,y,z
		void get_outline(std::vector<vec>& val);
		//获取外轮廓点
		//每列x,y,z
		void get_outline(mat& val);
		//获取外轮廓点
		//每列x,y,z
		mat get_outline();
		//获取外轮廓点
		void get_outline(vec_point& val);
		//沿y轴对称翻面
		void turn_over();
	};

	//处理圆弧相关的函数类
	class arc
	{
	protected:
		//圆弧角度划分
		//返回值是角度按照精度分段
		//err是插值后相邻两点的中点到圆心的距离偏差
		vec rot_angle(double err, double r, double start, double end);
		//获取圆弧插值点
		//圆心，精度，半径，起始角度，结束角度
		//err是插值后相邻两点的中点到圆心的距离偏差
		vec_point discrete_arc(vec c, double err, double r, double start, double end);
	};

	class wheel_list_data
	{
	public:
		std::string wheel_name;
		std::string group_name;
		std::string type;
		std::string time_new;
		int pos = 0;
	};

	class wheel_type
	{
	public:
		std::string type;
		int type_id = 0;
	};

	class group_list_data
	{
	public:
		std::string group_name;
		std::string wheel_name[3];
		std::string time_new;
		int pos = 0;
	};

	class NC_wheel_data_API canshu_1A1
	{
	public:
		double D = 100;
		double T = 10;
		double r_l = 0.1;
		double r_r = 0.1;
		std::string name;
	};
	class NC_wheel_data_API canshu_1V1
	{
	public:
		double D = 100;
		double T = 10;
		double S = 60;
		double r_l = 0.1;
		double r_r = 0.1;
		std::string name;
	};
	class NC_wheel_data_API canshu_14E1
	{
	public:
		double D = 100;
		double J = 50;
		double T = 6;
		double U = 4;
		double V = 60;
		double A = 45;
		double r_z = 0.1;
		std::string name;
	};
	class NC_wheel_data_API canshu_DXF
	{
	public:
		std::string dir;
		std::string name;
	};

	class NC_wheel_data_API group_wheel_cankao
	{
		bool _is_daozhuang = 0;
		bool _is_cankao_Left = 1;
		double distance = 0;
		double r = 0;
		double d = 0;
		double l = 0;
		int yuanjiao_flag = 0;
		int type = 0;
	public:
		bool is_daozhuang();
		bool is_cankao_Left();
		double get_distance();
		//1：设置倒装
		//0：设置正装
		void set_daozhuang(bool val);
		//1：设置参考左
		//0：设置参考右
		void set_cankao(bool val);
		//设置参考距离
		void set_distance(double val);
		//获取圆角r
		double get_r();
		//获取圆角d
		double get_d();
		//获取圆角l
		double get_l();
		//获取圆角r
		void set_r(double val);
		//获取圆角d
		void set_d(double val);
		//获取圆角l
		void set_l(double val);
		double get_type();
		void set_type(double val);
		//参考圆角标记
		//0：自定义圆角
		//1：r_l圆角
		//2：r_r圆角
		//3：r_z圆角
		int get_yuanjiao_flag();
		//参考圆角标记
		//0：自定义圆角
		//1：r_l圆角
		//2：r_r圆角
		//3：r_z圆角
		void set_yuanjiao_flag(int val);
	};

	class NC_wheel_data_API canshu_Group
	{
	public:
		double L0 = 10;
		double L1 = 120;
		double L2 = 20;
		double L3 = 10;
		double D0 = 50;
		double D1 = 20;
		double D2 = 15;
		double D3 = 25;
		std::vector<int> list_wheel_temp;
		//临时砂轮参考列表
		std::vector<wheel_namespace::group_wheel_cankao> list_wheel_cankao_temp;
		std::string name;
	};

	//砂轮数据输出基类
	class wheel_output_base
	{
	public:
		//获取直径
		virtual double get_D(bool& is_wrong);
		//获取厚度
		virtual double get_T(bool& is_wrong);
		//获取左圆角半径
		virtual double get_R_l(bool& is_wrong);
		//获取右圆角半径
		virtual double get_R_r(bool& is_wrong);
		//获取圆角精度
		virtual double get_R_acc(bool& is_wrong);
		//获取砂轮角度
		virtual double get_S(bool& is_wrong);
		//获取直径J
		virtual double get_J(bool& is_wrong);
		//获取厚度U
		virtual double get_U(bool& is_wrong);
		//获取中间圆角
		virtual double get_R_z(bool& is_wrong);
		//获取砂轮角度V
		virtual double get_V(bool& is_wrong);
		//获取砂轮角度a
		virtual double get_a(bool& is_wrong);
		//获取文件路径
		virtual std::string get_dir(bool& is_wrong);
	public:
		//获取直径
		virtual bool set_D(double val);
		//获取厚度
		virtual bool set_T(double val);
		//获取左圆角半径
		virtual bool set_R_l(double val);
		//获取右圆角半径
		virtual bool set_R_r(double val);
		//获取圆角精度
		virtual bool set_R_acc(double val);
		//获取砂轮角度
		virtual bool set_S(double val);
		//获取直径J
		virtual bool set_J(double val);
		//获取厚度U
		virtual bool set_U(double val);
		//获取中间圆角
		virtual bool set_R_z(double val);
		//获取砂轮角度V
		virtual bool set_V(double val);
		//获取砂轮角度a
		virtual bool set_a(double val);
		//获取文件路径
		virtual bool set_dir(std::string val);

	public:
		virtual ~wheel_output_base();
	};


}

class wheel_14E1;
class wheel_1A1;
class wheel_dxf;
class wheel_pole;
class wheel_group;

//砂轮管理类
class NC_wheel_data_API wheel:
	public wheel_database
{
public:
	wheel();
	//初始化数据库文件路径
	//1.砂轮索引文件路径
	//2.砂轮数据文件路径
	//3.砂轮组索引文件路径
	//4.砂轮组数据文件路径
	void Init_Dir(
		std::string dir_list_wheel,
		std::string dir_data_wheel,
		std::string dir_list_group,
		std::string dir_data_group);

	std::vector<wheel_namespace::wheel_type> wheel_type_all;
	//获取一条砂轮列表显示参数
	wheel_namespace::wheel_list_data get_wheel_canshu(int pos);
	//获取一条砂轮组列表显示参数
	wheel_namespace::group_list_data get_group_canshu(int pos);


//编辑砂轮参数使用的函数
private:
	//被编辑砂轮临时主键
	int wheel_edit_key_buff = -1;
public:
	//设置被编辑砂轮临时主键
	void set_wheel_edit_key_buff(int pos);

	//获取被编辑砂轮临时主键
	//调用后清除
	int get_wheel_edit_key_buff();


//砂轮组列表窗口使用的函数
public:
	//砂轮组临时添加砂轮的函数
	//返回0：安装成功
	//返回1：砂轮已被选择
	//返回2：砂轮已被安装到其他砂轮组
	int temp_add(int pos);

public:
	//砂轮数据转换为砂轮数据库数据
	void to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_14E1& val);

	//砂轮数据转换为砂轮数据库数据
	void to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_1A1& val);

	//砂轮数据转换为砂轮数据库数据
	void to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_1V1& val);

	//砂轮数据转换为砂轮数据库数据
	void to_wheel_data(wheel_database_namespace::wheel_data& temp, wheel_namespace::canshu_DXF& val);

//砂轮详细参数窗口使用的函数
public:
	//添加砂轮函数
	int wheel_add(wheel_namespace::canshu_14E1 val);

	//添加砂轮函数
	int wheel_add(wheel_namespace::canshu_1A1 val);

	//添加砂轮函数
	int wheel_add(wheel_namespace::canshu_1V1 val);

	//添加砂轮函数
	int wheel_add(wheel_namespace::canshu_DXF val);

	//编辑砂轮函数
	void wheel_edit(int pos, wheel_namespace::canshu_14E1 val);

	//编辑砂轮函数
	void wheel_edit(int pos, wheel_namespace::canshu_1A1 val);

	//编辑砂轮函数
	void wheel_edit(int pos, wheel_namespace::canshu_1V1 val);

	//编辑砂轮函数
	void wheel_edit(int pos, wheel_namespace::canshu_DXF val);

	//获取砂轮参数的函数
	void wheel_out(wheel_namespace::canshu_14E1& val, int _pos = -1);

	//获取砂轮参数的函数
	void wheel_out(wheel_namespace::canshu_1A1& val, int _pos = -1);

	//获取砂轮参数的函数
	void wheel_out(wheel_namespace::canshu_1V1& val, int _pos = -1);

	//获取砂轮参数的函数
	void wheel_out(wheel_namespace::canshu_DXF& val, int _pos = -1);
	
	//删除砂轮
	//删除失败返回 1
	//删除成功返回 0
	bool wheel_delete(int pos);
	
	//获取砂轮类型编码
	int get_wheel_type(int pos);
public:
	//添加砂轮组函数
	int group_add(wheel_namespace::canshu_Group val);
	//编辑砂轮组函数
	void group_edit(int pos, wheel_namespace::canshu_Group val);
	//删除砂轮组
	bool group_delete(int pos);
	//编辑砂轮组参数使用的函数
private:
	//被编辑砂轮组临时主键
	int group_edit_key_buff = -1;
public:
	//设置被编辑砂轮组临时主键
	void set_group_edit_key_buff(int pos);

	//获取被编辑砂轮组临时主键
	//调用后清除
	int get_group_edit_key_buff();

	//获取砂轮组参数的函数
	void group_out(wheel_namespace::canshu_Group& val);
private:
	//砂轮组数据转换为砂轮组数据库数据
	void to_group_data(wheel_database_namespace::group_data& temp, wheel_namespace::canshu_Group& val);
	
public:
	//临时砂轮列表
	std::vector<int> list_wheel_temp;
	//临时砂轮参考列表
	std::vector<wheel_namespace::group_wheel_cankao> list_wheel_cankao_temp;
	//清除临时砂轮列表
	void clear_list_wheel_temp();
	//清除临时砂轮列表
	void clear_list_wheel_cankao_temp();
	//计算_d_r_l
	void jisuan_d_r_l(int n);

private:

	void set_bit(unsigned char& val, int bit, bool in);

	void d_r_l_1A1(wheel_namespace::canshu_1A1 data, int n, int pos);

	void d_r_l_1V1(wheel_namespace::canshu_1V1 data, int n, int pos);

	void d_r_l_14E1(wheel_namespace::canshu_14E1 data, int n, int pos);

public:
	//获取一个砂轮组指针
	//输入：砂轮组主键
	wheel_group* get_a_group_ptr(int group_key);

	//获取一个砂轮组指针
	//输入：砂轮主键
	wheel_group* get_a_group_ptr_by_wheel(int wheel_key);

	//通过砂轮主键获取一个砂轮组主键
	//输入：砂轮主键
	int get_group_key_by_wheel(int wheel_key);

	//flag：0外，1内
	void get_d_r_l(int wheel_key, bool flag, double& d, double& r, double& l);

	//获取在砂轮组上的2D砂轮轮廓，包含位置信息
	//输入：砂轮主键
	//输出：每列为一个点x、y、z的mat 3*n
	mat get_2D_wheel_outline(int wheel_key);

	//获取砂轮厚度，不能获取dxf厚度
	double get_wheel_T(int wheel_key);

	//获取一个砂轮组上的砂轮键号
	//输入：砂轮组的键
	std::vector<int> get_a_group_all_wheel_key(int group_key);

};

//14E1型砂轮类
class NC_wheel_data_API wheel_14E1 :
	virtual public wheel_namespace::wheel_output_base,
	virtual public wheel_namespace::RotateOutline,
	virtual public wheel_namespace::arc
{
private:
	//直径
	double D;
	//直径J
	double J;
	//厚度
	double T;
	//厚度U
	double U;
	//倒角中
	double r_z;
	//砂轮角度
	double V;
	//砂轮角度a
	double a;
	//倒角精度
	double r_acc;
public:
	wheel_14E1();
	//设置砂轮参数
	void set_wheel(double _D, double _J, double _T, double _U, double _r_z, double _V = 45.0, double _a = 45.0, double _r_acc = 0.01);
	//设置砂轮参数
	void set_wheel(wheel_database_namespace::wheel_data data, bool _flag = 1, double _r_acc = 0.01);
	//获取厚度T
	double get_T();
public:
	//获取直径D
	virtual double get_D(bool& is_wrong);
	//获取直径J
	virtual double get_J(bool& is_wrong);
	//获取厚度T
	virtual double get_T(bool& is_wrong);
	//获取厚度U
	virtual double get_U(bool& is_wrong);
	//获取中间圆角
	virtual double get_R_z(bool& is_wrong);
	//获取砂轮角度V
	virtual double get_V(bool& is_wrong);
	//获取砂轮角度a
	virtual double get_a(bool& is_wrong);
	//获取圆角精度
	virtual double get_R_acc(bool& is_wrong);
public:
	//设置直径D
	virtual bool set_D(double val);
	//设置直径J
	virtual bool set_J(double val);
	//设置厚度T		  
	virtual bool set_T(double val);
	//设置厚度U	
	virtual bool set_U(double val);
	//设置中间圆角
	virtual bool set_R_z(double val);
	//设置砂轮角度V
	virtual bool set_V(double val);
	//设置砂轮角度a
	virtual bool set_a(double val);
	//设置圆角精度
	virtual bool set_R_acc(double val);
private:
	//更新外轮廓
	void renew_outline();
};

//1A1型砂轮类
class NC_wheel_data_API wheel_1A1 :
	virtual public wheel_namespace::wheel_output_base,
	virtual public wheel_namespace::RotateOutline,
	virtual public wheel_namespace::arc
{
private:
	//直径
	double D;
	//厚度
	double T;
	//倒角左
	double r_l;
	//倒角右
	double r_r;
	//倒角精度
	double r_acc;
public:
	wheel_1A1();
	//设置砂轮参数
	void set_wheel(double _D, double _T, double _r_l, double _r_r, double _r_acc = 0.01);
	//设置砂轮参数
	void set_wheel(wheel_database_namespace::wheel_data data, bool _flag = 1, double _r_acc = 0.01);
	
	//获取厚度T
	double get_T();
public:
	//获取直径
	virtual double get_D(bool& is_wrong);
	//获取厚度
	virtual double get_T(bool& is_wrong);
	//获取左圆角半径
	virtual double get_R_l(bool& is_wrong);
	//获取右圆角半径
	virtual double get_R_r(bool& is_wrong);
	//获取圆角精度
	virtual double get_R_acc(bool& is_wrong);
public:
	//获取直径
	virtual bool set_D(double val);
	//获取厚度
	virtual bool set_T(double val);
	//获取左圆角半径
	virtual bool set_R_l(double val);
	//获取右圆角半径
	virtual bool set_R_r(double val);
	//获取圆角精度
	virtual bool set_R_acc(double val);
private:
	//更新外轮廓
	void renew_outline();
};

//1V1型砂轮类
class NC_wheel_data_API wheel_1V1 :
	virtual public wheel_namespace::wheel_output_base,
	virtual public wheel_namespace::RotateOutline,
	virtual public wheel_namespace::arc
{
private:
	//直径
	double D;
	//厚度
	double T;
	//倒角左
	double r_l;
	//倒角右
	double r_r;
	//砂轮角度
	double S;
	//倒角精度
	double r_acc;
public:
	wheel_1V1();
	//设置砂轮参数
	void set_wheel(double _D, double _T, double _r_l, double _r_r, double _S, double _r_acc = 0.01);
	//设置砂轮参数
	void set_wheel(wheel_database_namespace::wheel_data data, bool _flag = 1, double _r_acc = 0.01);
	//获取厚度T
	double get_T();
public:
	//获取直径
	virtual double get_D(bool& is_wrong);
	//获取厚度
	virtual double get_T(bool& is_wrong);
	//获取左圆角半径
	virtual double get_R_l(bool& is_wrong);
	//获取右圆角半径
	virtual double get_R_r(bool& is_wrong);
	//获取圆角精度
	virtual double get_R_acc(bool& is_wrong);
	//获取砂轮角度
	virtual double get_S(bool& is_wrong);
public:
	//获取直径
	virtual bool set_D(double val);
	//获取厚度
	virtual bool set_T(double val);
	//获取左圆角半径
	virtual bool set_R_l(double val);
	//获取右圆角半径
	virtual bool set_R_r(double val);
	//获取圆角精度
	virtual bool set_R_acc(double val);
	//获取砂轮角度
	virtual bool set_S(double val);
private:
	//更新外轮廓
	void renew_outline();
};

//dxf输入类型
class NC_wheel_data_API wheel_dxf :
	virtual public wheel_namespace::wheel_output_base,
	virtual public wheel_namespace::RotateOutline
{
private:
	std::string filename_dir;
public:
	wheel_dxf();
	void set_wheel(std::string filename, double _r_acc = 0.01);
	//设置砂轮参数
	void set_wheel(wheel_database_namespace::wheel_data data, bool _flag = 1, double _r_acc = 0.01);
	
	//获取厚度T
	double get_T();
public:
	//获取厚度T
	virtual double get_T(bool& is_wrong);
	//获取圆角精度
	virtual double get_R_acc(bool& is_wrong);
	//获取文件路径
	virtual std::string get_dir(bool& is_wrong);
public:
	//设置圆角精度
	virtual bool set_R_acc(double val);
	//设置文件路径
	virtual bool set_dir(std::string val);
private:
	//更新外轮廓
	void renew_outline();
	//倒角精度
	double r_acc;
	double houdu;
};

//砂轮杆
class NC_wheel_data_API wheel_pole :
	virtual public wheel_namespace::RotateOutline
{
private:

	double D0;
	double D1;
	double D2;
	double L0;
	double L1;
	double L2;
public:
	wheel_pole();
	//设置砂轮杆
	void set_pole(double _D0, double _D1, double _D2, double _L0, double _L1, double _L2);
	//设置砂轮杆
	void set_pole(wheel_database_namespace::group_data data);
	

private:
	//更新外轮廓
	void renew_outline();
};

//砂轮组
class NC_wheel_data_API wheel_group
{
private:
	//螺母位置
	double nut_L;
	//最大安装砂轮个数
	int max_num;
private:
	//砂轮杆
	wheel_pole pole;
	//螺母
	wheel_1A1 nut;
	//杆、螺母、砂轮1、砂轮2、砂轮3
	mat* show_data[5];
public:
	wheel_group();
	~wheel_group();
	//设置杆
	void set_wheel_pole(
		double _L0, double _L1, double _L2,
		double _D0, double _D1, double _D2);

	//设置螺母
	void set_nut(double _L3, double _D3);

	//添加砂轮
	//砂轮最多安装3个
	//dz_flag:0正,1反
	//ck_flag:0左,1右
	//ck_d:参考距离
	void add_wheel(wheel_namespace::port_getData& val, bool dz_flag, bool ck_flag, double ck_d);

	//获取砂轮组显示外轮廓
	//每列向量x,y,z
	void get_show_outlines(std::vector<mat>& mat_vec);

	//获取砂轮组显示外轮廓
	//每列向量x,y,z
	std::vector<mat> get_show_outlines();

	//获取全部砂轮切削外轮廓
	//每列向量x,y,z
	void get_wheel_outline(mat& val);

	//获取全部砂轮切削外轮廓
	//每列向量x,y,z
	mat get_wheel_outline();

	
private:
	//查找pole_data的空位置
	void is_data_n(size_t& n);

};