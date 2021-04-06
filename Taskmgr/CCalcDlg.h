#pragma once
#include"CPe.h"
#include "resource.h"
// CCalcDlg 对话框

class CCalcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalcDlg)

public:
	CPe* m_Pe;
	CCalcDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CCalcDlg(CPe* pe, CWnd* pParent = nullptr);
	virtual ~CCalcDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_EditVA;
	CString m_szVA;
	CEdit m_EditRVA;
	CString m_szRVA;
	CEdit m_EditFOA;
	CString m_szFOA;
	afx_msg void OnBnClickedButtonVa();
	afx_msg void OnBnClickedButtonRva();
	afx_msg void OnBnClickedButton3();
	void InputControl(CEdit* pEdit, CString& str);
	afx_msg void OnEnUpdateEditVa();
	afx_msg void OnEnUpdateEditRva();
	afx_msg void OnEnUpdateEditFoa();
	afx_msg void OnBnClickedButtonCalc();

//	afx_msg void OnEnChangeEditDatainfo();
	CString m_szSectionName;
	CString m_szBytes;
};
