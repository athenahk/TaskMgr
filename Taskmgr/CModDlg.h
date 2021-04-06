#pragma once
#include "Resource.h"
#include "CMyListCtrl.h"

// CModDlg 对话框

class CModDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModDlg)

public:
	CModDlg(CWnd* pParent = nullptr);
	CModDlg(DWORD dwPid, CWnd* pParent = nullptr);// 标准构造函数
	virtual ~CModDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DWORD dwPid;
public:
	CMyListCtrl m_ListCtrlMod;
	virtual BOOL OnInitDialog();
};
