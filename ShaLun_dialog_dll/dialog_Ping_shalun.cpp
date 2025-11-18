// dialog_Ping_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_Ping_shalun.h"
#include "resource.h"


// dialog_Ping_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_Ping_shalun, CDialogEx)

dialog_Ping_shalun::dialog_Ping_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Ping_shalun, pParent)
{

}

dialog_Ping_shalun::~dialog_Ping_shalun()
{
}

void dialog_Ping_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_daozhuang1, daozhuang_1);
	DDX_Control(pDX, IDC_RADIO_daozhuang2, daozhuang_2);
	DDX_Control(pDX, IDC_EDIT1, m_Dadaun_D);
	DDX_Control(pDX, IDC_EDIT2, m_Xiaoduan_D);
	DDX_Control(pDX, IDC_EDIT3, m_Daduan_yuanjiao_r);
	DDX_Control(pDX, IDC_EDIT4, m_Xiaoduan_yuanjiao_r);
	DDX_Control(pDX, IDC_EDIT5, m_Jiaodu);
	DDX_Control(pDX, IDC_EDIT6, m_Kuandu);
	DDX_Control(pDX, IDC_RADIO1, Celiang_Daduan);
	DDX_Control(pDX, IDC_RADIO2, Celiang_Xiaoduan);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_CUSTOM1, m_draw);
}


BEGIN_MESSAGE_MAP(dialog_Ping_shalun, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_Ping_shalun::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT7, &dialog_Ping_shalun::OnEnChangeEdit_name)
	ON_EN_KILLFOCUS(IDC_EDIT1, &dialog_Ping_shalun::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_RADIO1, &dialog_Ping_shalun::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &dialog_Ping_shalun::OnBnClickedRadio2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &dialog_Ping_shalun::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT5, &dialog_Ping_shalun::OnEnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, &dialog_Ping_shalun::OnEnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT4, &dialog_Ping_shalun::OnEnKillfocusEdit4)
	ON_BN_CLICKED(IDC_RADIO_daozhuang1, &dialog_Ping_shalun::OnBnClickedRadiodaozhuang1)
	ON_BN_CLICKED(IDC_RADIO_daozhuang2, &dialog_Ping_shalun::OnBnClickedRadiodaozhuang2)
	ON_EN_KILLFOCUS(IDC_EDIT2, &dialog_Ping_shalun::OnEnKillfocusEdit2)
END_MESSAGE_MAP()


// dialog_Ping_shalun 消息处理程序

BOOL dialog_Ping_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_Xiaoduan_D.EnableWindow(0);
	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void dialog_Ping_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
		if (canshu.Celiang_flag)
		{
			m_Xiaoduan_D.EnableWindow();
			m_Dadaun_D.EnableWindow(0);
		}
	}
	updata_show();
	set_draw();
}

void dialog_Ping_shalun::updata_show()
{
	CString strValue;
	if (canshu.Celiang_flag)
	{
		Celiang_Xiaoduan.SetCheck(1);
	}
	else
	{
		Celiang_Daduan.SetCheck(1);
	}
	if (canshu.daozhuang_flag)
	{
		daozhuang_2.SetCheck(1);
	}
	else
	{
		daozhuang_1.SetCheck(1);
	}
	strValue.Format(_T("%.3f"), canshu.Daduan_D);
	m_Dadaun_D.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Xiaoduan_D);
	m_Xiaoduan_D.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Daduan_Yuanjiao_r);
	m_Daduan_yuanjiao_r.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Xiaoduan_Yuanjiao_r);
	m_Xiaoduan_yuanjiao_r.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiaodu);
	m_Jiaodu.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Kuandu);
	m_Kuandu.SetWindowTextW(strValue);


}

