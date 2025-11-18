#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Tool_Canshu.h"

//


CanShu_Geo_ZQ::CanShu_Geo_ZQ()
{
	D = 10.0;   //球直径
	len_ren = 20.0;	//刃的轴线长度
	len_all = 50.0;	
	ang_zhui = 0.0;	//半锥角

	ang_end_luo = 35.0;		//球头结束螺旋角  等于螺旋角

	xishu_aotu =1.0; //曲线凹凸系数，默认1.0


	ang_luoxuan=30.0;	//等螺旋角

	ren_count=4; //刃的个数，通常为2,3,4,6
	is_dengfen = 1;

	 hdm_1_width=1.0;	//后刀面1宽度
	 hdm_1_d_qiu=0.0; //径向-刀尖
	 hdm_1_a_qiu=5.0;	//轴向
	 hdm_1_d_mid=5.0;
	 hdm_1_a_mid=3.0;
	 hdm_1_d_luo=10.0;
	 hdm_1_a_luo=0.0;
				
	 hdm_2_width=1.0;	//后刀面2宽度
	 hdm_2_d_qiu=0.0;  //径向
	 hdm_2_a_qiu=5.0;	//轴向
	 hdm_2_d_mid=5.0;
	 hdm_2_a_mid=3.0;
	 hdm_2_d_luo=10.0;
	 hdm_2_a_luo=0.0;
				
	 hdm_3_width=1.0;	//后刀面3宽度
	 hdm_3_d_qiu=0.0;  //径向
	 hdm_3_a_qiu=5.0;	//轴向
	 hdm_3_d_mid=5.0;
	 hdm_3_a_mid=3.0;
	 hdm_3_d_luo=10.0;
	 hdm_3_a_luo=0.0;

	 for (int i = 0; i < 6; i++)
	 {
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	 }
}

CanShu_Geo_PD::CanShu_Geo_PD()
{
	D =10.0;	// 柱直径
	len_ren = 20.0;	//刃的轴线长度
	len_all = 50.0;
	ang_die=2.0;	//蝶形角
	ang_luo=35.0;	//螺旋角

	ren_count=5; //刃的个数，通常为2,3,4,6
	is_dengfen=1;


	hdm_1_width=1.0;	//后刀面1宽度
	hdm_1_a_hen=5.0;	//轴向--横刃只有
	hdm_1_d_luo=10.0;

	hdm_2_width = 1.0;	//后刀面2宽度
	hdm_2_a_hen = 5.0;	//轴向--横刃只有
	hdm_2_d_luo = 10.0;

	hdm_3_width = 1.0;	//后刀面3宽度
	hdm_3_a_hen = 5.0;	//轴向--横刃只有
	hdm_3_d_luo = 10.0;

	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}
}

CanShu_Geo_R::CanShu_Geo_R()
{
	D=10.0;	//柱直径
	ang_die=2.0;	//蝶形角
	ang_luo=35.0;	//螺旋角
	len_ren = 20.0;	//刃的轴线长度
	len_all = 50.0;

	R_qiu=0.2;	//圆角半径

	ren_count=4; //刃的个数，通常为2,3,4,6
	is_dengfen=1;

	hdm_1_width=1.0;	//后刀面1宽度
	hdm_1_a_hen=5.0;	//横刃轴向
	hdm_1_d_rrr=5.0; //圆角径向
	hdm_1_d_luo=10.0;

	hdm_2_width = 1.0;	//后刀面2宽度
	hdm_2_a_hen = 5.0;	//横刃轴向
	hdm_2_d_rrr = 5.0;  //圆角径向
	hdm_2_d_luo = 10.0;

	hdm_3_width = 1.0;	//后刀面3宽度
	hdm_3_a_hen = 5.0;	//横刃轴向
	hdm_3_d_rrr = 5.0;  //圆角径向
	hdm_3_d_luo = 10.0;

	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}

}

CanShu_Geo_CX::CanShu_Geo_CX()
{
	type = -1; //0-参数，1-型线

	cx_D = 10.0;
	cx_len = 50.0;
	cx_zhui = 0.0;

	cx_sel_xx_id = -1;
	cx_is_max_ring = -1;

	for (int i = 0; i < 6; i++)
	{
		v_no_dengfen_angle[i] = 0.0;
		v_pianxin_dis[i] = 0.0;
		v_center_dis[i] = 0.0;
	}
}
