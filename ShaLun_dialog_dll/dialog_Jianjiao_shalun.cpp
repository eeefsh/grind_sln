// dialog_Jianjiao_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_Jianjiao_shalun.h"
#include "resource.h"

// dialog_Jianjiao_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_Jianjiao_shalun, CDialogEx)

dialog_Jianjiao_shalun::dialog_Jianjiao_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Jianjiao_shalun, pParent)
{

}

dialog_Jianjiao_shalun::~dialog_Jianjiao_shalun()
{
}

void dialog_Jianjiao_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_EDIT1, m_Zhijing);
	DDX_Control(pDX, IDC_EDIT2, m_Yuanjiao);
	DDX_Control(pDX, IDC_EDIT3, m_Jiaodu);
	DDX_Control(pDX, IDC_EDIT4, m_Kuandu);
	DDX_Control(pDX, IDC_CHECK1, m_auto_jiti);
	DDX_Control(pDX, IDC_EDIT5, m_Jiti_D);
	DDX_Control(pDX, IDC_EDIT6, m_Jiti_jiao);
	DDX_Control(pDX, IDC_EDIT8, m_Jiti_kuan);
	DDX_Control(pDX, IDC_CUSTOM1, m_draw);
}


BEGIN_MESSAGE_MAP(dialog_Jianjiao_shalun, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &dialog_Jianjiao_shalun::OnBnClickedCheck1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &dialog_Jianjiao_shalun::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT3, &dialog_Jianjiao_shalun::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &dialog_Jianjiao_shalun::OnEnKillfocusEdit4)
	ON_BN_CLICKED(IDOK, &dialog_Jianjiao_shalun::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT2, &dialog_Jianjiao_shalun::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT5, &dialog_Jianjiao_shalun::OnEnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, &dialog_Jianjiao_shalun::OnEnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT8, &dialog_Jianjiao_shalun::OnEnKillfocusEdit8)
	ON_EN_CHANGE(IDC_EDIT7, &dialog_Jianjiao_shalun::OnEnChangeEdit7)
END_MESSAGE_MAP()


// dialog_Jianjiao_shalun 消息处理程序

BOOL dialog_Jianjiao_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_Jianjiao_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
		if (canshu.auto_Jiti)
		{
			m_auto_jiti.SetCheck(1);
			m_Jiti_D.EnableWindow(0);
			m_Jiti_jiao.EnableWindow(0);
			m_Jiti_kuan.EnableWindow(0);
		}
		else
		{
			m_auto_jiti.SetCheck(0);
			m_Jiti_D.EnableWindow();
			m_Jiti_jiao.EnableWindow();
			m_Jiti_kuan.EnableWindow();
		}
	}
	else
	{
		m_auto_jiti.SetCheck(1);
		m_Jiti_D.EnableWindow(0);
		m_Jiti_jiao.EnableWindow(0);
		m_Jiti_kuan.EnableWindow(0);
	}
	updata_show();
	set_draw();
}

void dialog_Jianjiao_shalun::updata_show()
{
	CString strValue;

	strValue.Format(_T("%.3f"), canshu.Zhijing_D);
	m_Zhijing.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Yuanjiao_r);
	m_Yuanjiao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiaodu);
	m_Jiaodu.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Kuandu);
	m_Kuandu.SetWindowTextW(strValue);

	strValue.Format(_T("%.3f"), canshu.Jiti_D);
	m_Jiti_D.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiti_jiao);
	m_Jiti_jiao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiti_kuan);
	m_Jiti_kuan.SetWindowTextW(strValue);
}