void dialog_Ping_shalun::get_canshu()
{
	CString temp;

	m_Dadaun_D.GetWindowTextW(temp);
	canshu.Daduan_D = _tstof(temp);

	m_Xiaoduan_D.GetWindowTextW(temp);
	canshu.Xiaoduan_D = _tstof(temp);

	m_Daduan_yuanjiao_r.GetWindowTextW(temp);
	canshu.Daduan_Yuanjiao_r = _tstof(temp);

	m_Xiaoduan_yuanjiao_r.GetWindowTextW(temp);
	canshu.Xiaoduan_Yuanjiao_r = _tstof(temp);

	m_Jiaodu.GetWindowTextW(temp);
	canshu.Jiaodu = _tstof(temp);

	m_Kuandu.GetWindowTextW(temp);
	canshu.Kuandu = _tstof(temp);

	m_name.GetWindowTextW(temp);

	CT2CA temp_str(temp);
	canshu.name = temp_str;

	if (daozhuang_1.GetCheck() == 1)
	{
		canshu.daozhuang_flag = 0;
	}
	else
	{
		canshu.daozhuang_flag = 1;
	}

	if (Celiang_Daduan.GetCheck() == 1)
	{
		canshu.Celiang_flag = 0;
	}
	else
	{
		canshu.Celiang_flag = 1;
	}
}

void dialog_Ping_shalun::jisuan_canshu()
{
	if (Celiang_Daduan.GetCheck())
	{
		canshu.jisuan_canshu(0);
	}
	else
	{
		canshu.jisuan_canshu(1);
	}
}

void dialog_Ping_shalun::save_canshu()
{
	get_canshu();
	if (is_open)
	{
		auto w_data = wheel_ptr->read_wheel(buff_wheel_pos);

		wheel_ptr->edit_wheel(buff_wheel_pos, canshu.To_wheel_data(w_data));
	}
	else
	{
		wheel_ptr->add_wheel(canshu.To_wheel_data());
	}

}

void dialog_Ping_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_Ping_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_Ping_shalun::OnBnClickedOk()
{
	if (m_name.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("请设置名称"), _T("提示"), MB_ICONWARNING);
		return;
	}

	CString temp;
	m_Dadaun_D.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("直径不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Xiaoduan_D.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("直径不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Kuandu.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("宽度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Daduan_yuanjiao_r.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Xiaoduan_yuanjiao_r.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	save_canshu();
	CDialogEx::OnOK();
}



void dialog_Ping_shalun::OnEnChangeEdit_name()
{
	const int max_char = 50;
	CString temp;
	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	std::string str_buff = temp_str;
	if (name_flag)
	{
		m_name.SetSel(temp.GetLength(), temp.GetLength());
		name_flag = 0;
	}
	if (str_buff.size() > max_char)
	{
		int num = temp.GetLength();
		temp = temp.Left(num - 1);
		name_flag = 1;
		m_name.SetWindowTextW(temp);
	}
}


void dialog_Ping_shalun::set_draw()
{
	get_canshu();
	jisuan_canshu();
	updata_show();
	auto line1 = canshu.To_wheel_data();
	canshu.Jisuan_Yuanjiao(line1, 0, 0);
	auto line = wheel_output_namespace::wheel_outlines::wheel_Ping_2D(line1);
	mat reflected = line;
	reflected.rows(1, 2) = -reflected.rows(1, 2);
	reflected = fliplr(reflected);
	line = join_horiz(line, reflected);
	m_draw.Set_wheel_outline(line);
}

void dialog_Ping_shalun::OnBnClickedRadio1()
{
	m_Dadaun_D.EnableWindow();
	m_Xiaoduan_D.EnableWindow(0);
	set_draw();
}

void dialog_Ping_shalun::OnBnClickedRadio2()
{
	m_Dadaun_D.EnableWindow(0);
	m_Xiaoduan_D.EnableWindow();
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit1()
{
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit2()
{
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit3()
{
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit4()
{
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit5()
{
	set_draw();
}

void dialog_Ping_shalun::OnEnKillfocusEdit6()
{
	set_draw();
}

void dialog_Ping_shalun::OnBnClickedRadiodaozhuang1()
{
	set_draw();
}

void dialog_Ping_shalun::OnBnClickedRadiodaozhuang2()
{
	set_draw();
}

BOOL dialog_Ping_shalun::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		set_draw();
		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

