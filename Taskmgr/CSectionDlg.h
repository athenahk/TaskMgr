#pragma once
#include"CMyListCtrl.h"
#include"CPe.h"
#include"Resource.h"
// CSectionDlg 对话框

class CSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSectionDlg)

public:
	CSectionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CSectionDlg(CPe* Pe,CWnd* pParent = nullptr);
	virtual ~CSectionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CPe* m_Pe;
	CMyListCtrl m_MyListCtrl;
	virtual BOOL OnInitDialog();
};
