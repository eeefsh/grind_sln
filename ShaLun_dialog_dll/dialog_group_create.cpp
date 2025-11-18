// dialog_group_create.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_group_create.h"
#include "dialog_wheel_list.h"
#include "resource.h"


// dialog_group_create 对话框

IMPLEMENT_DYNAMIC(dialog_group_create, CDialogEx)

dialog_group_create::dialog_group_create(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_group_create, pParent)
{

}

dialog_group_create::~dialog_group_create()
{
}

void dialog_group_create::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_del);
	DDX_Control(pDX, IDC_RADIO1, m_cankao_nei);
	DDX_Control(pDX, IDC_RADIO3, m_cankao_wai);
	DDX_Control(pDX, IDC_EDIT5, m_falan);
	DDX_Control(pDX, IDC_BUTTON4, m_add_wheel);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_gan_D);
	DDX_Control(pDX, IDC_EDIT3, m_luomao_D);
	DDX_Control(pDX, IDC_EDIT4, m_luomao_L);
}

void dialog_group_create::set_list_init()
{
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, L"砂轮类型", LVCFMT_CENTER, 70);
	m_list.InsertColumn(1, L"砂轮名称", LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, L"法兰长度", LVCFMT_CENTER, 70);
	m_list.InsertColumn(3, L"参考位置", LVCFMT_CENTER, 70);
	
}

void dialog_group_create::set_Select_canshu(int nSelectedItem)
{
	int pos_temp = m_list.GetItemData(nSelectedItem);
	auto it = wheel_ptr->get_wheel_canshu(pos_temp);
	double dis = 0;
	bool cankao_flag = 0, one_cankao = 0;
	canshu.get_a_wheel_canshu(pos_temp, dis, cankao_flag, one_cankao);
	if (one_cankao)
	{
		m_cankao_nei.SetCheck(1);
		m_cankao_wai.SetCheck(0);
	}
	else
	{
		if (cankao_flag)
		{
			m_cankao_nei.SetCheck(0);
			m_cankao_wai.SetCheck(1);
		}
		else
		{
			m_cankao_nei.SetCheck(1);
			m_cankao_wai.SetCheck(0);
		}
	}
	CString strValue;
	strValue.Format(_T("%.3f"), dis);
	m_falan.SetWindowTextW(strValue);
}

void dialog_group_create::insert_a_list(int wheel_pos)
{
	using namespace wheel_namespace;	
	auto data = wheel_ptr->read_wheel(wheel_pos);
	if (data.key_group != -1)
	{
		MessageBox(_T("砂轮已经被安装，请选择其他砂轮!"), _T("提示"), MB_ICONWARNING);
		return;
	}

	bool one_cankao = 1;
	if (data.type_wheel == _Ping || data.type_wheel == _Yuanjiao || data.type_wheel == _Diexing)
	{
		one_cankao = 0;
	}

	if (canshu.add_wheel(wheel_pos, 0, 0, one_cankao))
	{
		MessageBox(_T("当前砂轮已经被选择，请选择其他砂轮!"), _T("提示"), MB_ICONWARNING);
		return;
	}
	
	auto it = wheel_ptr->get_group_creat_list_canshu(wheel_pos);
	int nIndex = m_list.GetItemCount();
	m_list.InsertItem(nIndex, CString(it.wheel_type.c_str()));
	m_list.SetItemText(nIndex, 1, CString(it.wheel_name.c_str()));
	m_list.SetItemText(nIndex, 2, CString(it.dis.c_str()));
	m_list.SetItemText(nIndex, 3, CString(it.cankao.c_str()));
	m_list.SetItemData(nIndex, wheel_pos);
	int n = sizeof(wheel_database_namespace::group_data::weizhi) / sizeof(wheel_database_namespace::group_data::weizhi[0]);
	if (canshu.size() >= n)
	{
		m_add_wheel.EnableWindow(0);
	}
	else
	{
		m_add_wheel.EnableWindow();
	}
	//add_wheel_show();
}

