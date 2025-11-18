// dialog_wheel_list.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "resource.h"
#include "dialog_wheel_list.h"
#include "dialog_wheel_create.h"
#include "dialog_Ping_shalun.h"
#include "dialog_Beixing_shalun.h"
#include "dialog_Diexing_shalun.h"
#include "dialog_Yuanjiao_shalun.h"
#include "dialog_DXF_shalun.h"
#include "dialog_Jianjiao_shalun.h"


// dialog_wheel_list 对话框

IMPLEMENT_DYNAMIC(dialog_wheel_list, CDialogEx)

dialog_wheel_list::dialog_wheel_list(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_wheel_list, pParent)
{

}

dialog_wheel_list::~dialog_wheel_list()
{
}

void dialog_wheel_list::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_wheel_LIST, m_wheel_list);
	DDX_Control(pDX, IDC_BUTTON_create_wheel2, m_open);
	DDX_Control(pDX, IDC_BUTTON_create_wheel3, m_del);
	DDX_Control(pDX, IDOK, m_ok);
}


BEGIN_MESSAGE_MAP(dialog_wheel_list, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_create_wheel, &dialog_wheel_list::OnBnClickedButton_create_wheel)
	ON_BN_CLICKED(IDC_BUTTON_create_wheel3, &dialog_wheel_list::OnBnClickedButtoncreatewheel3)
	ON_NOTIFY(NM_CLICK, IDC_wheel_LIST, &dialog_wheel_list::OnNMClickwheelList)
	ON_BN_CLICKED(IDC_BUTTON_create_wheel2, &dialog_wheel_list::OnBnClickedButtoncreatewheel2)
	ON_BN_CLICKED(IDOK, &dialog_wheel_list::OnBnClickedOk)
END_MESSAGE_MAP()


// dialog_wheel_list 消息处理程序

void dialog_wheel_list::set_list_init()
{
	m_wheel_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wheel_list.InsertColumn(0, L"类型", LVCFMT_CENTER, 50);
	m_wheel_list.InsertColumn(1, L"砂轮名称", LVCFMT_CENTER, 100);
	m_wheel_list.InsertColumn(2, L"砂轮组名称", LVCFMT_CENTER, 100);
	m_wheel_list.InsertColumn(3, L"法兰长度", LVCFMT_CENTER, 70);
	m_wheel_list.InsertColumn(4, L"直径", LVCFMT_CENTER, 70);
	m_wheel_list.InsertColumn(5, L"角度", LVCFMT_CENTER, 70);
	m_wheel_list.InsertColumn(6, L"圆角1", LVCFMT_CENTER, 70);
	m_wheel_list.InsertColumn(7, L"圆角2", LVCFMT_CENTER, 70);
	m_wheel_list.InsertColumn(8, L"修改时间", LVCFMT_CENTER, 150);
	CString temp;
	int i = 0;
	for (auto iter = wheel_ptr->list_wheel_all.begin(); iter != wheel_ptr->list_wheel_all.end(); ++iter)
	{
		auto it = wheel_ptr->get_wheel_canshu(iter->pos);

		temp = it.type.c_str();
		int nItem = m_wheel_list.InsertItem(i++, temp);
		temp = it.wheel_name.c_str();
		m_wheel_list.SetItemText(nItem, 1, temp);
		temp = it.group_name.c_str();
		m_wheel_list.SetItemText(nItem, 2, temp);
		temp = it.falan.c_str();
		m_wheel_list.SetItemText(nItem, 3, temp);
		temp = it.Zhijin_D.c_str();
		m_wheel_list.SetItemText(nItem, 4, temp);
		temp = it.Jiaodu.c_str();
		m_wheel_list.SetItemText(nItem, 5, temp);
		temp = it.Yuanjiao_1.c_str();
		m_wheel_list.SetItemText(nItem, 6, temp);
		temp = it.Yuanjiao_2.c_str();
		m_wheel_list.SetItemText(nItem, 7, temp);
		temp = it.time_new.c_str();
		m_wheel_list.SetItemText(nItem, 8, temp);

		m_wheel_list.SetItemData(nItem, it.pos);
	}
}

void dialog_wheel_list::update_list(bool is_edit)
{
	wheel_dialog_namespace::wheel_list_data it;
	

	if (is_edit)
	{
		int nSelectedItem = m_wheel_list.GetNextItem(-1, LVNI_SELECTED);
		it = wheel_ptr->get_wheel_canshu(m_wheel_list.GetItemData(nSelectedItem));
		m_wheel_list.DeleteItem(nSelectedItem);
	}
	else
	{
		it = wheel_ptr->get_wheel_canshu((wheel_ptr->list_wheel_all.begin())->pos);
	}
	CString temp;

	temp = it.type.c_str();
	int nItem = m_wheel_list.InsertItem(0, temp);
	temp = it.wheel_name.c_str();
	m_wheel_list.SetItemText(nItem, 1, temp);
	temp = it.group_name.c_str();
	m_wheel_list.SetItemText(nItem, 2, temp);
	temp = it.falan.c_str();
	m_wheel_list.SetItemText(nItem, 3, temp);
	temp = it.Zhijin_D.c_str();
	m_wheel_list.SetItemText(nItem, 4, temp);
	temp = it.Jiaodu.c_str();
	m_wheel_list.SetItemText(nItem, 5, temp);
	temp = it.Yuanjiao_1.c_str();
	m_wheel_list.SetItemText(nItem, 6, temp);
	temp = it.Yuanjiao_2.c_str();
	m_wheel_list.SetItemText(nItem, 7, temp);
	temp = it.time_new.c_str();
	m_wheel_list.SetItemText(nItem, 8, temp);

	m_wheel_list.SetItemData(nItem, it.pos);
}

