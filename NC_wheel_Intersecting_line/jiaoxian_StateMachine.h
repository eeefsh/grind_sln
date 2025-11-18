#pragma once
#ifdef NC_wheel_Intersecting_line_EXPORTS
#define NC_wheel_Intersecting_line_API __declspec(dllexport)
#else
#define NC_wheel_Intersecting_line_API __declspec(dllimport)
#endif

#include "gongyi_input.h"
#include "jiaoxian_wheel.h"
#include "gongjian_2D.h"
namespace jiaoxian_StateMachine_namespace
{
	//全步状态
	const int STEP_Full = 1;
	//单步状态
	const int STEP_Single = 2;
	//单齿状态
	const int STEP_Single_tooth = 3;
}

//交线状态机
class NC_wheel_Intersecting_line_API jiaoxian_StateMachine
{
private:

	//截面线类
	jie_mian_xian face_line;
private:
	//状态标记
	int State_flag = 0;
	//工艺数据
	gongyi_input gongyi_data;
	//输出轮廓线缓存区
	std::vector<mat> ans_buff;
public:
	//循环状态机
	//输出轮廓点
	void loop_StateMachine();
	//初始化工艺
	void Init(gongyi_input& val);
	//设置截面
	void reset_face(mat44 _view)
	{
		face_line.set_jiemian(_view, gongyi_data.get_one_wheel());
	}
public:
	//获取缓存的截面线(每次调用后清除)
	void get_buff(std::vector<mat>& val);
	//获取缓存的截面线(每次调用后需要手动清除clear_buff)
	std::vector<mat>& get_buff();
	//清除缓存区
	void clear_buff();
	//判断是重置标记
	bool is_reset = 1;
public:
	jiaoxian_StateMachine();
	//暂停标记
	bool is_pause = 1;
	//仿真结束标记
	bool complete_simulation = 0;
	//设置全步状态
	void set_STEP_Full();
	//设置单步状态
	void set_STEP_Single();
	//设置单齿状态
	void set_STEP_Single_tooth();
	//重置仿真
	void reset_simulation();
	//暂停仿真
	void pause_simulation();
private:
	//清除暂停标记
	void clear_pause();
	//获取显示数据
	void get_show_data(mat& val);
};

class NC_wheel_Intersecting_line_API Simulation2D
{
	//截面线类
	jie_mian_xian face_line;
	//砂轮外轮廓
	mat wheel_outline;
	//2D工件
	gongjian_2D gj;

public:
	//视口矩阵
	mat44 G_SYS_Look;
public:
	//设置截面
	void set_face(mat44 _view);
	//设置砂轮外轮廓
	void set_wheel_outline(mat val);

	//输入型线，X轴为长度轴，一列一个点
	void set_line(mat line);

	//设置圆柱工件
	//输入直接D，长度L
	void set_gj_YuanZhu(double D, double L);

	//设置工件位置
	//sys: mat4*4
	void set_gj_WeiZhi(mat _sys);

	//获取工件显示截线数据
	mat get_look_points();

	
	//获取截面线点mat每列为xyz
	//输入砂轮位置
	mat get_show_data(mat pos);

};