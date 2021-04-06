// CFileDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CFileDlg.h"
#include "afxdialogex.h"
#include <locale.h>

// CFileDlg 对话框

IMPLEMENT_DYNAMIC(CFileDlg, CDialogEx)

CFileDlg::CFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FILE, pParent)
{

}

CFileDlg::~CFileDlg()
{
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileDlg 消息处理程序

void EnumFile(CMyListCtrl& m_ListCtrl)
{
	TCHAR szBuff[0x100] = { 0 };
	WIN32_FIND_DATA  wfd = {};
	setlocale(LC_ALL, "chs"); // 设置字符编码格式
	   //找到第一个文件
	HANDLE hFindFile = FindFirstFile(TEXT("E:\\code\\Window\\ConsoleApplication1222\\ConsoleApplication1222\\*"), &wfd);

	int i = 0;
	if (hFindFile != INVALID_HANDLE_VALUE) {
		do {
			_stprintf_s(szBuff, 0x100, _T("%s"), wfd.cFileName);
			//_tprintf(TEXT("%s:\n"), wfd.cFileName);
			m_ListCtrl.InsertItem(i, szBuff);
			if (wfd.nFileSizeLow > 0)
				wfd.nFileSizeLow = wfd.nFileSizeLow / 8 / 1024 + 1;
			_stprintf_s(szBuff, 0x100, _T("%dKB"), wfd.nFileSizeLow);
			m_ListCtrl.SetItemText(i, 3, szBuff);
			//printf("文件大小为:%d字节", wfd.nFileSizeLow);
			FILETIME  Time = { 0 };
			FileTimeToLocalFileTime(&wfd.ftCreationTime, &Time);
			SYSTEMTIME sysTime = { 0 };
			FileTimeToSystemTime(&Time, &sysTime);
			_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
				sysTime.wMonth, sysTime.wDay, sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond);
			m_ListCtrl.SetItemText(i, 1, szBuff);
			FILETIME  Time1 = { 0 };
			FileTimeToLocalFileTime(&wfd.ftLastWriteTime, &Time1);
			SYSTEMTIME sysTime1 = { 0 };
			FileTimeToSystemTime(&wfd.ftLastWriteTime, &sysTime1);
			_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
				sysTime1.wMonth, sysTime1.wDay, sysTime1.wHour + 8,
				sysTime1.wMinute, sysTime1.wSecond);
			m_ListCtrl.SetItemText(i, 2, szBuff);
			//printf("创建时间:%d年%d月%d日%d时%d分%d秒\n",
			//	sysTime.wYear,
			//	sysTime.wMonth, sysTime.wDay, sysTime.wHour,
			//	sysTime.wMinute, sysTime.wSecond);
			i++;
		} while (FindNextFile(hFindFile, &wfd));
	}
}

int i = 0;
DWORD ListAllFileInDirectory(LPWSTR szPath, CMyListCtrl& m_ListCtrl)
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

			_stprintf_s(szBuff, 0x100, _T("%s"), FindFileData.cFileName);
			//_tprintf(TEXT("%s:\n"), wfd.cFileName);
			m_ListCtrl.InsertItem(i, szBuff);
			if (FindFileData.nFileSizeLow > 0)
				FindFileData.nFileSizeLow = FindFileData.nFileSizeLow / 8 / 1024 + 1;
			_stprintf_s(szBuff, 0x100, _T("%dKB"), FindFileData.nFileSizeLow);
			m_ListCtrl.SetItemText(i, 3, szBuff);
			//printf("文件大小为:%d字节", wfd.nFileSizeLow);
			FILETIME  Time = { 0 };
			FileTimeToLocalFileTime(&FindFileData.ftCreationTime, &Time);
			SYSTEMTIME sysTime = { 0 };
			FileTimeToSystemTime(&Time, &sysTime);
			_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
				sysTime.wMonth, sysTime.wDay, sysTime.wHour,
				sysTime.wMinute, sysTime.wSecond);
			m_ListCtrl.SetItemText(i, 1, szBuff);
			FILETIME  Time1 = { 0 };
			FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &Time1);
			SYSTEMTIME sysTime1 = { 0 };
			FileTimeToSystemTime(&FindFileData.ftLastWriteTime, &sysTime1);
			_stprintf_s(szBuff, 0x100, _T("%d年%d月%d日%d时%d分%d秒"), sysTime.wYear,
				sysTime1.wMonth, sysTime1.wDay, sysTime1.wHour + 8,
				sysTime1.wMinute, sysTime1.wSecond);
			m_ListCtrl.SetItemText(i, 2, szBuff);

		//	wprintf(L"%s\t", szFullPath);
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//printf("<DIR>");
				ListAllFileInDirectory(szFullPath, m_ListCtrl);
			}
			i++;
		} while (FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}

void EnumFile1(CMyListCtrl& m_ListCtrl, LPWSTR szFilePath)
{
	i = 0;
	ListAllFileInDirectory(szFilePath, m_ListCtrl);
}

wchar_t* Browse(HWND hWnd)
{
	wchar_t szRoot[MAX_PATH];
	wchar_t szChoose[MAX_PATH];
	wchar_t szDisplayName[MAX_PATH];

	LPITEMIDLIST pidlRoot = NULL;
	LPITEMIDLIST pidlSecected = NULL;

	BROWSEINFO bi = { 0 };
	LPMALLOC pMalloc = NULL;

	SHGetFolderLocation(NULL, CSIDL_DESKTOP, NULL, 0, &pidlRoot);
	SHGetPathFromIDList(pidlRoot, szRoot);

	bi.hwndOwner = hWnd;
	bi.pidlRoot = pidlRoot;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = L"Choose a target";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;

	pidlSecected = SHBrowseForFolder(&bi);
	SHGetPathFromIDList(pidlSecected, szChoose);

	ILFree(pidlRoot);
	return szChoose;
}


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	wchar_t szFilePath[0x100] = { 0 };
	// TODO:  在此添加额外的初始化
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrl.InsertColumn(1, L"文件名", LVCFMT_CENTER, 300);
	m_ListCtrl.InsertColumn(2, L"创建时间", LVCFMT_CENTER, 200);
	m_ListCtrl.InsertColumn(3, L"修改时间", LVCFMT_CENTER, 200);
	m_ListCtrl.InsertColumn(4, L"文件大小", LVCFMT_CENTER, 300);
	lstrcpy(szFilePath, Browse(NULL));
	EnumFile1(m_ListCtrl,szFilePath);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
