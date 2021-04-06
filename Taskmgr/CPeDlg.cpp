// CPeDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CPeDlg.h"
#include "Resource.h"
#include "afxdialogex.h"


// CPeDlg 对话框

IMPLEMENT_DYNAMIC(CPeDlg, CDialogEx)

CPeDlg::CPeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PE, pParent)
{

}

CPeDlg::~CPeDlg()
{
}

void CPeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON10, m_Section);
	DDX_Control(pDX, IDC_BUTTON11, m_DataDir);
	DDX_Control(pDX, IDC_BUTTON12, m_Calc);
	DDX_Control(pDX, IDC_BUTTON13, m_Time);
}


BEGIN_MESSAGE_MAP(CPeDlg, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON10, &CPeDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CPeDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CPeDlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// CPeDlg 消息处理程序
void CPeDlg::ShowFileHeader()
{
	PFileHeaderInfo pFileHeaderInfo = m_Pe.GetFileHeaderInfo();
	CWnd* pWnd = 0;
	for (DWORD i = 0; i < 8; i++)
	{
		CString str;
		pWnd = GetDlgItem(IDC_EDIT1 + i);
		str.Format(_T("0x%08X"), *((DWORD*)pFileHeaderInfo + i));
		pWnd->SetWindowText(str);
	}
}

void CPeDlg::ShowOpHeader()
{
	pOpHeaderInfo pOptionalHeaderInfo = m_Pe.GetOpHeaderInfo();
	CWnd* pWnd = 0;
	for (int i = 0; i < 16; i++)
	{
		CString str;
		pWnd = GetDlgItem(IDC_EDIT9 + i);
		str.Format(_T("0x%08X"), *((DWORD*)pOptionalHeaderInfo + i));
		pWnd->SetWindowText(str);
	}
}

void CPeDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TCHAR szFilePath[MAX_PATH] = { 0 };
	DWORD dwFileCount = DragQueryFile(hDropInfo, 0, szFilePath, MAX_PATH);

	m_Pe.SetFilePath(szFilePath);
	m_Pe.ReadPE();
	if (m_Pe.IsPeFile())
	{
		m_Section.EnableWindow(TRUE);
		m_DataDir.EnableWindow(TRUE);
		m_Calc.EnableWindow(TRUE);
		m_Time.EnableWindow(TRUE);
		ShowFileHeader();
		ShowOpHeader();
	}
	else
	{
		MessageBox(_T("此文件不是PE文件！"));
	}
	CDialogEx::OnDropFiles(hDropInfo);
}


void CPeDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CSectionDlg section(&m_Pe);
	section.DoModal();
}


BOOL CPeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	// TODO:  在此添加额外的初始化
	m_Section.EnableWindow(FALSE);
	m_DataDir.EnableWindow(FALSE);
	m_Calc.EnableWindow(FALSE);
	m_Time.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPeDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataDirDlg dataDirDlg(&m_Pe);
	dataDirDlg.DoModal();
}


void CPeDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CCalcDlg calc(&m_Pe);
	calc.DoModal();
}
