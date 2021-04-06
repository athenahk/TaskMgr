// CImportDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CImportDlg.h"
#include "afxdialogex.h"


// CImportDlg 对话框

IMPLEMENT_DYNAMIC(CImportDlg, CDialogEx)

CImportDlg::CImportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_IMPORT, pParent)
{

}

CImportDlg::CImportDlg(CPe* Pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_IMPORT, pParent)
{
	m_Pe = Pe;
}

CImportDlg::~CImportDlg()
{
}

void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMPORT1, m_ListCtrlImport1);
	DDX_Control(pDX, IDC_LIST_IMPORT2, m_ListCtrlImport2);
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMPORT1, &CImportDlg::OnNMClickListImport1)
END_MESSAGE_MAP()


// CImportDlg 消息处理程序


BOOL CImportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlImport1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlImport1.InsertColumn(1, L"DllName", LVCFMT_CENTER, 100);
	m_ListCtrlImport1.InsertColumn(2, L"OriginalFirstThunk", LVCFMT_CENTER, 100);
	m_ListCtrlImport1.InsertColumn(3, L"TimeDataStamp", LVCFMT_CENTER, 100);
	m_ListCtrlImport1.InsertColumn(4, L"ForwarderChain", LVCFMT_CENTER, 100);
	m_ListCtrlImport1.InsertColumn(5, L"Name Rva", LVCFMT_CENTER, 100);
	m_ListCtrlImport1.InsertColumn(6, L"FirstThunk", LVCFMT_CENTER, 100);

	m_ListCtrlImport2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlImport2.InsertColumn(1, L"ThunkRva", LVCFMT_CENTER, 100);
	m_ListCtrlImport2.InsertColumn(2, L"ThunkOffset", LVCFMT_CENTER, 100);
	m_ListCtrlImport2.InsertColumn(3, L"ThunkValue", LVCFMT_CENTER, 100);
	m_ListCtrlImport2.InsertColumn(4, L"Hint", LVCFMT_CENTER, 100);
	m_ListCtrlImport2.InsertColumn(5, L"AppName", LVCFMT_CENTER, 100);
	AnalysisImportTable(m_Pe->m_pBuf, vecInfo1, vecInfo2);
	InitImport1();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CImportDlg::OnNMClickListImport1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwIndex = m_ListCtrlImport1.GetSelectionMark();
	CString str;
	m_ListCtrlImport2.DeleteAllItems();
	for (int i = 0; i < vecInfo2[dwIndex].size(); i++)
	{
		str.Format(L"0x%08x", vecInfo2[dwIndex][i].ThunkRva);
		m_ListCtrlImport2.InsertItem(i, str);

		str.Format(L"0x%08X", vecInfo2[dwIndex][i].ThunkOffset);
		m_ListCtrlImport2.SetItemText(i, 1, str);

		str.Format(L"0x%08X", vecInfo2[dwIndex][i].ThunkValue);
		m_ListCtrlImport2.SetItemText(i, 2, str);

		str.Format(L"0x%08X", vecInfo2[dwIndex][i].Hint);
		m_ListCtrlImport2.SetItemText(i, 3, str);

		str = vecInfo2[dwIndex][i].FuncName;
		m_ListCtrlImport2.SetItemText(i, 4, str);

	}

	*pResult = 0;
}

void CImportDlg::InitImport1()
{
	CString str;
	for (int i = 0; i < vecInfo1.size(); i++)
	{
		str = vecInfo1[i].DllName;
		m_ListCtrlImport1.InsertItem(i, str);

		str.Format(L"0x%08X", vecInfo1[i].OriginalFirstThunk);
		m_ListCtrlImport1.SetItemText(i, 1, str);

		str.Format(L"0x%08X", vecInfo1[i].TimeDataStamp);
		m_ListCtrlImport1.SetItemText(i, 2, str);

		str.Format(L"0x%08X", vecInfo1[i].ForwarderChain);
		m_ListCtrlImport1.SetItemText(i, 3, str);

		str.Format(L"0x%08X", vecInfo1[i].Rva);
		m_ListCtrlImport1.SetItemText(i, 4, str);

		str.Format(L"0x%08X", vecInfo1[i].FirstThunk);
		m_ListCtrlImport1.SetItemText(i, 5, str);
	}
}
