#pragma once
#include "pch.h"

nc_block is_G54();
nc_block is_G55();
nc_block is_G56();
nc_block is_G57();
nc_block is_G58();
nc_block is_G59();

nc_block is_plane_x();
nc_block is_plane_y();
nc_block is_plane_z();

nc_block inner_X_current();
nc_block inner_Y_current();
nc_block inner_Z_current();
nc_block inner_A_current();
nc_block inner_C_current();
nc_block inner_X_coorMac();
nc_block inner_Y_coorMac();
nc_block inner_Z_coorMac();
nc_block inner_A_coorMac();
nc_block inner_C_coorMac();
nc_block inner_X_coorAbs();
nc_block inner_Y_coorAbs();
nc_block inner_Z_coorAbs();
nc_block inner_A_coorAbs();
nc_block inner_C_coorAbs();
nc_block tance_done();

nc_block set_safe_x_abs(double x);
nc_block set_safe_y_abs(double y);
nc_block set_safe_z_abs(double z);
nc_block set_safe_x_abs(nc_block x);
nc_block set_safe_y_abs(nc_block y);
nc_block set_safe_z_abs(nc_block z);
nc_block get_safe_x_abs();
nc_block get_safe_y_abs();
nc_block get_safe_z_abs();

nc_block set_safe_plane_x(nc_block x);
nc_block set_safe_plane_x(double x);
nc_block set_safe_plane_y(nc_block y);
nc_block set_safe_plane_y(double y);
nc_block set_safe_plane_z(nc_block z);
nc_block set_safe_plane_z(double z);
nc_block get_safe_plane_x();
nc_block get_safe_plane_y();
nc_block get_safe_plane_z();

//nc_block set_M_O_A_xyz(nc_block_vec3 O_xyz);
//nc_block set_M_O_A_xyz(vec3 O_xyz);
//nc_block set_M_O_A_xyz(double x, double y, double z);
//nc_block set_M_O_A_X(nc_block x);
//nc_block set_M_O_A_X(double x);
//nc_block set_M_O_A_Y(nc_block y);
//nc_block set_M_O_A_Y(double y);
//nc_block set_M_O_A_Z(nc_block z);
//nc_block set_M_O_A_Z(double z);
//
//nc_block set_M_O_A_A(nc_block A);
//nc_block set_M_O_A_A(double A);
//nc_block set_M_O_A_C(nc_block C);
//nc_block set_M_O_A_C(double C);
nc_block get_M_O_A_X();
nc_block get_M_O_A_Y();
nc_block get_M_O_A_Z();
nc_block get_M_O_A_A();
nc_block get_M_O_A_C();

//nc_block set_cube_length(nc_block l);
//nc_block set_cube_length(double l);
//nc_block set_cube_width(nc_block w);
//nc_block set_cube_width(double w);
//nc_block set_cube_depth(nc_block d);
//nc_block set_cube_depth(double d);
//nc_block get_cube_length();
//nc_block get_cube_width();
//nc_block get_cube_depth();

//«Ú≤‚’Î-∫Ï±¶ Ø«Ú∞Îæ∂£ªµ∂≤‚’Î-±ÿ–Î…Ë0.0
nc_block set_probe_r(nc_block r);
//«Ú≤‚’Î-∫Ï±¶ Ø«Ú∞Îæ∂£ªµ∂≤‚’Î-±ÿ–Î…Ë0.0
nc_block set_probe_r(double r);
//«Ú≤‚’Î-¬›Œ∆∂À√ÊµΩ∫Ï±¶ Ø«Ú–ƒ≥§∂»;
nc_block set_probe_l(nc_block r);
//«Ú≤‚’Î-¬›Œ∆∂À√ÊµΩ∫Ï±¶ Ø«Ú–ƒ≥§∂»£ª
nc_block set_probe_l(double l);
nc_block get_probe_r();
nc_block get_probe_l();

nc_block set_probe_dao_x(nc_block x);
nc_block set_probe_dao_x(double x);
nc_block set_probe_dao_y(nc_block y);
nc_block set_probe_dao_y(double y);
nc_block set_probe_dao_z(nc_block z);
nc_block set_probe_dao_z(double z);
nc_block get_probe_dao_x();
nc_block get_probe_dao_y();
nc_block get_probe_dao_z();

nc_block set_biaoding_xyz(double x, double y, double z);
nc_block get_biaoding_x();
nc_block get_biaoding_y();
nc_block get_biaoding_z();