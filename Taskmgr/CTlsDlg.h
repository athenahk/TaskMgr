#pragma once
#include"CPe.h"

// CTlsDlg 对话框

class CTlsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTlsDlg)

public:
	CPe* m_Pe;
	CTlsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CTlsDlg(CPe* Pe, CWnd* pParent = nullptr);
	virtual ~CTlsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TLS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
