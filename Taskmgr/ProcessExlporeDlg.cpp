
// ProcessExlporeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ProcessExlpore.h"
#include "ProcessExlporeDlg.h"
#include "afxdialogex.h"
#include<TlHelp32.h>
#include<windows.h>
#include<Psapi.h>
#include"Resource.h"
#include "CModDlg.h"
#include "CThreadDlg.h"
#include "CFileDlg.h"
#include "CHeapDlg.h"
#include "CWindowDlg.h"
#include "CServiceDlg.h"
#include"CKillVirusDlg.h"
#include "COperDlg.h"
#define PATH L"E:\\Folder\\注入\\第二天 - 副本\\Debug\\03_Inline-Hook.dll"
#pragma comment(lib, "psapi.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProcessExlporeDlg 对话框



CProcessExlporeDlg::CProcessExlporeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESSEXLPORE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsWindowHide = TRUE;
}

void CProcessExlporeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CProcessExlporeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_RBUTTONDBLCLK()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CProcessExlporeDlg::OnNMRClickList1)
	ON_COMMAND(ID_32771, &CProcessExlporeDlg::OnViewThread)
	ON_COMMAND(ID_32772, &CProcessExlporeDlg::OnViewModule)
	ON_WM_TIMER()	
	ON_MESSAGE(WM_USER + 1, &CProcessExlporeDlg::OnTimeCpu)
	ON_COMMAND(ID_32773, &CProcessExlporeDlg::OnClickExitProc)
	//ON_MESSAGE(WM_USER + 2, &CProcessExlporeDlg::OnUserClickExitThread)
	ON_BN_CLICKED(IDC_BUTTON1, &CProcessExlporeDlg::OnBnClickedButton1)
	ON_COMMAND(ID_32777, &CProcessExlporeDlg::OnClickEnumHeap)
	ON_BN_CLICKED(IDC_BUTTON7, &CProcessExlporeDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON2, &CProcessExlporeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProcessExlporeDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CProcessExlporeDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CProcessExlporeDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_HUISHOU, &CProcessExlporeDlg::OnBnClickedButtonHuishou)
	ON_BN_CLICKED(IDC_BUTTON5, &CProcessExlporeDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CProcessExlporeDlg::OnBnClickedButton6)
	ON_COMMAND(ID_32780, &CProcessExlporeDlg::OnInjectDLL)
	ON_BN_CLICKED(IDC_BUTTON8, &CProcessExlporeDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_HOTKEY, &CProcessExlporeDlg::OnBnClickedButtonHotkey)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()

void EnumProcess(vector<DWORD> &m_vecPID, CListCtrl& m_ListCtrl)
{
	int i = 0;
	TCHAR szBuffer[200] = {};
	TCHAR szFilePath[MAX_PATH + 1] = {0};
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		NULL
	);
	
	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	BOOL bSuccess = Process32First(hSnapshot, &pe32);

	if (bSuccess)
	{
		do {
			_stprintf_s(szBuffer, 200, _T("%d"), pe32.th32ProcessID);
			m_vecPID.push_back(pe32.th32ProcessID);
			m_ListCtrl.InsertItem(i, szBuffer);
			_stprintf_s(szBuffer, 200, _T("%s"), pe32.szExeFile);
			m_ListCtrl.SetItemText(i, 1, szBuffer);
			_stprintf_s(szBuffer, 200, _T("%d"), pe32.cntThreads);
			m_ListCtrl.SetItemText(i, 2, szBuffer);

			DWORD length = MAX_PATH + 1;
			HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
			//GetProcessImageFileNameW(hProcess, szFilePath, MAX_PATH+ 1);
			QueryFullProcessImageNameW(hProcess, 0, szFilePath, &length);
			CloseHandle(hProcess);
			m_ListCtrl.SetItemText(i, 3, szFilePath);
			i++;
		} while (Process32Next(hSnapshot, &pe32));
	
	}
}

// CProcessExlporeDlg 消息处理程序

void GetCpuUsage();

DWORD ThreadProc(
	LPVOID lpThreadParameter
)
{
	while (TRUE)
	{
		GetCpuUsage();
	}
	return 0;
}


