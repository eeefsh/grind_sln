// dialog_group_list.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "dialog_group_list.h"
#include "dialog_group_create.h"
#include "resource.h"


// dialog_group_list 对话框

IMPLEMENT_DYNAMIC(dialog_group_list, CDialogEx)

dialog_group_list::dialog_group_list(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_group_list, pParent)
{

}

dialog_group_list::~dialog_group_list()
{
}

void dialog_group_list::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_group_list);
	DDX_Control(pDX, IDC_BUTTON2, m_open);
	DDX_Control(pDX, IDC_BUTTON3, m_del);
	DDX_Control(pDX, IDOK, m_ok);
}


BEGIN_MESSAGE_MAP(dialog_group_list, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &dialog_group_list::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &dialog_group_list::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &dialog_group_list::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON3, &dialog_group_list::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &dialog_group_list::OnBnClickedOk)
END_MESSAGE_MAP()

void dialog_group_list::set_list_init()
{
	m_group_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_group_list.InsertColumn(0, L"砂轮组名称", LVCFMT_CENTER, 100);
	m_group_list.InsertColumn(1, L"砂轮数量", LVCFMT_CENTER, 70);
	m_group_list.InsertColumn(2, L"修改时间", LVCFMT_CENTER, 150);
	CString temp;
	int i = 0;
	for (auto iter = wheel_ptr->list_group_all.begin(); iter != wheel_ptr->list_group_all.end(); ++iter)
	{
		auto it = wheel_ptr->get_group_canshu(iter->pos);
		temp = it.group_name.c_str();
		int nItem = m_group_list.InsertItem(i++, temp);
		temp = it.n_wheel.c_str();
		m_group_list.SetItemText(nItem, 1, temp);
		temp = it.time_new.c_str();
		m_group_list.SetItemText(nItem, 2, temp);
		m_group_list.SetItemData(nItem, iter->pos);
	}
}

void dialog_group_list::update_list(int num)
{
	wheel_dialog_namespace::group_list_data data;
	CString temp;
	if (num != -1)
	{
		data = wheel_ptr->get_group_canshu(m_group_list.GetItemData(num));
		temp = data.group_name.c_str();
		m_group_list.SetItemText(num, 0, temp);
		temp = data.n_wheel.c_str();
		m_group_list.SetItemText(num, 1, temp);
		temp = data.time_new.c_str();
		m_group_list.SetItemText(num, 2, temp);
	}
	else
	{
		data = wheel_ptr->get_group_canshu((wheel_ptr->list_group_all.begin())->pos);
		temp = data.group_name.c_str();
		int nItem = m_group_list.InsertItem(0, temp);
		temp = data.n_wheel.c_str();
		m_group_list.SetItemText(nItem, 1, temp);
		temp = data.time_new.c_str();
		m_group_list.SetItemText(nItem, 2, temp);
		m_group_list.SetItemData(nItem, (wheel_ptr->list_group_all.begin())->pos);
	}
}

void dialog_group_list::No_Select(int nSelectedItem)
{
	// 确保有选中的项
	if (nSelectedItem != -1)
	{
		m_open.EnableWindow();
		m_del.EnableWindow();

		if (is_xuanzhe_flag)
		{
			m_ok.EnableWindow();
		}
	}
	else
	{
		m_open.EnableWindow(0);
		m_del.EnableWindow(0);
		m_ok.EnableWindow(0);
	}
}

void dialog_group_list::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_group_list::OnBnClickedButton1()
{
	dialog_group_create* group_create = new dialog_group_create;
	group_create->input_wheel_ptr(wheel_ptr);
	if (group_create->DoModal() == IDOK)
	{
		update_list();
	}
	delete group_create;
}

BOOL dialog_group_list::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	set_list_init();
	if (is_xuanzhe_flag)
	{
		m_ok.ShowWindow(SW_SHOW);
		m_ok.EnableWindow(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_group_list::is_Xuanzhe()
{
	is_xuanzhe_flag = 1;
}

int dialog_group_list::get_Xuanzhe_pos()
{
	return group_pos;
}

void dialog_group_list::OnBnClickedButton2()
{
	int nSelectedItem = m_group_list.GetNextItem(-1, LVNI_SELECTED);
	int pos = m_group_list.GetItemData(nSelectedItem);
	dialog_group_create* group_create = new dialog_group_create;
	group_create->is_open_group(pos);
	group_create->input_wheel_ptr(wheel_ptr);
	if (group_create->DoModal() == IDOK)
	{
		update_list(nSelectedItem);
	}

	delete group_create;
	No_Select(-1);

}

void dialog_group_list::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nSelectedItem = m_group_list.GetNextItem(-1, LVNI_SELECTED);
	No_Select(nSelectedItem);
	*pResult = 0;
}

void dialog_group_list::OnBnClickedButton3()
{
	int nSelectedItem = m_group_list.GetNextItem(-1, LVNI_SELECTED);
	int nResult = MessageBox(_T("确定要删除此砂轮组吗"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING);
	if (nResult == IDOK)
	{
		wheel_ptr->delete_group(m_group_list.GetItemData(nSelectedItem));
		m_group_list.DeleteItem(nSelectedItem);
		No_Select(-1);
	}
}


void dialog_group_list::OnBnClickedOk()
{
	int nSelectedItem = m_group_list.GetNextItem(-1, LVNI_SELECTED);
	group_pos = m_group_list.GetItemData(nSelectedItem);

	CDialogEx::OnOK();
}
