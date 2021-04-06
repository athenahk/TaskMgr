// CExportDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CExportDlg.h"
#include "afxdialogex.h"
#include"Func.h"


// CExportDlg 对话框

IMPLEMENT_DYNAMIC(CExportDlg, CDialogEx)

CExportDlg::CExportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent)
{

}

CExportDlg::CExportDlg(CPe* pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_EXPORT, pParent)
{
	m_Pe = pe;
}
CExportDlg::~CExportDlg()
{
}

void CExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EXPORT, m_ListCtrlExport);
}


BEGIN_MESSAGE_MAP(CExportDlg, CDialogEx)
END_MESSAGE_MAP()

void CExportDlg::InitExport()
{
	ExportInfo temp = m_Pe->GetExportInfo();
	CWnd* pWnd = 0;
	CString szString;
	for (int i = 0; i < 6; i++)
	{
		pWnd = GetDlgItem(IDC_EDIT70 + i);
		szString.Format(L"0x%08X", *((PDWORD)(&temp) + i));
		pWnd->SetWindowTextW(szString);
	}
}

void CExportDlg::InitListCtrl()
{
	st st1 = { 0 };
	st1 = AnalysisExport(m_Pe->m_pBuf);
	for (int i = 0; i < st1.count1; i++) {
		CString str;
		str.Format(L"%d", st1.p1[i].Ordinal);
		m_ListCtrlExport.InsertItem(i, str);

		str.Format(L"0x%08X", st1.p1[i].Rva);
		m_ListCtrlExport.SetItemText(i, 1, str);

		str.Format(L"0x%08x", st1.p1[i].Foa);
		m_ListCtrlExport.SetItemText(i, 2, str);

		str = st1.p1[i].szString;
		m_ListCtrlExport.SetItemText(i, 3, str);
	}
	delete[] st1.p1;
}

// CExportDlg 消息处理程序


BOOL CExportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitExport();
	m_ListCtrlExport.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlExport.InsertColumn(1, L"Ordinal", LVCFMT_CENTER, 100);
	m_ListCtrlExport.InsertColumn(2, L"RVA", LVCFMT_CENTER, 100);
	m_ListCtrlExport.InsertColumn(3, L"Offset", LVCFMT_CENTER, 100);
	m_ListCtrlExport.InsertColumn(4, L"Function Name", LVCFMT_CENTER, 400);
	InitListCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