void dialog_group_create::No_Select(int nSelectedItem)
{
	
	// 确保有选中的项
	if (nSelectedItem != -1)
	{
		CString type_temp;
		type_temp = m_list.GetItemText(nSelectedItem, 0);
		if (type_temp == L"平砂轮" || type_temp == L"蝶形" || type_temp == L"圆角型")
		{
			m_cankao_nei.EnableWindow();
			m_cankao_wai.EnableWindow();
			set_Select_canshu(nSelectedItem);
		}
		else
		{
			m_cankao_nei.EnableWindow(0);
			m_cankao_wai.EnableWindow(0);
			set_Select_canshu(nSelectedItem);
		}
		m_falan.EnableWindow();
		m_del.EnableWindow();
		
	}
	else
	{
		m_cankao_nei.EnableWindow(0);
		m_cankao_wai.EnableWindow(0);
		m_falan.EnableWindow(0);
		m_del.EnableWindow(0);
		m_cankao_nei.SetCheck(0);
		m_cankao_wai.SetCheck(0);
		m_falan.SetWindowTextW(L"");
	}
}

void dialog_group_create::add_wheel_show()
{
	wheel_database_namespace::group_data temp;
	int n = sizeof(temp.weizhi) / sizeof(temp.weizhi[0]);
	if (group_id != -1)
	{
		temp = wheel_ptr->read_group(group_id);
		canshu.Init(temp);
	}
	if (canshu.size() >= n)
	{
		m_add_wheel.EnableWindow(0);
	}
	else
	{
		m_add_wheel.EnableWindow();
	}
}

void dialog_group_create::get_canshu_wheel(int nSelectedItem)
{
	int pos = m_list.GetItemData(nSelectedItem);
	CString temp;

	m_falan.GetWindowTextW(temp);
	double dis = _tstof(temp);
	if (m_cankao_nei.GetCheck() == 1)
	{
		canshu.edit_a_wheel(pos, dis, 0);
		if (canshu.get_one_cankao_flag(pos))
		{
			m_list.SetItemText(nSelectedItem, 3, L"--");
		}
		else
		{
			m_list.SetItemText(nSelectedItem, 3, L"内侧");
		}
		
	}
	else
	{
		canshu.edit_a_wheel(pos, dis, 1);
		if (canshu.get_one_cankao_flag(pos))
		{
			m_list.SetItemText(nSelectedItem, 3, L"--");
		}
		else
		{
			m_list.SetItemText(nSelectedItem, 3, L"外侧");
		}
	}
	
	temp.Format(_T("%.3f"), dis);
	m_list.SetItemText(nSelectedItem, 2, temp);
}

void dialog_group_create::open_Init()
{
	CString temp;
	if (group_id != -1)
	{
		temp.Format(_T("%.3f"), canshu.get_gan_D());
		m_gan_D.SetWindowTextW(temp);
		temp.Format(_T("%.3f"), canshu.get_luomao_D());
		m_luomao_D.SetWindowTextW(temp);
		temp.Format(_T("%.3f"), canshu.get_luomao_L());
		m_luomao_L.SetWindowTextW(temp);
		m_name.SetWindowTextW(CString(canshu.group_name.c_str()));
		for (size_t i = 0; i < canshu.size(); i++)
		{
			
			auto it = wheel_ptr->get_group_creat_list_canshu(canshu.wheel_buff[i].key_wheel);
			m_list.InsertItem(i, CString(it.wheel_type.c_str()));
			m_list.SetItemText(i, 1, CString(it.wheel_name.c_str()));
			m_list.SetItemText(i, 2, CString(it.dis.c_str()));
			m_list.SetItemText(i, 3, CString(it.cankao.c_str()));
			m_list.SetItemData(i, canshu.wheel_buff[i].key_wheel);
		}
	}
	else
	{
		temp.Format(_T("%.3f"), canshu.get_gan_D());
		m_gan_D.SetWindowTextW(temp);
		temp.Format(_T("%.3f"), canshu.get_luomao_D());
		m_luomao_D.SetWindowTextW(temp);
		temp.Format(_T("%.3f"), canshu.get_luomao_L());
		m_luomao_L.SetWindowTextW(temp);
		/*m_gan_D.SetWindowTextW(L"0.000");
		
		m_luomao_D.SetWindowTextW(L"0.000");
		
		m_luomao_L.SetWindowTextW(L"0.000");*/
	}
}