//DWORD ThreadProc1(
//	LPVOID lpThreadParameter
//)
//{
//	HWND hWnd = (HWND)lpThreadParameter;
//	while (TRUE)
//	{
//		Sleep(5000);
//		SendMessage(hWnd, WM_USER + 2,0 ,0);
//	}
//	return 0;
//}
					   
BOOL CProcessExlporeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	
	// 设置列表风格: 整行选中 + 表格线
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"PID", LVCFMT_CENTER, 100);
	m_ListCtrl.InsertColumn(2, L"进程名称", LVCFMT_CENTER, 200);
	m_ListCtrl.InsertColumn(3, L"线程数量", LVCFMT_CENTER, 300);
	m_ListCtrl.InsertColumn(4, L"进程路径", LVCFMT_CENTER, 700);

	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc1, this->m_hWnd, NULL, NULL);
	EnumProcess(m_vecPID, m_ListCtrl);
	// 添加行信息（添加行首元素 + 这一行中列元素的值），可以指定图标索引
	/*m_ListCtrl.InsertItem(0, L"0x04", 0);
	m_ListCtrl.SetItemText(0, 1, L"qq.exe");
	m_ListCtrl.SetItemText(0, 2, L"C:\\app\\qq.exe");
	m_ListCtrl.InsertItem(1, L"0x08", 1);
	m_ListCtrl.SetItemText(1, 1, L"wechat.exe");
	m_ListCtrl.SetItemText(1, 2, L"C:\\app\\wechat.exe");
	m_ListCtrl.InsertItem(2, L"0x0C", 2);
	m_ListCtrl.SetItemText(2, 1, L"tim.exe");
	m_ListCtrl.SetItemText(2, 2, L"C:\\app\\tim.exe");*/
	// 状态栏的使用，先初始化状态栏
	m_StatusBar.Create(this);

	// 需要创建一个数组，提供每一栏的 ID 值，用于分割状态栏
	unsigned int Array[3] = { 0x5001, 0x5002, 0x5003 };
	m_StatusBar.SetIndicators(Array, 3);

	// 设置每一栏的属性值（初始化每一栏的内容，宽度自适应）
	m_StatusBar.SetPaneInfo(0, 0x5001, SBPS_STRETCH, 100);
	m_StatusBar.SetPaneInfo(1, 0x5002, SBPS_STRETCH, 100);
	m_StatusBar.SetPaneInfo(2, 0x5003, SBPS_STRETCH, 100);


	// 通过一个函数动态的计算出工具栏和状态栏的位置，并进行显示
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);


	// 使用定时器动态的刷新当前的时间
	SetTimer(0x01, 1000, NULL);
	SetTimer(0x02, 1000, NULL);
	//SetTimer(0x03, 1000, NULL);
	HANDLE hThread = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)ThreadProc, NULL, NULL, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProcessExlporeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProcessExlporeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProcessExlporeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CProcessExlporeDlg::OnRButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CMenu menu;
//	menu.LoadMenuW(IDR_MENU1);
//	CMenu* pSub = menu.GetSubMenu(0);
//	POINT pi;
//	GetCursorPos(&pi);
//	pSub->TrackPopupMenu(TPM_RIGHTALIGN, pi.x, pi.y, this);
//	CDialogEx::OnRButtonDblClk(nFlags, point);
//}


void CProcessExlporeDlg::OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CMenu menu;
	menu.LoadMenuW(IDR_MENU1);
	CMenu* pSub = menu.GetSubMenu(0);
	POINT pi;
	GetCursorPos(&pi);
	pSub->TrackPopupMenu(TPM_RIGHTALIGN, pi.x, pi.y, this);
	*pResult = 0;
}


void CProcessExlporeDlg::OnViewThread()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrl.GetSelectionMark();
	DWORD dwPid = m_vecPID[dwIndex];


	CThreadDlg thread(dwPid);
	thread.DoModal();
}


void CProcessExlporeDlg::OnViewModule()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrl.GetSelectionMark();
	DWORD dwPid = m_vecPID[dwIndex];


	CModDlg mod(dwPid);
	mod.DoModal();
}


