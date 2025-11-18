#include "pch.h"
#include "jiaoxian_StateMachine.h"

void jiaoxian_StateMachine::loop_StateMachine()
{
	if (is_pause || complete_simulation)
	{
		return;
	}
	else
	{
		//全步模式
		if (State_flag == jiaoxian_StateMachine_namespace::STEP_Full)
		{
			if (gongyi_data.is_pos_end())
			{
				pause_simulation();
				complete_simulation = 1;
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
			}
			else
			{
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
				gongyi_data.last_ptr();
			}
		}
		//单步模式
		else if (State_flag == jiaoxian_StateMachine_namespace::STEP_Single)
		{
			pause_simulation();
			if (gongyi_data.is_pos_end())
			{
				complete_simulation = 1;
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
			}
			else
			{
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
				gongyi_data.last_ptr();
			}
		}
		//单齿模式
		else if (State_flag == jiaoxian_StateMachine_namespace::STEP_Single_tooth)
		{
			if (gongyi_data.is_pos_end())
			{
				complete_simulation = 1;
				pause_simulation();
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
			}
			else
			{
				if (gongyi_data.is_duan_end())
				{
					pause_simulation();
				}
				//显示数据输出
				mat ans;
				get_show_data(ans);
				ans_buff.push_back(ans);
				gongyi_data.last_ptr();
			}
		}
		else
		{

		}
	}
	
}

void jiaoxian_StateMachine::Init(gongyi_input& val)
{
	gongyi_data = val;
}

void jiaoxian_StateMachine::get_buff(std::vector<mat>& val)
{
	val = ans_buff;
	ans_buff.clear();
}

std::vector<mat>& jiaoxian_StateMachine::get_buff()
{
	return ans_buff;
}

void jiaoxian_StateMachine::clear_buff()
{
	ans_buff.clear();
}

jiaoxian_StateMachine::jiaoxian_StateMachine()
{


}

void jiaoxian_StateMachine::set_STEP_Full()
{
	State_flag = jiaoxian_StateMachine_namespace::STEP_Full;
	clear_pause();
	is_reset = 0;
}

void jiaoxian_StateMachine::set_STEP_Single()
{
	State_flag = jiaoxian_StateMachine_namespace::STEP_Single;
	clear_pause();
	is_reset = 0;
}

void jiaoxian_StateMachine::set_STEP_Single_tooth()
{
	State_flag = jiaoxian_StateMachine_namespace::STEP_Single_tooth;
	clear_pause();
	is_reset = 0;
}

void jiaoxian_StateMachine::reset_simulation()
{
	gongyi_data.reset_ptr();
	pause_simulation();
	complete_simulation = 0;
	is_reset = 1;
}

void jiaoxian_StateMachine::pause_simulation()
{
	is_pause = 1;
}

void jiaoxian_StateMachine::clear_pause()
{
	is_pause = 0;
}

void jiaoxian_StateMachine::get_show_data(mat& val)
{
	mat ans = gongyi_data.get_one_pos();
	val = face_line.get_outline_point(ans);
}


void Simulation2D::set_face(mat44 _view)
{
	G_SYS_Look = _view;
	gj.set_jiemian(_view);
}

void Simulation2D::set_wheel_outline(mat val)
{
	wheel_outline.clear();
	wheel_outline = val;
}

void Simulation2D::set_line(mat line)
{
	//mat out = line.cols(0, line.n_cols - 1).t();
	//out.save("9.9-test-2D-xx.txt", raw_ascii);


	gj.set_gj_line(line);
}

void Simulation2D::set_gj_YuanZhu(double D, double L)
{
	gj.set_gj_YuanZhu(D, L);
}

void Simulation2D::set_gj_WeiZhi(mat _sys)
{
	gj.set_gj_WeiZhi(_sys);
}

mat Simulation2D::get_look_points()
{
	return gj.get_look_points();
}

mat Simulation2D::get_show_data(mat G_SYS_SL)
{
	face_line.set_jiemian(G_SYS_Look, wheel_outline);
	return face_line.get_outline_point(G_SYS_SL);
}

