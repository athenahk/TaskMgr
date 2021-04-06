#pragma once
#include"data.h"
#include"CPe.h"
#include"CMyListCtrl.h"
#include"Resource.h"
#include<vector>
using std::vector;

// CRelocaDlg 对话框

class CRelocaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRelocaDlg)

public:
	CPe* m_Pe;
	CRelocaDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CRelocaDlg(CPe* pe, CWnd* pParent = nullptr);
	virtual ~CRelocaDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELOCATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrlReloca1;
	CMyListCtrl m_ListCtrlReloca2;
	vector< RelocaInfo> m_vecRelocaInfo;
	vector<vector<RelocaInfo2>> m_vecRelocaInfo2;
	void InitReloca();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListReloca1(NMHDR* pNMHDR, LRESULT* pResult);
};
