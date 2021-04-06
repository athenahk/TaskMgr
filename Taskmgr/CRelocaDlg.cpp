// CRelocaDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CRelocaDlg.h"
#include "afxdialogex.h"
#include "Func.h"


// CRelocaDlg 对话框

IMPLEMENT_DYNAMIC(CRelocaDlg, CDialogEx)

CRelocaDlg::CRelocaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RELOCATION, pParent)
{

}

CRelocaDlg::CRelocaDlg(CPe* pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_RELOCATION, pParent)
{
	m_Pe = pe;
}
CRelocaDlg::~CRelocaDlg()
{
}

void CRelocaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RELOCA1, m_ListCtrlReloca1);
	DDX_Control(pDX, IDC_LIST_RELOCA2, m_ListCtrlReloca2);
}


BEGIN_MESSAGE_MAP(CRelocaDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RELOCA1, &CRelocaDlg::OnNMClickListReloca1)
END_MESSAGE_MAP()


// CRelocaDlg 消息处理程序


BOOL CRelocaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ListCtrlReloca1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlReloca1.InsertColumn(1, L"Index", LVCFMT_CENTER, 50);
	m_ListCtrlReloca1.InsertColumn(2, L"Section", LVCFMT_CENTER, 100);
	m_ListCtrlReloca1.InsertColumn(3, L"Rva", LVCFMT_CENTER, 100);
	m_ListCtrlReloca1.InsertColumn(4, L"项目", LVCFMT_CENTER, 100);
	

	m_ListCtrlReloca2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlReloca2.InsertColumn(1, L"Index", LVCFMT_CENTER, 50);
	m_ListCtrlReloca2.InsertColumn(2, L"Rva", LVCFMT_CENTER, 100);
	m_ListCtrlReloca2.InsertColumn(3, L"Offset", LVCFMT_CENTER, 100);
	m_ListCtrlReloca2.InsertColumn(4, L"类型", LVCFMT_CENTER, 100);
	m_ListCtrlReloca2.InsertColumn(5, L"FAR 地址", LVCFMT_CENTER, 100);
	m_ListCtrlReloca2.InsertColumn(6, L"数据", LVCFMT_CENTER, 200);
	// TODO:  在此添加额外的初始化
	AnalyzeBaseReloc(m_Pe->m_pBuf, m_vecRelocaInfo, m_vecRelocaInfo2);
	InitReloca();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CRelocaDlg::InitReloca()
{
	CString str;
	for (int i = 0; i < m_vecRelocaInfo.size(); i++)
	{
		str.Format(L"%d", i + 1);
		m_ListCtrlReloca1.InsertItem(i, str);

		str = m_vecRelocaInfo[i].Section;
		m_ListCtrlReloca1.SetItemText(i, 1, str);

		str.Format(L"0x%08X", m_vecRelocaInfo[i].Rva);
		m_ListCtrlReloca1.SetItemText(i, 2, str);

		str = m_vecRelocaInfo[i].Count;
		m_ListCtrlReloca1.SetItemText(i, 3, str);


	}
}

void CRelocaDlg::OnNMClickListReloca1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwIndex = m_ListCtrlReloca1.GetSelectionMark();
	CString str;
	m_ListCtrlReloca2.DeleteAllItems();
	for (int i = 0; i < m_vecRelocaInfo2[dwIndex].size(); i++)
	{
		str.Format(L"%d", i+ 1);
		m_ListCtrlReloca2.InsertItem(i, str);

		str.Format(L"0x%08X", m_vecRelocaInfo2[dwIndex][i].Rva);
		m_ListCtrlReloca2.SetItemText(i, 1, str);

		str.Format(L"0x%08X", m_vecRelocaInfo2[dwIndex][i].Offset);
		m_ListCtrlReloca2.SetItemText(i, 2, str);

		str = "HIGHLOW (3)";
		m_ListCtrlReloca2.SetItemText(i, 3, str);

		str.Format(L"0x%08X", m_vecRelocaInfo2[dwIndex][i].Va);
		m_ListCtrlReloca2.SetItemText(i, 4, str);

		str.Format(L"%X", m_vecRelocaInfo2[dwIndex][i].Data);
		m_ListCtrlReloca2.SetItemText(i, 5, str);
	}
	*pResult = 0;
}
