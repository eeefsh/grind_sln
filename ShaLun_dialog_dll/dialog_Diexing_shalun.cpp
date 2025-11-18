// dialog_Diexing_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
#include "dialog_Diexing_shalun.h"


// dialog_Diexing_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_Diexing_shalun, CDialogEx)

dialog_Diexing_shalun::dialog_Diexing_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Diexing_shalun, pParent)
{

}

dialog_Diexing_shalun::~dialog_Diexing_shalun()
{
}

void dialog_Diexing_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_EDIT1, m_Zhijing);
	DDX_Control(pDX, IDC_EDIT2, m_Yuanjiao);
	DDX_Control(pDX, IDC_EDIT3, m_Jiaodu);
	DDX_Control(pDX, IDC_EDIT4, m_Kuandu);
	DDX_Control(pDX, IDC_RADIO1, m_Nei);
	DDX_Control(pDX, IDC_RADIO2, m_Wai);
	DDX_Control(pDX, IDC_CUSTOM1, m_draw);
}


BEGIN_MESSAGE_MAP(dialog_Diexing_shalun, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_Diexing_shalun::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT1, &dialog_Diexing_shalun::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &dialog_Diexing_shalun::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &dialog_Diexing_shalun::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &dialog_Diexing_shalun::OnEnKillfocusEdit4)
	ON_BN_CLICKED(IDC_RADIO1, &dialog_Diexing_shalun::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &dialog_Diexing_shalun::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT7, &dialog_Diexing_shalun::OnEnChangeEdit_name)
END_MESSAGE_MAP()


// dialog_Diexing_shalun 消息处理程序

BOOL dialog_Diexing_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_Diexing_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
		if (canshu.Chao_wai)
		{
			m_Nei.SetCheck(0);
			m_Wai.SetCheck(1);
		}
		else
		{
			m_Nei.SetCheck(1);
			m_Wai.SetCheck(0);
		}
	}
	else
	{
		m_Nei.SetCheck(1);
		m_Wai.SetCheck(0);
	}
	updata_show();
	set_draw();
}

void dialog_Diexing_shalun::updata_show()
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
}

void dialog_Diexing_shalun::get_canshu()
{
	CString temp;

	m_Zhijing.GetWindowTextW(temp);
	canshu.Zhijing_D = _tstof(temp);

	m_Yuanjiao.GetWindowTextW(temp);
	canshu.Yuanjiao_r = _tstof(temp);

	m_Kuandu.GetWindowTextW(temp);
	canshu.Kuandu = _tstof(temp);

	m_Jiaodu.GetWindowTextW(temp);
	canshu.Jiaodu = _tstof(temp);

	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	canshu.name = temp_str;

	if (m_Nei.GetCheck() == 1)
	{
		canshu.Chao_wai = 0;
	}
	else
	{
		canshu.Chao_wai = 1;
	}
}

void dialog_Diexing_shalun::save_canshu()
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

void dialog_Diexing_shalun::set_draw()
{
	get_canshu();

	updata_show();
	auto line1 = canshu.To_wheel_data();
	canshu.Jisuan_Yuanjiao(line1, 0, 0);
	auto line = wheel_output_namespace::wheel_outlines::wheel_Diexing_2D(line1);
	mat reflected = line;
	reflected.rows(1, 2) = -reflected.rows(1, 2);
	reflected = fliplr(reflected);
	line = join_horiz(line, reflected);
	m_draw.Set_wheel_outline(line);
}

void dialog_Diexing_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_Diexing_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_Diexing_shalun::OnBnClickedOk()
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
	m_Yuanjiao.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Kuandu.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("宽度不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	save_canshu();
	CDialogEx::OnOK();
}

void dialog_Diexing_shalun::OnEnKillfocusEdit1()
{
	set_draw();
}

void dialog_Diexing_shalun::OnEnKillfocusEdit2()
{
	set_draw();
}

void dialog_Diexing_shalun::OnEnKillfocusEdit3()
{
	set_draw();
}

void dialog_Diexing_shalun::OnEnKillfocusEdit4()
{
	set_draw();
}

void dialog_Diexing_shalun::OnBnClickedRadio1()
{
	set_draw();
}

void dialog_Diexing_shalun::OnBnClickedRadio2()
{
	set_draw();
}

void dialog_Diexing_shalun::OnEnChangeEdit_name()
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

BOOL dialog_Diexing_shalun::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		set_draw();
		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
