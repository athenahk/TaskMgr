// CHeapDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CHeapDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <TlHelp32.h>


// CHeapDlg 对话框

IMPLEMENT_DYNAMIC(CHeapDlg, CDialogEx)

CHeapDlg::CHeapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HEAP, pParent)
{

}

CHeapDlg::CHeapDlg(DWORD dwPid, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_HEAP, pParent)
{
	this->dwPid = dwPid;
}

CHeapDlg::~CHeapDlg()
{
}

void CHeapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HEAP, m_ListCtrlHeap);
}


BEGIN_MESSAGE_MAP(CHeapDlg, CDialogEx)
END_MESSAGE_MAP()


// CHeapDlg 消息处理程序

void EnumHeap(DWORD dwPid, CMyListCtrl& m_ListCtrlHeap)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, dwPid);
	TCHAR szBuff[0x100] = { 0 };
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		//_tprintf(L"%d\n", GetLastError());
		return;
	}

	HEAPLIST32 hl = { 0 };
	hl.dwSize = sizeof(hl);
	Heap32ListFirst(hSnapshot, &hl);
	int i = 0;
	do {
		//_tprintf(L"------------------------------------------------\n");
		//_tprintf(TEXT("ProcessID=%d,HeapID=%d\n"), hl.th32ProcessID, hl.th32HeapID);
		_stprintf_s(szBuff, 0x100, L"0x%08x", hl.th32HeapID);
		m_ListCtrlHeap.InsertItem(i, szBuff);
			_stprintf_s(szBuff, 0x100, L"%d", hl.dwSize);
			m_ListCtrlHeap.SetItemText(i, 1, szBuff);
	} while (Heap32ListNext(hSnapshot, &hl));
	
}
BOOL CHeapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ListCtrlHeap.InsertColumn(1, L"HeapId", LVCFMT_CENTER, 100);
	m_ListCtrlHeap.InsertColumn(2, L"堆大小", LVCFMT_CENTER, 200);
	
	EnumHeap(dwPid, m_ListCtrlHeap);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
