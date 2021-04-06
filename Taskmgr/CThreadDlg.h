#pragma once
#include "CMyListCtrl.h"
#include<vector>
using std::vector;

// CThreadDlg 对话框

class CThreadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThreadDlg)

public:
	CThreadDlg(CWnd* pParent = nullptr);// 标准构造函数
	CThreadDlg(DWORD dwPid,CWnd* pParent = nullptr); 
	virtual ~CThreadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DWORD dwPid;
public:
	CMyListCtrl m_ListCtrlThread;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRClickListThread(NMHDR* pNMHDR, LRESULT* pResult);
	vector<DWORD> m_vecTid;
	afx_msg void OnClickedResumeThread();
	afx_msg void OnClickResumeThread();
	afx_msg void OnClickExitThread();
//	afx_msg void OnLvnItemchangedListThread(NMHDR* pNMHDR, LRESULT* pResult);
};