void dialog_group_create::save_data()
{
	CString str_val;
	m_name.GetWindowTextW(str_val);
	CT2CA temp_str(str_val);

	m_gan_D.GetWindowTextW(str_val);
	double gan_D = _tstof(str_val);
	m_luomao_D.GetWindowTextW(str_val);
	double luomao_D = _tstof(str_val);
	m_luomao_L.GetWindowTextW(str_val);
	double luomao_L = _tstof(str_val);

	
	if (group_id != -1)
	{
		auto it = canshu.To_group_data(std::string(temp_str), gan_D, luomao_D, luomao_L, wheel_ptr->read_group(group_id));
		wheel_ptr->edit_group(it.key_group, it);
	}
	else
	{
		auto it = canshu.To_group_data(std::string(temp_str), gan_D, luomao_D, luomao_L);
		wheel_ptr->add_group(it);
	}
	
}

void dialog_group_create::is_open_group(int pos)
{
	group_id = pos;
}

void dialog_group_create::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}


BEGIN_MESSAGE_MAP(dialog_group_create, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &dialog_group_create::OnBnClickedButton_anzhuang)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &dialog_group_create::OnNMClickList1)
	ON_BN_CLICKED(IDC_RADIO1, &dialog_group_create::OnBnClickedRadio_cankao_nei)
	ON_BN_CLICKED(IDC_RADIO3, &dialog_group_create::OnBnClickedRadio_cankao_wai)
	ON_EN_KILLFOCUS(IDC_EDIT5, &dialog_group_create::OnEnKillfocusEdit_falan)
	ON_BN_CLICKED(IDOK, &dialog_group_create::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &dialog_group_create::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &dialog_group_create::OnEnChangeEdit_name)
END_MESSAGE_MAP()


// dialog_group_create 消息处理程序

BOOL dialog_group_create::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	set_list_init();
	add_wheel_show();
	open_Init();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_group_create::OnBnClickedButton_anzhuang()
{
	dialog_wheel_list* wheel_list = new dialog_wheel_list;
	wheel_list->input_wheel_ptr(wheel_ptr);
	wheel_list->is_anzhuang();
	if (wheel_list->DoModal() == IDOK)
	{
		insert_a_list(wheel_list->get_anzhuang_pos());
	}
	delete wheel_list;
}

void dialog_group_create::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nSelectedItem = m_list.GetNextItem(-1, LVNI_SELECTED);
	temp_row = nSelectedItem;
	No_Select(nSelectedItem);
	*pResult = 0;
}

void dialog_group_create::OnBnClickedRadio_cankao_nei()
{
	get_canshu_wheel(temp_row);
}

void dialog_group_create::OnBnClickedRadio_cankao_wai()
{
	get_canshu_wheel(temp_row);
}

void dialog_group_create::OnEnKillfocusEdit_falan()
{
	get_canshu_wheel(temp_row);
}

void dialog_group_create::OnBnClickedOk()
{
	if (m_name.GetWindowTextLengthW() == 0)
	{
		MessageBox(_T("请设置名称"), _T("提示"), MB_ICONWARNING);
		return;
	}

	save_data();
	CDialogEx::OnOK();
}

void dialog_group_create::OnBnClickedButton1()
{
	int nSelectedItem = m_list.GetNextItem(-1, LVNI_SELECTED);
	canshu.del_wheel(m_list.GetItemData(nSelectedItem));
	m_list.DeleteItem(nSelectedItem);
	No_Select(-1);
}

BOOL dialog_group_create::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd* pFocusWnd = GetFocus();

		if (pFocusWnd == &m_falan)  // m_edit1 是 CEdit 类型的控件变量 
		{
			get_canshu_wheel(temp_row);
		}

		return TRUE; // 拦截 Enter 键，防止默认行为 
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void dialog_group_create::OnEnChangeEdit_name()
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
