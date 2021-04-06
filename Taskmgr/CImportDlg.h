#pragma once
#include"CPe.h"
#include"data.h"
#include<vector>
#include"CMyListCtrl.h"
#include"Resource.h"
#include"Func.h"
using std::vector;
// CImportDlg 对话框

class CImportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImportDlg)

public:
	CImportDlg(CWnd* pParent = nullptr);   // 标准构造函数
	CImportDlg(CPe* Pe, CWnd* pParent = nullptr);
	virtual ~CImportDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CPe* m_Pe;
	CMyListCtrl m_ListCtrlImport1;
	CMyListCtrl m_ListCtrlImport2;
	vector<ImportInfo> vecInfo1;
	vector<vector<ImportInfo2>> vecInfo2;
	void InitImport1();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListImport1(NMHDR* pNMHDR, LRESULT* pResult);
};
