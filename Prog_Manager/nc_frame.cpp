#include"pch.h"
#include"nc_frame.h"

nc_block is_G54()
{
	return ChangShu(0.0);
}

nc_block is_G55()
{
	return ChangShu(1.0);
}

nc_block is_G56()
{
	return ChangShu(2.0);
}

nc_block is_G57()
{
	return ChangShu(3.0);
}

nc_block is_G58()
{
	return ChangShu(4.0);
}

nc_block is_G59()
{
	return ChangShu(5.0);
}

nc_block is_plane_x()
{
	return ChangShu(0.0);
}

nc_block is_plane_y()
{
	return ChangShu(1.0);
}

nc_block is_plane_z()
{
	return ChangShu(2.0);
}

nc_block inner_X_current()
{
	return BL_Block(1, 1321);
}

nc_block inner_Y_current()
{
	return BL_Block(1, 1322);
}

nc_block inner_Z_current()
{
	return BL_Block(1, 1323);
}

nc_block inner_A_current()
{
	return BL_Block(1, 1324);
}

nc_block inner_C_current()
{
	return BL_Block(1, 1325);
}

nc_block inner_X_coorMac()
{
	return BL_Block(1, 1441);
}

nc_block inner_Y_coorMac()
{
	return BL_Block(1, 1442);
}

nc_block inner_Z_coorMac()
{
	return BL_Block(1, 1443);
}

nc_block inner_A_coorMac()
{
	return BL_Block(1, 1444);
}

nc_block inner_C_coorMac()
{
	return BL_Block(1, 1445);
}

nc_block inner_X_coorAbs()
{
	return BL_Block(1, 1361);
}

nc_block inner_Y_coorAbs()
{
	return BL_Block(1, 1362);
}

nc_block inner_Z_coorAbs()
{
	return BL_Block(1, 1363);
}

nc_block inner_A_coorAbs()
{
	return BL_Block(1, 1364);
}

nc_block inner_C_coorAbs()
{
	return BL_Block(1, 1365);
}

nc_block tance_done()
{
	return BL_Block(1, 1608);
}

nc_block set_safe_x_abs(double x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1871) = x);
	return entr;
}

nc_block set_safe_y_abs(double y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1872) = y);
	return entr;
}

nc_block set_safe_z_abs(double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1873) = z);
	return entr;
}

nc_block set_safe_x_abs(nc_block x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1871) = x);
	return entr;
}

nc_block set_safe_y_abs(nc_block y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1872) = y);
	return entr;
}

nc_block set_safe_z_abs(nc_block z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1873) = z);
	return entr;
}

nc_block get_safe_x_abs()
{
	return BL(1871);
}

nc_block get_safe_y_abs()
{
	return  BL(1872);
}

nc_block get_safe_z_abs()
{
	return  BL(1873);
}

nc_block set_safe_plane_x(nc_block x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1874) = x);
	return entr;
}

nc_block set_safe_plane_x(double x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1874) = x);
	return entr;
}

nc_block set_safe_plane_y(nc_block y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1875) = y);
	return entr;
}

nc_block set_safe_plane_y(double y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1875) = y);
	return entr;
}

nc_block set_safe_plane_z(nc_block z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1876) = z);
	return entr;
}

nc_block set_safe_plane_z(double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1876) = z);
	return entr;
}

nc_block get_safe_plane_x()
{
	return BL(1874);
}

nc_block get_safe_plane_y()
{
	return BL(1875);
}

nc_block get_safe_plane_z()
{
	return BL(1876);
}

nc_block set_M_O_A_xyz(nc_block_vec3 O_xyz)
{
	nc_block entr(Process_K(0));
	entr << (BL(1877) = O_xyz(0));
	entr << (BL(1878) = O_xyz(0));
	entr << (BL(1879) = O_xyz(0));
	return entr;
}

nc_block set_M_O_A_xyz(vec3 O_xyz)
{
	nc_block entr(Process_K(0));
	entr << (BL(1877) = O_xyz(0));
	entr << (BL(1878) = O_xyz(0));
	entr << (BL(1879) = O_xyz(0));
	return entr;
}

nc_block set_M_O_A_xyz(double x, double y, double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1877) = x);
	entr << (BL(1878) = y);
	entr << (BL(1879) = z);
	return entr;
}

nc_block set_M_O_A_X(nc_block x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1877) = x);
	return entr;
}

nc_block set_M_O_A_X(double x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1877) = x);
	return entr;
}

