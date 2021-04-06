#pragma once
#include"CPe.h"

// CDelayDlg 对话框

class CDelayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelayDlg)

public:
	CDelayDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CDelayDlg(CPe* pe, CWnd* pParent = nullptr);
	virtual ~CDelayDlg();
	CPe* m_Pe;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
