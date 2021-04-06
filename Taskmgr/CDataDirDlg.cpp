// CDataDirDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CDataDirDlg.h"
#include "afxdialogex.h"


// CDataDirDlg 对话框

IMPLEMENT_DYNAMIC(CDataDirDlg, CDialogEx)

CDataDirDlg::CDataDirDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DATADIR, pParent)
{

}

CDataDirDlg::CDataDirDlg(CPe* Pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_DATADIR, pParent)
{
	m_Pe = Pe;
}
CDataDirDlg::~CDataDirDlg()
{
}

void CDataDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataDirDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataDirDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDataDirDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CDataDirDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CDataDirDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CDataDirDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDataDirDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDataDirDlg 消息处理程序
void CDataDirDlg::InitDataDir()
{
	vector<DataDirInfo> vDataDirInfo = m_Pe->GetDataDirInfo();
	CWnd* pWnd = NULL;
	CString szRva, szSize;
	for (int i = 0; i < 16; i++)
	{
		pWnd = GetDlgItem(IDC_EDIT30 + 2 * i + 0);
		szRva.Format(L"0x%08x", vDataDirInfo[i].VirtualAddress);
		pWnd->SetWindowTextW(szRva);
		pWnd = GetDlgItem(IDC_EDIT30 + 2 * i + 1);
		szSize.Format(L"0x%08x", vDataDirInfo[i].Size);
		pWnd->SetWindowTextW(szSize);
	}
}


BOOL CDataDirDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitDataDir();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDataDirDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	PIMAGE_DATA_DIRECTORY pData = NULL;
	pData = m_Pe->GetPData();
	if (pData[0].VirtualAddress == 0 && pData[0].Size == 0)
	{
		MessageBox(L"无导出表!");
		return;
	}
	CExportDlg export1(m_Pe);
	export1.DoModal();

}


void CDataDirDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CImportDlg import(m_Pe);
	import.DoModal();
}


void CDataDirDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CRelocaDlg reloca(m_Pe);
	reloca.DoModal();
}


void CDataDirDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CResDlg resdlg(m_Pe);
	resdlg.DoModal();
}

//TLS
void CDataDirDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	PIMAGE_DATA_DIRECTORY pData = NULL;
	pData = m_Pe->GetPData();
	if (pData[9].VirtualAddress == 0 && pData[9].Size == 0)
	{
		MessageBox(L"无TLS表!");
		return;
	}
	CTlsDlg tls(m_Pe);
	tls.DoModal();
}

//延迟载入
void CDataDirDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	PIMAGE_DATA_DIRECTORY pData = NULL;
	pData = m_Pe->GetPData();
	if (pData[13].VirtualAddress == 0 && pData[13].Size == 0)
	{
		MessageBox(L"无延迟载入表!");
		return;
	}
	CDelayDlg delay(m_Pe);
	delay.DoModal();
}
