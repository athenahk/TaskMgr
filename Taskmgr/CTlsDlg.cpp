// CTlsDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CTlsDlg.h"
#include "afxdialogex.h"


// CTlsDlg 对话框

IMPLEMENT_DYNAMIC(CTlsDlg, CDialogEx)

CTlsDlg::CTlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TLS, pParent)
{

}

CTlsDlg::CTlsDlg(CPe* Pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_TLS, pParent)
{
	m_Pe = Pe;
}
CTlsDlg::~CTlsDlg()
{
}

void CTlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTlsDlg, CDialogEx)
END_MESSAGE_MAP()


// CTlsDlg 消息处理程序


BOOL CTlsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	PIMAGE_DATA_DIRECTORY pData = m_Pe->GetPData();
	DWORD dwFoa = m_Pe->RvaToFoa(m_Pe->m_pBuf, pData[9].VirtualAddress);
	PIMAGE_TLS_DIRECTORY32 pTls = (PIMAGE_TLS_DIRECTORY32)(m_Pe->m_pBuf + dwFoa);
	CString szStr;
	CWnd* pWnd = 0;
	for (int i = 0; i < 6; i++)
	{	
		pWnd = GetDlgItem(IDC_EDIT_TLS1 + i);
		szStr.Format(L"%08x", *((PDWORD)pTls + i));
		pWnd->SetWindowTextW(szStr);
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
