// CWindowDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CWindowDlg.h"
#include "afxdialogex.h"
#include <locale.h>


// CWindowDlg 对话框

IMPLEMENT_DYNAMIC(CWindowDlg, CDialogEx)

CWindowDlg::CWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WINDOW, pParent)
{

}

CWindowDlg::~CWindowDlg()
{
}

void CWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WINDOW, m_ListCtrlWnd);
}


BEGIN_MESSAGE_MAP(CWindowDlg, CDialogEx)
END_MESSAGE_MAP()


// CWindowDlg 消息处理程序


BOOL CALLBACK EnumWinProc(HWND hWnd, LPARAM lParam)
{
	static int i = 0;
	TCHAR buff[200];
	CMyListCtrl* pLparam = (CMyListCtrl*)lParam;
	setlocale(LC_ALL, "chs");
	GetWindowText(hWnd, buff, 200);
	if (IsWindowVisible(hWnd) == TRUE && wcslen(buff) != 0)
	{
		//_tprintf(_T("%s\n"), buff);
		pLparam->InsertItem(i, buff);
	}
	return true;
}

BOOL CWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 初始化图片列表，前两个元素描述的是图片的宽度和高度，第三个元素
	//	用于指定图片支持的颜色，最后两个参数是初始化的图片个数，以及创建的个数
	m_ImageList.Create(32, 32, ILC_COLOR32, 4, 0);

	// 将图片列表绑定到列表控件上
	m_ListCtrlWnd.SetImageList(&m_ImageList, LVSIL_SMALL);


	m_ListCtrlWnd.InsertColumn(1, L"窗口名", LVCFMT_CENTER, 500);
	EnumWindows(&EnumWinProc, (LPARAM)(&m_ListCtrlWnd));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
