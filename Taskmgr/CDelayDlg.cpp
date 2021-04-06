// CDelayDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CDelayDlg.h"
#include "afxdialogex.h"


// CDelayDlg 对话框

IMPLEMENT_DYNAMIC(CDelayDlg, CDialogEx)

CDelayDlg::CDelayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELAY, pParent)
{

}

CDelayDlg::CDelayDlg(CPe* pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_DELAY, pParent)
{
	m_Pe = pe;
}

CDelayDlg::~CDelayDlg()
{
}

void CDelayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDelayDlg, CDialogEx)
END_MESSAGE_MAP()


// CDelayDlg 消息处理程序


BOOL CDelayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	PIMAGE_DATA_DIRECTORY pData = m_Pe->GetPData();
	DWORD dwFoa = m_Pe->RvaToFoa(m_Pe->m_pBuf, pData[13].VirtualAddress);
	PIMAGE_DELAYLOAD_DESCRIPTOR pTls = (PIMAGE_DELAYLOAD_DESCRIPTOR)(m_Pe->m_pBuf + dwFoa);
	CString szStr;
	CWnd* pWnd = 0;
	for (int i = 0; i < 8; i++)
	{
		pWnd = GetDlgItem(IDC_EDIT_DELAY1 + i);
		szStr.Format(L"%08x", *((PDWORD)pTls + i));
		pWnd->SetWindowTextW(szStr);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