void dialog_wheel_list::open_wheel_edit(int data_pos)
{
	using namespace wheel_namespace;
	auto data = wheel_ptr->read_wheel(data_pos);
	switch (data.type_wheel)
	{
	case _Ping: 
	{
		dialog_Ping_shalun* Ping_shalun = new dialog_Ping_shalun;
		Ping_shalun->input_wheel_ptr(wheel_ptr);
		Ping_shalun->input_wheel_pos(data.key_wheel);
		if (Ping_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete Ping_shalun;
	}break;
	case _Beixing:
	{
		dialog_Beixing_shalun* Beixing_shalun = new dialog_Beixing_shalun;
		Beixing_shalun->input_wheel_ptr(wheel_ptr);
		Beixing_shalun->input_wheel_pos(data.key_wheel);
		if (Beixing_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete Beixing_shalun;
	}break;
	case _Yuanjiao:
	{
		dialog_Yuanjiao_shalun* Yuanjiao_shalun = new dialog_Yuanjiao_shalun;
		Yuanjiao_shalun->input_wheel_ptr(wheel_ptr);
		Yuanjiao_shalun->input_wheel_pos(data.key_wheel);
		if (Yuanjiao_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete Yuanjiao_shalun;
	}break;
	case _Diexing:
	{
		dialog_Diexing_shalun* Diexing_shalun = new dialog_Diexing_shalun;
		Diexing_shalun->input_wheel_ptr(wheel_ptr);
		Diexing_shalun->input_wheel_pos(data.key_wheel);
		if (Diexing_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete Diexing_shalun;
	}break;
	case _DXF:
	{
		dialog_DXF_shalun* DXF_shalun = new dialog_DXF_shalun;
		DXF_shalun->input_wheel_ptr(wheel_ptr);
		DXF_shalun->input_wheel_pos(data.key_wheel);
		if (DXF_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete DXF_shalun;
	}break;
	case _Jianjiao:
	{
		dialog_Jianjiao_shalun* Jianjiao_shalun = new dialog_Jianjiao_shalun;
		Jianjiao_shalun->input_wheel_ptr(wheel_ptr);
		Jianjiao_shalun->input_wheel_pos(data.key_wheel);
		if (Jianjiao_shalun->DoModal() == IDOK)
		{
			update_list(1);
		}
		m_wheel_list.SetItemState(-1, 0, LVIS_SELECTED);
		No_Select(-1);
		delete Jianjiao_shalun;
	}break;
	default:
		break;
	}
}

void dialog_wheel_list::is_anzhuang()
{
	anzhuang_flag = 1;
}

void dialog_wheel_list::is_xuanzhe()
{
	anzhuang_flag = 1;
}

int dialog_wheel_list::get_anzhuang_pos()
{
	return anzhuang_pos;
}

int dialog_wheel_list::get_xuanzhe_pos()
{
	return anzhuang_pos;
}

void dialog_wheel_list::input_wheel_ptr(wheel_dialog* _ptr)
{
	wheel_ptr = _ptr;
}

void dialog_wheel_list::OnBnClickedButton_create_wheel()
{
	dialog_wheel_create* wheel_create = new dialog_wheel_create;
	wheel_create->input_wheel_ptr(wheel_ptr);
	if (wheel_create->DoModal() == IDOK)
	{
		update_list();
	}
	No_Select(-1);
	delete wheel_create;
}

BOOL dialog_wheel_list::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	set_list_init();
	if (anzhuang_flag)
	{
		m_ok.ShowWindow(1);
	}
	else
	{
		m_ok.ShowWindow(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void dialog_wheel_list::OnBnClickedButtoncreatewheel3()
{
	int nSelectedItem = m_wheel_list.GetNextItem(-1, LVNI_SELECTED);
	int pos = m_wheel_list.GetItemData(nSelectedItem);
	if (wheel_ptr->read_wheel(pos).key_group != -1)
	{
		MessageBox(_T("砂轮已经被安装!"), _T("提示"), MB_ICONWARNING);
		No_Select(-1);
		return;
	}
	int nResult = MessageBox(_T("确定要删除此砂轮吗"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING);
	if (nResult == IDOK)
	{
		wheel_ptr->delete_wheel(pos);
		m_wheel_list.DeleteItem(nSelectedItem);
		No_Select(-1);
	}
}

void dialog_wheel_list::OnNMClickwheelList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nSelectedItem = m_wheel_list.GetNextItem(-1, LVNI_SELECTED);

	No_Select(nSelectedItem);
	*pResult = 0;
}

void dialog_wheel_list::No_Select(int nSelectedItem)
{
	// 确保有选中的项
	if (nSelectedItem != -1)
	{
		m_open.EnableWindow();
		m_del.EnableWindow();
		m_ok.EnableWindow();
		
		
	}
	else
	{
		m_open.EnableWindow(0);
		m_del.EnableWindow(0);
		m_ok.EnableWindow(0);
	}
}

void dialog_wheel_list::OnBnClickedButtoncreatewheel2()
{
	int nSelectedItem = m_wheel_list.GetNextItem(-1, LVNI_SELECTED);
	open_wheel_edit(m_wheel_list.GetItemData(nSelectedItem));
	
}


BOOL dialog_wheel_list::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void dialog_wheel_list::OnBnClickedOk()
{
	int nSelectedItem = m_wheel_list.GetNextItem(-1, LVNI_SELECTED);
	anzhuang_pos = m_wheel_list.GetItemData(nSelectedItem);
	CDialogEx::OnOK();
}
