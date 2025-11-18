// dialog_Beixing_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_Beixing_shalun.h"
#include "resource.h"

// dialog_Beixing_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_Beixing_shalun, CDialogEx)

dialog_Beixing_shalun::dialog_Beixing_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Beixing_shalun, pParent)
{

}

dialog_Beixing_shalun::~dialog_Beixing_shalun()
{
}

void dialog_Beixing_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_EDIT1, m_Zhijing_D);
	DDX_Control(pDX, IDC_EDIT2, m_Yuanjiao);
	DDX_Control(pDX, IDC_EDIT3, m_Kuandu);
	DDX_Control(pDX, IDC_EDIT4, m_Neishen);
	DDX_Control(pDX, IDC_CHECK1, m_auto_Neishen);
	DDX_Control(pDX, IDC_EDIT5, m_Moliao);
	DDX_Control(pDX, IDC_EDIT6, m_Jiao_nei);
	DDX_Control(pDX, IDC_EDIT8, m_Jiao_wai);
	DDX_Control(pDX, IDC_CUSTOM1, m_draw);
}

void dialog_Beixing_shalun::set_draw()
{
	get_canshu();
	jisuan_canshu();
	updata_show();
	auto line1 = canshu.To_wheel_data();
	canshu.Jisuan_Yuanjiao(line1, 0, 0);
	auto line = wheel_output_namespace::wheel_outlines::wheel_Beixing_2D(line1);
	mat reflected = line;
	reflected.rows(1, 2) = -reflected.rows(1, 2);
	reflected = fliplr(reflected);
	line = join_horiz(line, reflected);
	m_draw.Set_wheel_outline(line);
}

void dialog_Beixing_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
		if (canshu.auto_Neishen)
		{
			m_auto_Neishen.SetCheck(1);
		}
		else
		{
			m_auto_Neishen.SetCheck(0);
		}
	}
	else
	{
		m_auto_Neishen.SetCheck(1);
	}
	updata_show();
	set_draw();
}

void dialog_Beixing_shalun::updata_show()
{
	CString strValue;
	if (canshu.auto_Neishen)
	{
		m_Neishen.EnableWindow(0);
	}
	else
	{
		m_Neishen.EnableWindow(1);
	}
	strValue.Format(_T("%.3f"), canshu.jiao_nei);
	m_Jiao_nei.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.jiao_wai);
	m_Jiao_wai.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Kuandu);
	m_Kuandu.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Moliao);
	m_Moliao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Neishen);
	m_Neishen.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Yuanjiao_r);
	m_Yuanjiao.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Zhijing_D);
	m_Zhijing_D.SetWindowTextW(strValue);
}

void dialog_Beixing_shalun::get_canshu()
{
	CString temp;

	m_Zhijing_D.GetWindowTextW(temp);
	canshu.Zhijing_D = _tstof(temp);

	m_Yuanjiao.GetWindowTextW(temp);
	canshu.Yuanjiao_r = _tstof(temp);

	m_Kuandu.GetWindowTextW(temp);
	canshu.Kuandu = _tstof(temp);

	m_Moliao.GetWindowTextW(temp);
	canshu.Moliao = _tstof(temp);

	m_Neishen.GetWindowTextW(temp);
	canshu.Neishen = _tstof(temp);

	m_Jiao_nei.GetWindowTextW(temp);
	canshu.jiao_nei = _tstof(temp);

	m_Jiao_wai.GetWindowTextW(temp);
	canshu.jiao_wai = _tstof(temp);

	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	canshu.name = temp_str;

	if (m_auto_Neishen.GetCheck() == 1)
	{
		canshu.auto_Neishen = 1;
	}
	else
	{
		canshu.auto_Neishen = 0;
	}
}

void dialog_Beixing_shalun::jisuan_canshu()
{
	if (canshu.auto_Neishen)
	{
		canshu.jisuan_canshu();
	}
}

void dialog_Beixing_shalun::save_canshu()
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

void dialog_Beixing_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_Beixing_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}


BEGIN_MESSAGE_MAP(dialog_Beixing_shalun, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_Beixing_shalun::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &dialog_Beixing_shalun::OnBnClickedCheck1)
	ON_EN_KILLFOCUS(IDC_EDIT3, &dialog_Beixing_shalun::OnEnKillfocusEdit3)
	ON_EN_CHANGE(IDC_EDIT7, &dialog_Beixing_shalun::OnEnChangeEdit_name)
	ON_EN_KILLFOCUS(IDC_EDIT1, &dialog_Beixing_shalun::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &dialog_Beixing_shalun::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT4, &dialog_Beixing_shalun::OnEnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, &dialog_Beixing_shalun::OnEnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, &dialog_Beixing_shalun::OnEnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT8, &dialog_Beixing_shalun::OnEnKillfocusEdit8)
END_MESSAGE_MAP()


// dialog_Beixing_shalun 消息处理程序

void dialog_Beixing_shalun::OnBnClickedOk()
{
	if (m_name.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("请设置名称"), _T("提示"), MB_ICONWARNING);
		return;
	}

	CString temp;
	m_Zhijing_D.GetWindowTextW(temp);
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
	m_Yuanjiao.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	save_canshu();
	CDialogEx::OnOK();
}

BOOL dialog_Beixing_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_Beixing_shalun::OnBnClickedCheck1()
{
	CString strValue;
	if (m_auto_Neishen.GetCheck())
	{
		m_Neishen.EnableWindow(0);
		m_Kuandu.GetWindowTextW(strValue);
		canshu.Kuandu = _tstof(strValue);
		jisuan_canshu();
		strValue.Format(_T("%.3f"), canshu.Neishen);
		m_Neishen.SetWindowTextW(strValue);
	}
	else
	{
		m_Neishen.EnableWindow(1);
	}
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit3()
{
	CString strValue;
	if (m_auto_Neishen.GetCheck())
	{
		m_Kuandu.GetWindowTextW(strValue);
		canshu.Kuandu = _tstof(strValue);
		jisuan_canshu();
		strValue.Format(_T("%.3f"), canshu.Neishen);
		m_Neishen.SetWindowTextW(strValue);
	}
	set_draw();
}

void dialog_Beixing_shalun::OnEnChangeEdit_name()
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

void dialog_Beixing_shalun::OnEnKillfocusEdit1()
{
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit2()
{
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit4()
{
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit5()
{
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit6()
{
	set_draw();
}

void dialog_Beixing_shalun::OnEnKillfocusEdit8()
{
	set_draw();
}

BOOL dialog_Beixing_shalun::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		set_draw();
		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
