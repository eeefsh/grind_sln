// dialog_Yuanjiao_shalun.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_Yuanjiao_shalun.h"
#include "resource.h"

// dialog_Yuanjiao_shalun 对话框

IMPLEMENT_DYNAMIC(dialog_Yuanjiao_shalun, CDialogEx)

dialog_Yuanjiao_shalun::dialog_Yuanjiao_shalun(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Yuanjiao_shalun, pParent)
{

}

dialog_Yuanjiao_shalun::~dialog_Yuanjiao_shalun()
{
}

void dialog_Yuanjiao_shalun::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_EDIT9, m_Zhijing);
	DDX_Control(pDX, IDC_EDIT10, m_Yuanjiao);
	DDX_Control(pDX, IDC_CUSTOM1, m_draw);
}


BEGIN_MESSAGE_MAP(dialog_Yuanjiao_shalun, CDialogEx)
	ON_BN_CLICKED(IDOK, &dialog_Yuanjiao_shalun::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT9, &dialog_Yuanjiao_shalun::OnEnKillfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT10, &dialog_Yuanjiao_shalun::OnEnKillfocusEdit10)
	ON_EN_CHANGE(IDC_EDIT7, &dialog_Yuanjiao_shalun::OnEnChangeEdit_name)
END_MESSAGE_MAP()


// dialog_Yuanjiao_shalun 消息处理程序

BOOL dialog_Yuanjiao_shalun::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	init_canshu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_Yuanjiao_shalun::init_canshu()
{
	CString strValue;
	if (is_open)
	{
		canshu.To_dialog_data(wheel_ptr->read_wheel(buff_wheel_pos));
		strValue = canshu.name.c_str();
		m_name.SetWindowTextW(strValue);
	}
	updata_show();
	set_draw();
}

void dialog_Yuanjiao_shalun::updata_show()
{
	CString strValue;

	strValue.Format(_T("%.3f"), canshu.Zhijing_D);
	m_Zhijing.SetWindowTextW(strValue);
	strValue.Format(_T("%.3f"), canshu.Yuanjiao_r);
	m_Yuanjiao.SetWindowTextW(strValue);
}

void dialog_Yuanjiao_shalun::get_canshu()
{
	CString temp;

	m_Zhijing.GetWindowTextW(temp);
	canshu.Zhijing_D = _tstof(temp);

	m_Yuanjiao.GetWindowTextW(temp);
	canshu.Yuanjiao_r = _tstof(temp);

	m_name.GetWindowTextW(temp);
	CT2CA temp_str(temp);
	canshu.name = temp_str;

}

void dialog_Yuanjiao_shalun::save_canshu()
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

void dialog_Yuanjiao_shalun::set_draw()
{
	get_canshu();
	updata_show();
	auto line1 = canshu.To_wheel_data();
	canshu.Jisuan_Yuanjiao(line1, 0, 0);
	auto line = wheel_output_namespace::wheel_outlines::wheel_Yuanjiao_2D(line1);
	mat reflected = line;
	reflected.rows(1, 2) = -reflected.rows(1, 2);
	reflected = fliplr(reflected);
	line = join_horiz(line, reflected);
	m_draw.Set_wheel_outline(line);
}

void dialog_Yuanjiao_shalun::input_wheel_pos(int pos)
{
	buff_wheel_pos = pos;
	is_open = 1;
}

void dialog_Yuanjiao_shalun::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_Yuanjiao_shalun::OnBnClickedOk()
{
	if (m_name.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("请设置名称"), _T("提示"), MB_ICONWARNING);
		return;
	}

	CString temp;
	m_Yuanjiao.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("圆角不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	m_Zhijing.GetWindowTextW(temp);
	if (_tstof(temp) <= 0)
	{
		MessageBox(_T("直径不能<=0"), _T("提示"), MB_ICONWARNING);
		return;
	}
	save_canshu();
	CDialogEx::OnOK();
}

void dialog_Yuanjiao_shalun::OnEnKillfocusEdit9()
{
	set_draw();
}

void dialog_Yuanjiao_shalun::OnEnKillfocusEdit10()
{
	set_draw();
}

void dialog_Yuanjiao_shalun::OnEnChangeEdit_name()
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

BOOL dialog_Yuanjiao_shalun::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		set_draw();
		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
