#pragma once
#include"CPe.h"
#include"data.h"
#include"Func.h"
// CResDlg 对话框

class CResDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResDlg)

public:
	CPe* m_Pe;
	CResDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CResDlg(CPe* pe, CWnd* pParent = nullptr);
	virtual ~CResDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_TreeCtrlRes;
	virtual BOOL OnInitDialog();
	vector<ResInfo> vecResInfo;
	vector<vector<ResInfo2>> vecResInfo2;
	afx_msg void OnNMClickTreeRes(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_szResRva;
	CString m_szResOffset;
	CString m_szResSize;
};
