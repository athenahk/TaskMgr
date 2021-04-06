
// ProcessExlporeDlg.h: 头文件
//

#pragma once
#include<vector>
#include "CMyListCtrl.h"
#include "CPeDlg.h"
using std::vector;

// CProcessExlporeDlg 对话框
class CProcessExlporeDlg : public CDialogEx
{
// 构造
public:
	CProcessExlporeDlg(CWnd* pParent = nullptr);	// 标准构造函数
	BOOL m_IsWindowHide;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSEXLPORE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrl;
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMRClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewThread();
	afx_msg void OnViewModule();
	CStatusBar m_StatusBar;
	vector<DWORD>m_vecPID;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
	afx_msg LRESULT OnTimeCpu(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickExitProc();
protected:
//	afx_msg LRESULT OnUserClickExitThread(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClickEnumHeap();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButtonHuishou();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnInjectDLL();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButtonHotkey();
//	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
