// CModDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CModDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")


// CModDlg 对话框

IMPLEMENT_DYNAMIC(CModDlg, CDialogEx)

CModDlg::CModDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MOD, pParent)
{

}

CModDlg::CModDlg(DWORD dwPid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MOD, pParent)
{
	this->dwPid = dwPid;
}

CModDlg::~CModDlg()
{
}

void CModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MOD, m_ListCtrlMod);
}


BEGIN_MESSAGE_MAP(CModDlg, CDialogEx)
END_MESSAGE_MAP()


// CModDlg 消息处理程序

void EnumModule(DWORD dwPid, CMyListCtrl& m_ListCtrlMod)
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,false, dwPid);
	DWORD dwNeed = 0;
	TCHAR szBuffer[200] = {0};
	HMODULE hModules[0x2000] = {};
	EnumProcessModulesEx(hProcess, hModules, sizeof(hModules), &dwNeed, LIST_MODULES_ALL);
	DWORD dwModuleCount = dwNeed / sizeof(HMODULE);
	MODULEINFO moif = { 0 };
	TCHAR szBuff[0x500] = { 0 };
	if (hProcess == 0)
	{
		_stprintf_s(szBuff, 0x500, _T("%d"), 0);
		m_ListCtrlMod.InsertItem(0, szBuff);
		_stprintf_s(szBuffer, 200, _T("%d"), 0);
		m_ListCtrlMod.SetItemText(0, 1, szBuffer);
		m_ListCtrlMod.SetItemText(0, 3, szBuffer);
		m_ListCtrlMod.SetItemText(0, 2, szBuffer);
		return;
	}
	for (SIZE_T i = 0; i < dwModuleCount; ++i)
	{
		GetModuleFileNameEx(hProcess, hModules[i], szBuff, 0x500);
		m_ListCtrlMod.InsertItem(i, szBuff);
		GetModuleInformation(hProcess, hModules[i], &moif, sizeof(MODULEINFO));
		_stprintf_s(szBuffer, 200, _T("0x%x"), moif.EntryPoint);
		//m_vecPID.push_back(pe32.th32ProcessID);
		m_ListCtrlMod.SetItemText(i,1, szBuffer);
		_stprintf_s(szBuffer, 200, _T("0x%x"), moif.lpBaseOfDll);
		m_ListCtrlMod.SetItemText(i, 2, szBuffer);
		_stprintf_s(szBuffer, 200, _T("0x%x"), moif.SizeOfImage);
		m_ListCtrlMod.SetItemText(i, 3, szBuffer);
		//moif.EntryPoint;
		//moif.lpBaseOfDll;
		//moif.SizeOfImage;
	}

}
BOOL CModDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlMod.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlMod.InsertColumn(1, L"模块路径", LVCFMT_CENTER, 500);
	m_ListCtrlMod.InsertColumn(2, L"dll入口点", LVCFMT_CENTER, 200);
	m_ListCtrlMod.InsertColumn(3, L"dll基址", LVCFMT_CENTER, 200);
	m_ListCtrlMod.InsertColumn(4, L"dll大小", LVCFMT_CENTER, 200);
	EnumModule(dwPid, m_ListCtrlMod);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