DWORD GetMemoryUsedPrecent()
{
	MEMORYSTATUSEX memStatus = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx(&memStatus);
	return memStatus.dwMemoryLoad;
}

double FILETIME2Double(const _FILETIME& fileTime)
{
	return double(fileTime.dwHighDateTime * 4.294967296e9)
		+ double(fileTime.dwLowDateTime);
}

void GetCpuUsage()
{
	CString sz;
	_FILETIME idleTime, kernelTime, userTime;

	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	Sleep(1000);
	_FILETIME newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);

	double dOldIdleTime = FILETIME2Double(idleTime);
	double dNewIdleTime = FILETIME2Double(newIdleTime);
	double dOldKernelTime = FILETIME2Double(kernelTime);
	double dNewKernelTime = FILETIME2Double(newKernelTime);
	double dOldUserTime = FILETIME2Double(userTime);
	double dNewUserTime = FILETIME2Double(newUserTime);

	double howUsePrecent =  double(100.0 - (dNewIdleTime - dOldIdleTime) /
		(dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime) * 100.0);
	sz.Format(L"%lf", howUsePrecent);
	HWND hWnd = FindWindow(NULL, L"任务管理器");
	SendMessage(hWnd, WM_USER + 1, (WPARAM)sz.GetBuffer(), 0);
}
void CProcessExlporeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 获取当前的系统时间
	SYSTEMTIME SystemTime = { 0 };
	GetSystemTime(&SystemTime);

	// 格式化时间设置到状态栏中
	CString temp;
	temp.Format(L"%d-%d-%d %d:%d:%d", SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,SystemTime.wHour + 8, SystemTime.wMinute, SystemTime.wSecond);
	m_StatusBar.SetPaneText(0, temp);
	temp.Format(L"内存:%d%%", GetMemoryUsedPrecent());
	m_StatusBar.SetPaneText(1, temp);
	//temp.Format(L"CPU:%d%%", GetCpuUsage());
	//m_StatusBar.SetPaneText(2, temp);

	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CProcessExlporeDlg::OnTimeCpu(WPARAM wParam, LPARAM lParam)
{
	CString sz;
	TCHAR* buff = (TCHAR*)(wParam);
	sz.Format(L"CPU:%s%%", buff);
	m_StatusBar.SetPaneText(2, sz);
	return 0;
}


void CProcessExlporeDlg::OnClickExitProc()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrl.GetSelectionMark();
	DWORD dwPid = m_vecPID[dwIndex];


	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);
	m_ListCtrl.DeleteItem(dwIndex);
	MessageBox(L"已结束进程");
}


//afx_msg LRESULT CProcessExlporeDlg::OnUserClickExitThread(WPARAM wParam, LPARAM lParam)
//{
//	int i = 0;
//	TCHAR szBuffer[200] = {};
//	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
//	HANDLE hSnapshot = CreateToolhelp32Snapshot(
//		TH32CS_SNAPPROCESS,
//		NULL
//	);
//
//	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
//	BOOL bSuccess = Process32First(hSnapshot, &pe32);
//
//	if (bSuccess)
//	{
//		do {
//			_stprintf_s(szBuffer, 200, _T("%d"), pe32.th32ProcessID);
//			m_vecPID.push_back(pe32.th32ProcessID);
//			m_ListCtrl.InsertItem(i, szBuffer);
//			_stprintf_s(szBuffer, 200, _T("%s"), pe32.szExeFile);
//			m_ListCtrl.SetItemText(i, 1, szBuffer);
//			_stprintf_s(szBuffer, 200, _T("%d"), pe32.cntThreads);
//			m_ListCtrl.SetItemText(i, 2, szBuffer);
//
//			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
//			GetProcessImageFileNameW(hProcess, szFilePath, MAX_PATH + 1);
//			CloseHandle(hProcess);
//			m_ListCtrl.SetItemText(i, 3, szFilePath);
//			i++;
//		} while (Process32Next(hSnapshot, &pe32));
//		
//	}
//	return 0;
//}


void CProcessExlporeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDlg File;
	File.DoModal();
}


void CProcessExlporeDlg::OnClickEnumHeap()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrl.GetSelectionMark();
	DWORD dwPid = m_vecPID[dwIndex];

	CHeapDlg Heap(dwPid);
	Heap.DoModal();
}


void CProcessExlporeDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CWindowDlg Window;
	Window.DoModal();
}

extern wchar_t* Browse(HWND hWnd);

bool FindHouZhuiNameFile(const wchar_t* szFileName)
{
	//.obj\.tlog\.lastbuildstate\.idb\.pdb\.pch\.res\.ilk\.exe\.sdf\.ipch\.log
	int index = 0;
	int flag = 0;
	wchar_t houzhui[12][30] = { {L"obj"},{L"tlog"},{L"lastbuildstate"},{L"idb"},{L"pdb"},
		{L"pch"},{L"res"},{L"ilk"},{L"exe"},{L"sdf"},{L"ipch"},{L"log"} };
	int length = lstrlen(szFileName);
	wchar_t houZhuiDump[20] = { 0 };
	for (int i = length; i > 0; i--)
	{
		if (szFileName[i - 1] == '.')
		{
			flag = 1;
			int z = i;
			for (int j = 0; j < length - i; j++)
			{
				houZhuiDump[j] = szFileName[z];
				z++;
			}
		}
		if (flag == 1)
			break;
	}

	for (int i = 0; i < 12; i++)
	{
		if (lstrcmp(houZhuiDump, houzhui[i]) == 0)
			return true;
	}
	return false;
}

DWORD ListAllFileInDirectory(LPWSTR szPath)
{

	wchar_t szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	wchar_t szFullPath[MAX_PATH];
	TCHAR szBuff[0x100] = { 0 };
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, L"\\*");

	hListFile = FindFirstFile(szFilePath, &FindFileData);
	if (hListFile == INVALID_HANDLE_VALUE)
	{
		printf("错误: %d", GetLastError());
		return 1;
	}
	else
	{
		do {
			if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 ||
				lstrcmp(FindFileData.cFileName, TEXT("..")) == 0)
			{
				continue;
			}
			wsprintf(szFullPath, L"%s\\%s", szPath, FindFileData.cFileName);
			if (FindHouZhuiNameFile(FindFileData.cFileName)) {
			//	wsprintf(szFullPath, L"%s\\%s", szPath, FindFileData.cFileName);
				DeleteFile(szFullPath);
			}
			//_stprintf_s(szBuff, 0x100, _T("%s"), FindFileData.cFileName);
			//_tprintf(TEXT("%s:\n"), wfd.cFileName);
		//	m_ListCtrl.InsertItem(i, szBuff);
		//	if (FindFileData.nFileSizeLow > 0)
		//		FindFileData.nFileSizeLow = FindFileData.nFileSizeLow / 8 / 1024 + 1;
		//	_stprintf_s(szBuff, 0x100, _T("%dKB"), FindFileData.nFileSizeLow);
		//	m_ListCtrl.SetItemText(i, 3, szBuff);
			//printf("文件大小为:%d字节", wfd.nFileSizeLow);
			//FILETIME  Time = { 0 };
			//FileTimeToLocalFileTime(&FindFileData.ftCreationTime, &Time);
			//SYSTEMTIME sysTime = { 0 };
			//FileTimeToSystemTime(&Time, &sysTime);
			//_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
			//	sysTime.wMonth, sysTime.wDay, sysTime.wHour,
			//	sysTime.wMinute, sysTime.wSecond);
			//m_ListCtrl.SetItemText(i, 1, szBuff);
			//FILETIME  Time1 = { 0 };
			//FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &Time1);
			//SYSTEMTIME sysTime1 = { 0 };
			//FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &sysTime1);
			//_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
			//	sysTime1.wMonth, sysTime1.wDay, sysTime1.wHour + 8,
			//	sysTime1.wMinute, sysTime1.wSecond);
			////m_ListCtrl.SetItemText(i, 2, szBuff);

			//	wprintf(L"%s\t", szFullPath);
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//printf("<DIR>");
				ListAllFileInDirectory(szFullPath);
			}
			//i++;
		} while (FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}