nc_block set_M_O_A_Y(nc_block y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1878) = y);
	return entr;
}

nc_block set_M_O_A_Y(double y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1878) = y);
	return entr;
}

nc_block set_M_O_A_Z(nc_block z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1879) = z);
	return entr;
}

nc_block set_M_O_A_Z(double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1879) = z);
	return entr;
}

nc_block set_M_O_A_A(nc_block A)
{
	nc_block entr(Process_K(0));
	entr << (BL(1880) = A);
	return entr;
}

nc_block set_M_O_A_A(double A)
{
	nc_block entr(Process_K(0));
	entr << (BL(1880) = A);
	return entr;
}

nc_block set_M_O_A_C(nc_block C)
{
	nc_block entr(Process_K(0));
	entr << (BL(1881) = C);
	return entr;
}

nc_block set_M_O_A_C(double C)
{
	nc_block entr(Process_K(0));
	entr << (BL(1881) = C);
	return entr;
}

nc_block get_M_O_A_X()
{
	return BL(1877);
}

nc_block get_M_O_A_Y()
{
	return BL(1878);
}

nc_block get_M_O_A_Z()
{
	return BL(1879);
}

nc_block get_M_O_A_A()
{
	return BL(1880);
}

nc_block get_M_O_A_C()
{
	return BL(1881);
}

nc_block set_cube_length(nc_block l)
{
	nc_block entr(Process_K(0));
	entr << (BL(1887) = l);
	return entr;
}

nc_block set_cube_length(double l)
{
	nc_block entr(Process_K(0));
	entr << (BL(1887) = l);
	return entr;
}

nc_block set_cube_width(nc_block w)
{
	nc_block entr(Process_K(0));
	entr << (BL(1888) = w);
	return entr;
}

nc_block set_cube_width(double w)
{
	nc_block entr(Process_K(0));
	entr << (BL(1888) = w);
	return entr;
}

nc_block set_cube_depth(nc_block d)
{
	nc_block entr(Process_K(0));
	entr << (BL(1889) = d);
	return entr;
}

nc_block set_cube_depth(double d)
{
	nc_block entr(Process_K(0));
	entr << (BL(1889) = d);
	return entr;
}

nc_block get_cube_length()
{
	return BL(1887);
}

nc_block get_cube_width()
{
	return BL(1888);
}

nc_block get_cube_depth()
{
	return BL(1889);
}

nc_block set_probe_r(nc_block r)
{
	nc_block entr(Process_K(0));
	entr << (BL(1890) = r);
	return entr;
}

nc_block set_probe_r(double r)
{
	nc_block entr(Process_K(0));
	entr << (BL(1890) = r);
	return entr;
}

nc_block set_probe_l(nc_block l)
{
	nc_block entr(Process_K(0));
	entr << (BL(1891) = l);
	return entr;
}

nc_block set_probe_l(double l)
{
	nc_block entr(Process_K(0));
	entr << (BL(1891) = l);
	return entr;
}

nc_block get_probe_r()
{
	return BL(1890);
}

nc_block get_probe_l()
{
	return BL(1891);
}

nc_block set_probe_dao_x(nc_block x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1892) = x);
	return entr;
}

nc_block set_probe_dao_x(double x)
{
	nc_block entr(Process_K(0));
	entr << (BL(1892) = x);
	return entr;
}

nc_block set_probe_dao_y(nc_block y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1893) = y);
	return entr;
}

nc_block set_probe_dao_y(double y)
{
	nc_block entr(Process_K(0));
	entr << (BL(1893) = y);
	return entr;
}

nc_block set_probe_dao_z(nc_block z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1894) = z);
	return entr;
}

nc_block set_probe_dao_z(double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1894) = z);
	return entr;
}

nc_block get_probe_dao_x()
{
	return BL(1892);
}

nc_block get_probe_dao_y()
{
	return BL(1893);
}

nc_block get_probe_dao_z()
{
	return BL(1894);
}

nc_block set_biaoding_xyz(double x, double y, double z)
{
	nc_block entr(Process_K(0));
	entr << (BL(1895) = x);
	entr << (BL(1896) = y);
	entr << (BL(1897) = z);
	return entr;
}

nc_block get_biaoding_x()
{
	return BL(1895);
}

nc_block get_biaoding_y()
{
	return BL(1896);
}

nc_block get_biaoding_z()
{
	return BL(1897);
}