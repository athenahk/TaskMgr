#pragma once
#include "CMyListCtrl.h"

// CHeapDlg 对话框

class CHeapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHeapDlg)

public:
	
	CHeapDlg(CWnd* pParent = nullptr);// 标准构造函数
	CHeapDlg(DWORD dwPid, CWnd* pParent = nullptr);
	virtual ~CHeapDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HEAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DWORD dwPid;
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrlHeap;
	virtual BOOL OnInitDialog();
};
