#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif

#include"buchang_tance_zi.h"

class Prog_Manager_API length_tance_fu :
	public nc_program_fu
{
public:
	//01 构造与析构
	length_tance_fu(nc_program_zi_fangzhichongfu* father, int nc_var_type);

	//02 函数主体
	void prog_main();
	//03 输入输出变量

	vec3 v_points_in; //端面点大致位置已知
	vec3 v_nors_in;
    double v_dis_jiagong_in;
	double v_A_in;
	double v_C_in;

	double dis_safe_in;  //统一成一把刀设置一次
	double dis_start_in;
	double dis_more_in;

	//04 函数调用
	nc_block diaoyong();

	//05 成员子函数
	F_zi_tance_3_axis zi_obj;

	//对外接口
public:
	//设置探测需要的几个距离
	void set_tance_dis(double in_safe, double in_start, double in_more);

private:
	//根据工序类型，探测点在模型的顺序，确定存储位置
	int find_num_BL_pos(int in_gx_type, int in_p_pos);
};


/*
* // 函数：计算绕Z轴旋转和绕旋转坐标系X轴旋转的角度
void calculateRotationAngles(Vector3d& point, Vector3d& direction, double& theta1, double& theta2) {
    // 1. 原始向量：point 是起点，direction 是方向向量
    // point: 向量的起点坐标
    // direction: 向量的方向

    // 2. 计算绕Z轴旋转的角度 theta1
    // 我们想让旋转后的向量与原始坐标系的Z轴对齐，即方向 (0, 0, 1)
    
    // 计算在XY平面上的投影
    double x = direction(0);
    double y = direction(1);
    
    // 计算theta1，绕Z轴旋转角度
    theta1 = atan2(y, x);  // atan2 可以避免除零错误，返回从X轴到向量的角度
    
    // 计算旋转后的方向向量
    Matrix3d Rz;
    Rz << cos(theta1), -sin(theta1), 0,
          sin(theta1), cos(theta1), 0,
          0, 0, 1;
    
    // 旋转后的向量
    Vector3d rotatedDirection = Rz * direction;

    // 3. 计算绕旋转坐标系新X轴旋转的角度 theta2
    // 新的X轴方向是 Rz 旋转矩阵乘以 (1, 0, 0)
    Vector3d newX = Rz * Vector3d(1, 0, 0);
    
    // 我们希望新的向量与Z轴对齐，计算旋转角度
    // 计算新的方向与Z轴的夹角，theta2是绕新X轴旋转的角度
    theta2 = acos(rotatedDirection(2)); // 计算夹角，旋转后的z分量
    
    // 4. 输出计算结果
    cout << "Rotation around Z-axis (theta1): " << theta1 * 180.0 / M_PI << " degrees" << endl;
    cout << "Rotation around new X-axis (theta2): " << theta2 * 180.0 / M_PI << " degrees" << endl;
}

int main() {
    // 向量的起点与方向
    Vector3d point(20, 0, 10);
    Vector3d direction(-0.49, -0.85, -0.17);
    
    double theta1, theta2;  // 旋转角度

    // 调用函数计算旋转角度
    calculateRotationAngles(point, direction, theta1, theta2);

    return 0;
}
*/
