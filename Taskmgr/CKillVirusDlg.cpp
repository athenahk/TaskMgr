// CKillVirusDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CKillVirusDlg.h"
#include "afxdialogex.h"
#include "openssl/md5.h"
#include "openssl/sha.h"
#include<vector>
#include <windows.h>
#include<TlHelp32.h>
#pragma comment(lib, "libcrypto.lib")
using std::vector;
struct stMd5Info {
	TCHAR szFullPath[MAX_PATH];
	TCHAR szMd5[34];
};

struct stProcName {
	char Name[20];
};
// CKillVirusDlg 对话框
vector<stMd5Info> vecMd5;
IMPLEMENT_DYNAMIC(CKillVirusDlg, CDialogEx)

CKillVirusDlg::CKillVirusDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_KILLVIRUS, pParent)
{

}

CKillVirusDlg::~CKillVirusDlg()
{
}

void CKillVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_KILL, m_ListCtrlKillVirus);
}


BEGIN_MESSAGE_MAP(CKillVirusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FINDFILE, &CKillVirusDlg::OnBnClickedButtonFindfile)
	ON_BN_CLICKED(IDC_BUTTON2, &CKillVirusDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CKillVirusDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CKillVirusDlg 消息处理程序


BOOL CKillVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlKillVirus.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化列表的标题信息(列)，添加指定数量的列
	m_ListCtrlKillVirus.InsertColumn(1, L"名称", LVCFMT_CENTER, 100);
	m_ListCtrlKillVirus.InsertColumn(2, L"MD5", LVCFMT_CENTER, 300);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


int md5_encrypt(const void* data, size_t len, unsigned char* md5)
{
	// 初始化保存 md5 信息的结构体
	MD5_CTX ctx = { 0 };
	MD5_Init(&ctx);

	// 将需要计算的数据传入到对应的结构中
	MD5_Update(&ctx, data, len);

	// 从结构中获取计算后的结果
	MD5_Final(md5, &ctx);

	return 0;
}

int CreateMd5(wchar_t* szFullPath, unsigned char* md5)
{
	WIN32_FIND_DATA FindFileData;
	FindFirstFile(szFullPath, &FindFileData);
	if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		return 0;
	HANDLE hFile = CreateFile(szFullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	char* ch = new char[dwFileSize];
	DWORD dwRealSize = 0;
	ReadFile(hFile, ch, dwFileSize, &dwRealSize, NULL);
	CloseHandle(hFile);
	md5_encrypt(ch, dwFileSize, md5);
	delete[] ch;
	return 1;
}
int y = 0;
DWORD ListAllFileInDirectory1(LPWSTR szPath, CMyListCtrl& m_ListCtrl)
{
	stMd5Info temp;
	unsigned char hex[100] = { 0 };
	wchar_t szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	TCHAR szHex[10] = { 0 };
	TCHAR szMd5[34] = { 0 };
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
			
			
			//	wprintf(L"%s\t", szFullPath);
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//printf("<DIR>");
				ListAllFileInDirectory1(szFullPath, m_ListCtrl);
			}
			int n = CreateMd5(szFullPath, hex);
			if (n == 0)
				goto end;
			for (int i = 0; i < 16; i++)
			{
				_stprintf_s(szHex, 10, _T("%02x"), hex[i]);
				lstrcat(szMd5, szHex);
			}
			m_ListCtrl.InsertItem(y, szBuff);
			m_ListCtrl.SetItemText(y, 1, szMd5);
			lstrcpy(temp.szFullPath, szFullPath);
			lstrcpy(temp.szMd5, szMd5);
			vecMd5.push_back(temp);
			memset(szMd5, 0, 68);
			y++;
end:		y = y;
		} while (FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}

void EnumFile2(CMyListCtrl& m_ListCtrl, LPWSTR szFilePath)
{
	y = 0;
	ListAllFileInDirectory1(szFilePath, m_ListCtrl);
}

wchar_t* Browse1(HWND hWnd)
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
	if (!lstrcmp(szChoose, L""))
	{
		return NULL;
	}
	else
	{
		return szChoose;
	}
}
//选择文件
void CKillVirusDlg::OnBnClickedButtonFindfile()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t szFilePath[0x100] = { 0 };
	wchar_t* szChoose = Browse1(NULL);
	if (szChoose == NULL)
	{
		return;
	}
	lstrcpy(szFilePath, szChoose);
	EnumFile2(m_ListCtrlKillVirus, szFilePath);
}

TCHAR* CKillVirusDlg::AsciiToUnicode(char* str)
{
	DWORD dwNum = 0;
	dwNum = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	TCHAR* pwHostName = new TCHAR[dwNum];
	MultiByteToWideChar(CP_ACP, 0, str, -1, pwHostName, dwNum);
	return pwHostName;
}
//md5查杀
void CKillVirusDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hFile = CreateFile(L"md5.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwSize = GetFileSize(hFile, NULL);
	DWORD dwRealSize = 0;
	char* ch1 = new char[dwSize];
	ReadFile(hFile, ch1, dwSize, &dwRealSize, NULL);
	TCHAR* ch = AsciiToUnicode(ch1);
	TCHAR* tmpCh = ch;
	for (int i = 0; i < vecMd5.size(); i++)
	{
		for (int j = 0; j < dwSize / 32; j++)
		{
			if (!memcmp(vecMd5[i].szMd5, ch, 64))
			{
				DeleteFile(vecMd5[i].szFullPath);
				ch += 32;
			}
		}
	}
	delete[] ch1;
	delete[] tmpCh;
	MessageBox(L"查杀成功!");
}

//黑名单查杀进程
void CKillVirusDlg::KillProcess()
{
	vector<stProcName> vecProcName;
	stProcName temp;
	FILE* fp;
	TCHAR* szName = NULL;
	fopen_s(&fp, "heimingdan.txt", "r+");
	if (!fp)
	{
		MessageBox(L"黑名单文件打开失败!");
		return;
	}
	while (fgets(temp.Name, 20, fp) != NULL)
	{
		int length = strlen(temp.Name);
		//去除\n
		if (temp.Name[length - 1] == '\n')
			temp.Name[length - 1] = 0;
		vecProcName.push_back(temp);
	}
	fclose(fp);

	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS,
		NULL
	);

	PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
	BOOL bSuccess = Process32First(hSnapshot, &pe32);

	if (bSuccess)
	{
		do {

			for (int i = 0; i < vecProcName.size(); i++)
			{
				szName = AsciiToUnicode(vecProcName[i].Name);
				if (!lstrcmp(pe32.szExeFile, szName))
				{
					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
					TerminateProcess(hProcess, 0);
					CloseHandle(hProcess);
				}
				delete[] szName;
			}


		} while (Process32Next(hSnapshot, &pe32));
	}
	MessageBox(L"黑名单查杀成功!");
}

//黑名单查杀进程
void CKillVirusDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	KillProcess();
}
