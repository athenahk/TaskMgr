// COperDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "COperDlg.h"
#include "afxdialogex.h"
#include<windows.h>
#include<powrprof.h>
#pragma comment(lib, "PowrProf.lib")
// COperDlg 对话框

IMPLEMENT_DYNAMIC(COperDlg, CDialogEx)

COperDlg::COperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OP, pParent)
{

}

COperDlg::~COperDlg()
{
}

void COperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COperDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COperDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &COperDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &COperDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// COperDlg 消息处理程序

//关机
void COperDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	InitiateSystemShutdownEx(
		NULL,        // NULL 为操作本地计算机
		L"即将关机", // 关机或重启提示框文本信息
		5,           // 延时时间
		FALSE,       // TRUE 为强制关闭，FALSE 为提示关闭计算机
		FALSE,        // TRUE 为重启，FALSE 为关机
		NULL);
}

//注销
void COperDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, NULL);
}

//休眠
void COperDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	SetSuspendState(TRUE, FALSE, FALSE);
}
