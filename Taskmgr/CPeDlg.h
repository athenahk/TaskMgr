#pragma once
#include "CPe.h"
#include"CSectionDlg.h"
#include "CDataDirDlg.h"
#include "CCalcDlg.h"
// CPeDlg 对话框

class CPeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPeDlg)

public:
	CPeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CPe m_Pe;
	CButton m_Section;
	CButton m_DataDir;
	CButton m_Calc;
	CButton m_Time;
	void ShowFileHeader();
	void ShowOpHeader();
	afx_msg void OnBnClickedButton10();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
};
