#pragma once
#include"CMyListCtrl.h"
#include<vector>
using std::vector;
// CServiceDlg 对话框

class CServiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServiceDlg)

public:
	CServiceDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CServiceDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrlService;
	virtual BOOL OnInitDialog();
	void InitService();
	vector<CString> m_vecSerName;
	afx_msg void OnNMRClickListService(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartService();
	afx_msg void OnCloseService();
};
