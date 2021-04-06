#pragma once
#include "CMyListCtrl.h"

// CWindowDlg 对话框

class CWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWindowDlg)

public:
	CWindowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CWindowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WINDOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
		CMyListCtrl m_ListCtrlWnd;
		CImageList m_ImageList;
	//CMyListCtrl m_ListCtrlWnd;
	//CImageList m_ImageList;
	virtual BOOL OnInitDialog();
};

struct srt {
	CMyListCtrl& m_ListCtrl;
	CImageList& m_ImageList;
};