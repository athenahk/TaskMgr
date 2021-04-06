#pragma once
#include"CPe.h"
#include"CExportDlg.h"
#include"CImportDlg.h"
#include"CRelocaDlg.h"
#include"CResDlg.h"
#include"CTlsDlg.h"
#include"CDelayDlg.h"
// CDataDirDlg 对话框

class CDataDirDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDataDirDlg)

public:
	CPe* m_Pe;
	CDataDirDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CDataDirDlg(CPe* Pe, CWnd* pParent = nullptr);
	virtual ~CDataDirDlg();
	void InitDataDir();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATADIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