void dialog_Jianjiao_shalun::get_canshu()
{
	CString temp;

	m_Zhijing.GetWindowTextW(temp);
	canshu.Zhijing_D = _tstof(temp);

	m_Yuanjiao.GetWindowTextW(temp);
	canshu.Yuanjiao_r = _tstof(temp);

	m_Jiaodu.GetWindowTextW(temp);
	canshu.Jiaodu = _tstof(temp);

	m_Kuandu.GetWindowTextW(temp);
	canshu.Kuandu = _tstof(temp);

	m_Jiti_D.GetWindowTextW(temp);
	canshu.Jiti_D = _tstof(temp);

	m_Jiti_jiao.GetWindowTextW(temp);
	canshu.Jiti_jiao = _tstof(temp);

	m_Jiti_kuan.GetWindowTextW(temp);
	canshu.Jiti_kuan = _tstof(temp);

	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	canshu.name = temp_str;

	if (m_auto_jiti.GetCheck() == 1)
	{
		canshu.auto_Jiti = 1;
	}
	else
	{
		canshu.auto_Jiti = 0;
	}
}

void dialog_Jianjiao_shalun::jisuan_canshu()
{
	if (canshu.auto_Jiti)
	{
		canshu.jisuan_canshu();
	}
}

void dialog_Jianjiao_shalun::save_canshu()
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

void dialog_Jianjiao_shalun::set_draw()
{
	get_canshu();
	jisuan_canshu();
	updata_show();
	auto line1 = canshu.To_wheel_data();
	canshu.Jisuan_Yuanjiao(line1, 0, 0);
	auto line = wheel_output_namespace::wheel_outlines::wheel_Jianjiao_2D(line1);
	mat reflected = line;
	reflected.rows(1, 2) = -reflected.rows(1, 2);
	reflected = fliplr(reflected);
	line = join_horiz(line, reflected);
	m_draw.Set_wheel_outline(line);
}

void dialog_Jianjiao_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_Jianjiao_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_Jianjiao_shalun::OnBnClickedCheck1()
{
	
	if (m_auto_jiti.GetCheck())
	{
		m_Jiti_D.EnableWindow(0);
		m_Jiti_jiao.EnableWindow(0);
		m_Jiti_kuan.EnableWindow(0);
		auto_show();
	}
	else
	{
		m_Jiti_D.EnableWindow();
		m_Jiti_jiao.EnableWindow();
		m_Jiti_kuan.EnableWindow();
	}
}

void dialog_Jianjiao_shalun::auto_show()
{
	CString strValue;
	m_Zhijing.GetWindowTextW(strValue);
	canshu.Zhijing_D = _tstof(strValue);
	m_Jiaodu.GetWindowTextW(strValue);
	canshu.Jiaodu = _tstof(strValue);
	m_Kuandu.GetWindowTextW(strValue);
	canshu.Kuandu = _tstof(strValue);
	jisuan_canshu();
	strValue.Format(_T("%.3f"), canshu.Jiti_D);
	m_Jiti_D.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiti_jiao);
	m_Jiti_jiao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Jiti_kuan);
	m_Jiti_kuan.SetWindowTextW(strValue);
}

void dialog_Jianjiao_shalun::OnBnClickedOk()
{
	if (m_name.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("请设置名称"), _T("提示"), MB_ICONWARNING);
		return;
	}

	CString temp;
	m_Zhijing.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("直径不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Jiti_D.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("基体直径不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Kuandu.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("宽度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Yuanjiao.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Jiaodu.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("角度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Jiti_jiao.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("基体角度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Jiti_kuan.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("基体宽度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}

	save_canshu();
	CDialogEx::OnOK();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit1()
{
	if (m_auto_jiti.GetCheck())
	{
		auto_show();
	}
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit2()
{
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit3()
{
	if (m_auto_jiti.GetCheck())
	{
		auto_show();
	}
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit4()
{
	if (m_auto_jiti.GetCheck())
	{
		auto_show();
	}
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit5()
{
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit6()
{
	set_draw();
}

void dialog_Jianjiao_shalun::OnEnKillfocusEdit8()
{
	set_draw();
}


void dialog_Jianjiao_shalun::OnEnChangeEdit7()
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

BOOL dialog_Jianjiao_shalun::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		set_draw();
		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
