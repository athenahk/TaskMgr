#pragma once
#include"CMyListCtrl.h"
#include"CPe.h"
#include"pch.h"

// CExportDlg 对话框

class CExportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExportDlg)

public:
	CExportDlg(CWnd* pParent = nullptr); // 标准构造函数
	CExportDlg(CPe* pe, CWnd* pParent = nullptr);
	virtual ~CExportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CPe* m_Pe;
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrlExport;
	void InitExport();
	void InitListCtrl();
	virtual BOOL OnInitDialog();
};
