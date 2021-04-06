#pragma once
#include "CMyListCtrl.h"

// CKillVirusDlg 对话框

class CKillVirusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CKillVirusDlg)

public:
	CKillVirusDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CKillVirusDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_KILLVIRUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CMyListCtrl m_ListCtrlKillVirus;
	afx_msg void OnBnClickedButtonFindfile();
	TCHAR* AsciiToUnicode(char* str);
	void KillProcess();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