void EnumFile1(LPWSTR szFilePath)
{
	ListAllFileInDirectory(szFilePath);
}
//vs清理
void CProcessExlporeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t szFilePath[0x100] = { 0 };
	lstrcpy(szFilePath, Browse(NULL));
	EnumFile1(szFilePath);
	MessageBox(L"项目清理完成");
}


void CProcessExlporeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CPeDlg Pe;
	Pe.DoModal();
}


void CProcessExlporeDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//清理内存
void CProcessExlporeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	MEMORYSTATUSEX stcMemStatusEx = { 0 };
	stcMemStatusEx.dwLength = sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsedMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;

	DWORD dwPIDList[1000] = { 0 };
	DWORD bufSize = sizeof(dwPIDList);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPIDList, bufSize, &dwNeedSize);
	for (DWORD i = 0; i < dwNeedSize / sizeof(DWORD); i++)
	{
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPIDList[i]);
		SetProcessWorkingSetSize(hProcess, -1, -1);
	}

	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUsedMem = stcMemStatusEx.ullTotalPhys - stcMemStatusEx.ullAvailPhys;
	MessageBox(L"内存清理完成！");
}

//清理回收站
void CProcessExlporeDlg::OnBnClickedButtonHuishou()
{
	// TODO: 在此添加控件通知处理程序代码
	SHQUERYRBINFO RecycleBinInfo = {};
	RecycleBinInfo.cbSize = sizeof(RecycleBinInfo);

	SHQueryRecycleBin(NULL, &RecycleBinInfo);

	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
	MessageBox(L"回收站清理成功!");
}

//服务
void CProcessExlporeDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CServiceDlg service;
	service.DoModal();
}

//杀毒
void CProcessExlporeDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CKillVirusDlg kv;
	kv.DoModal();
}


void CProcessExlporeDlg::OnInjectDLL()
{
	// TODO: 在此添加命令处理程序代码
	DWORD dwIndex = m_ListCtrl.GetSelectionMark();
	DWORD dwPid = m_vecPID[dwIndex];

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	//2. 在目标进程中申请一块空间
	LPVOID pBuf = VirtualAllocEx(
		hProcess, //目标进程的句柄
		NULL, 100, MEM_COMMIT, PAGE_READWRITE);
	//3. 将dll的路径写入到对方空间中
	DWORD dwRealSize = 0;
	WriteProcessMemory(
		hProcess,  //目标进程句柄   
		pBuf,      //目标进程的缓冲区地址
		PATH,      //要写入数据的起始地址
		(wcslen(PATH) + 1) * 2,//写入的大小  
		&dwRealSize
	);
	//4. 创建一个远程线程，将LoadLibrary作为回调函数，dll路径的起始地址作为参数
	HANDLE hThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)(LoadLibrary),
		pBuf,
		0, 0
	);
	//5. 等待线程结束，关闭句柄，将对方进程空间申请的内存释放
	WaitForSingleObject(hThread, -1);
	//VirtualFre
}

//关机休眠等等
void CProcessExlporeDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	COperDlg op;
	op.DoModal();
}


void CProcessExlporeDlg::OnBnClickedButtonHotkey()
{
	// TODO: 在此添加控件通知处理程序代码
	::RegisterHotKey(this->GetSafeHwnd(), 0xa001, MOD_CONTROL | MOD_SHIFT, 'K');
}


//void CProcessExlporeDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
//}


//BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0xa001))
//	{
//		if (IsWindowVisible() == TRUE)
//			ShowWindow(SW_HIDE);
//		else
//			ShowWindow(SW_SHOW);
//	}
//	return CDialogEx::PreTranslateMessage(pMsg);
//}


BOOL CProcessExlporeDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0xa001))
	{
		if (m_IsWindowHide == TRUE)
		{
			ShowWindow(SW_HIDE);
			m_IsWindowHide = FALSE;
		}
		else {
			ShowWindow(SW_SHOW);
			m_IsWindowHide = TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
