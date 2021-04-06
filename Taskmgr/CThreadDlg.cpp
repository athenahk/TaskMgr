// CThreadDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CThreadDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>
#include "Resource.h"

// CThreadDlg 对话框

IMPLEMENT_DYNAMIC(CThreadDlg, CDialogEx)

CThreadDlg::CThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_THREAD, pParent)
{

}

CThreadDlg::CThreadDlg(DWORD dwPid, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_THREAD, pParent)
{
	this->dwPid = dwPid;
}

CThreadDlg::~CThreadDlg()
{
}

void CThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_THREAD, m_ListCtrlThread);
}


BEGIN_MESSAGE_MAP(CThreadDlg, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_THREAD, &CThreadDlg::OnNMRClickListThread)
	ON_COMMAND(ID_32774, &CThreadDlg::OnClickedResumeThread)
	ON_COMMAND(ID_32775, &CThreadDlg::OnClickResumeThread)
	ON_COMMAND(ID_32776, &CThreadDlg::OnClickExitThread)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_THREAD, &CThreadDlg::OnLvnItemchangedListThread)
END_MESSAGE_MAP()


// CThreadDlg 消息处理程序
void EnumThread(DWORD dwPid, CMyListCtrl& m_ListCtrlThread, vector<DWORD>& m_vecTid)
{
	TCHAR szBuffer[200] = { 0 };
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	THREADENTRY32 te32 = { sizeof(te32) };
	BOOL bSuccess = Thread32First(hSnapshot, &te32);
	if (bSuccess)
	{
		int i = 0;
		do {
			if (te32.th32OwnerProcessID == dwPid)
			{
				_stprintf_s(szBuffer, 200, _T("%d"), te32.th32ThreadID);
				m_vecTid.push_back(te32.th32ThreadID);
				m_ListCtrlThread.InsertItem(i, szBuffer);
				_stprintf_s(szBuffer, 200, _T("%d"), te32.tpBasePri);
				m_ListCtrlThread.SetItemText(i, 1, szBuffer);
				i++;
			}
		} while (Thread32Next(hSnapshot, &te32));
	}
}

BOOL CThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlThread.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlThread.InsertColumn(1, L"线程ID", LVCFMT_CENTER, 200);
	m_ListCtrlThread.InsertColumn(2, L"线程优先级", LVCFMT_CENTER, 200);
	EnumThread(dwPid, m_ListCtrlThread, m_vecTid);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CThreadDlg::OnNMRClickListThread(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu menu;
	menu.LoadMenuW(IDR_MENU2);
	CMenu* pSub = menu.GetSubMenu(0);
	POINT pi;
	GetCursorPos(&pi);
	pSub->TrackPopupMenu(TPM_RIGHTALIGN, pi.x, pi.y, this);
	*pResult = 0;
}


void CThreadDlg::OnClickedResumeThread()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrlThread.GetSelectionMark();
	DWORD dwTid = m_vecTid[dwIndex];

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwTid);
	SuspendThread(hThread);
	CloseHandle(hThread);
}


void CThreadDlg::OnClickResumeThread()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrlThread.GetSelectionMark();
	DWORD dwTid = m_vecTid[dwIndex];

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwTid);
	ResumeThread(hThread);
	CloseHandle(hThread);
}


void CThreadDlg::OnClickExitThread()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrlThread.GetSelectionMark();
	DWORD dwTid = m_vecTid[dwIndex];

	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, dwTid);
	TerminateThread(hThread, 0);
	CloseHandle(hThread);
}


//void CThreadDlg::OnLvnItemchangedListThread(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}
