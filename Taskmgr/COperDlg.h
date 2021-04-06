#pragma once


// COperDlg 对话框

class COperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COperDlg)

public:
	COperDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COperDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
