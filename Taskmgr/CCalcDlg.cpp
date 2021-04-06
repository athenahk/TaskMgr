// CCalcDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CCalcDlg.h"
#include "afxdialogex.h"


// CCalcDlg 对话框

IMPLEMENT_DYNAMIC(CCalcDlg, CDialogEx)

CCalcDlg::CCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CALC, pParent)
	, m_szVA(_T(""))
	, m_szRVA(_T(""))
	, m_szFOA(_T(""))
	, m_szSectionName(_T(""))
	, m_szBytes(_T(""))
{

}

CCalcDlg::CCalcDlg(CPe* pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_CALC, pParent)
	, m_szVA(_T(""))
	, m_szRVA(_T(""))
	, m_szFOA(_T(""))
	, m_szSectionName(_T(""))
	, m_szBytes(_T(""))
{
	m_Pe = pe;
}

CCalcDlg::~CCalcDlg()
{
}

void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VA, m_EditVA);
	DDX_Text(pDX, IDC_EDIT_VA, m_szVA);
	DDX_Control(pDX, IDC_EDIT_RVA, m_EditRVA);
	DDX_Text(pDX, IDC_EDIT_RVA, m_szRVA);
	DDX_Control(pDX, IDC_EDIT_FOA, m_EditFOA);
	DDX_Text(pDX, IDC_EDIT_FOA, m_szFOA);
	DDX_Text(pDX, IDC_EDIT_SECINFO, m_szSectionName);
	DDX_Text(pDX, IDC_EDIT_DATAINFO, m_szBytes);
}


BEGIN_MESSAGE_MAP(CCalcDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_VA, &CCalcDlg::OnBnClickedButtonVa)
	ON_BN_CLICKED(IDC_BUTTON_RVA, &CCalcDlg::OnBnClickedButtonRva)
	ON_BN_CLICKED(IDC_BUTTON3, &CCalcDlg::OnBnClickedButton3)
	ON_EN_UPDATE(IDC_EDIT_VA, &CCalcDlg::OnEnUpdateEditVa)
	ON_EN_UPDATE(IDC_EDIT_RVA, &CCalcDlg::OnEnUpdateEditRva)
	ON_EN_UPDATE(IDC_EDIT_FOA, &CCalcDlg::OnEnUpdateEditFoa)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CCalcDlg::OnBnClickedButtonCalc)
	//ON_EN_CHANGE(IDC_EDIT_DATAINFO, &CCalcDlg::OnEnChangeEditDatainfo)
END_MESSAGE_MAP()


// CCalcDlg 消息处理程序


BOOL CCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_EditVA.SetReadOnly(TRUE);
	m_EditVA.SetLimitText(8);

	m_EditFOA.SetReadOnly(TRUE);
	m_EditFOA.SetLimitText(8);

	m_EditRVA.SetLimitText(8);
	// 设置编辑框焦点位置
	m_EditRVA.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCalcDlg::OnBnClickedButtonVa()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditVA.SetReadOnly(FALSE);
	m_EditRVA.SetReadOnly(TRUE);
	m_EditFOA.SetReadOnly(TRUE);
	m_szRVA = _T("");
	m_szVA = _T("");
	m_szFOA = _T("");
	m_szSectionName = _T("");
	m_szBytes = _T("");
	m_EditVA.SetFocus();

	UpdateData(FALSE);
}


void CCalcDlg::OnBnClickedButtonRva()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditVA.SetReadOnly(TRUE);
	m_EditRVA.SetReadOnly(FALSE);
	m_EditFOA.SetReadOnly(TRUE);
	m_szRVA = _T("");
	m_szVA = _T("");
	m_szFOA = _T("");
	m_szSectionName = _T("");
	m_szBytes = _T("");
	m_EditRVA.SetFocus();

	UpdateData(FALSE);
}


//foa
void CCalcDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_EditVA.SetReadOnly(TRUE);
	m_EditRVA.SetReadOnly(TRUE);
	m_EditFOA.SetReadOnly(FALSE);
	m_szRVA = _T("");
	m_szVA = _T("");
	m_szFOA = _T("");
	m_szSectionName = _T("");
	m_szBytes = _T("");
	m_EditFOA.SetFocus();

	UpdateData(FALSE);
}

void CCalcDlg::InputControl(CEdit* pEdit, CString& str)
{
	// TODO: 在此处添加实现代码.
	DWORD len = str.GetLength();

	TCHAR* sz = str.GetBuffer();
	DWORD TMP = 0;
	if ((sz[len - 1] >= '0' && sz[len - 1] <= '9') || (sz[len - 1] >= 'A' && sz[len - 1] <= 'F'))
	{
		// 把字符转为数字
		switch (sz[len - 1])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			TMP = sz[len - 1] - '0';
		}
		break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		{
			TMP = sz[len - 1] - 0x37;
		}
		break;
		default:
			break;
		}
		str = sz;
	}
	else
	{
		sz[len - 1] = 0;
		str = sz;
	}
	UpdateData(FALSE);
	int nLength = str.GetLength();
	pEdit->SetSel(nLength, nLength, FALSE);
	pEdit->SetFocus();
}

void CCalcDlg::OnEnUpdateEditVa()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	InputControl(&m_EditVA, m_szVA);
}


void CCalcDlg::OnEnUpdateEditRva()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	InputControl(&m_EditRVA, m_szRVA);
}


void CCalcDlg::OnEnUpdateEditFoa()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数，以将 EM_SETEVENTMASK 消息发送到该控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	InputControl(&m_EditFOA, m_szFOA);
}



void CCalcDlg::OnBnClickedButtonCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_Pe->InitVectorSec();
	DWORD RVA = 0, VA = 0, FOA = 0;
	DWORD dwRet = 0;
	if (!m_szRVA.IsEmpty())
	{
		// 把CString 转为HEX
		RVA = m_Pe->CstringToHex(m_szRVA);
		char szSectionName[9] = { 0 };
		dwRet = m_Pe->CalcFromRva(RVA, FOA, VA, szSectionName);

		if (ERROR_OUT_OF_RANGE == dwRet)
		{
			MessageBox(_T("超出范围"));
			return;
		}
		m_szVA.Format(_T("%08X"), VA);
		m_szRVA.Format(_T("%08X"), RVA);
		m_szFOA.Format(_T("%08X"), FOA);
		m_szSectionName = szSectionName;
		DWORD dwBuff = (DWORD)m_Pe->m_pBuf + FOA;
		for (DWORD i = 0; i < 16; i++)
		{
			CString str;
			str.Format(_T("%X"), *(byte*)((byte*)dwBuff + i));
			m_szBytes = m_szBytes + str + _T(" ");
		}
		UpdateData(FALSE);
		return;
	}
	if (!m_szVA.IsEmpty())
	{
		// 把CString 转为HEX
		VA = m_Pe->CstringToHex(m_szVA);
		char szSectionName[9] = { 0 };
		dwRet = m_Pe->CalcFromVa(VA, RVA, FOA, szSectionName);
		if (ERROR_OUT_OF_RANGE == dwRet)
		{
			MessageBox(_T("超出范围"));
			return;
		}
		m_szVA.Format(_T("%08X"), VA);
		m_szRVA.Format(_T("%08X"), RVA);
		m_szFOA.Format(_T("%08X"), FOA);
		//m_szSectionName = szSectionName;
		m_szSectionName = szSectionName;
		DWORD dwBuff = (DWORD)m_Pe->m_pBuf + FOA;
		for (DWORD i = 0; i < 16; i++)
		{
			CString str;
			str.Format(_T("%X"), *(byte*)((byte*)dwBuff + i));
			m_szBytes = m_szBytes + str + _T(" ");
		}
		UpdateData(FALSE);
		return;
	}
	if (!m_szFOA.IsEmpty())
	{
		// 把CString 转为HEX
		FOA = m_Pe->CstringToHex(m_szFOA);
		
		char szSectionName[9] = { 0 };
		dwRet = m_Pe->CalcFromFoa(FOA, RVA, VA, szSectionName);
		if (ERROR_OUT_OF_RANGE == dwRet)
		{
			MessageBox(_T("超出范围"));
			return;
		}
		m_szVA.Format(_T("%08X"), VA);
		m_szRVA.Format(_T("%08X"), RVA);
		m_szFOA.Format(_T("%08X"), FOA);
		m_szSectionName = szSectionName;
		DWORD dwBuff = (DWORD)m_Pe->m_pBuf + FOA;
		for (DWORD i = 0; i < 16; i++)
		{
			CString str;
			str.Format(_T("%X"), *(byte*)((byte*)dwBuff + i));
			m_szBytes = m_szBytes + str + _T(" ");
		}
		UpdateData(FALSE);
		//m_szSectionName = szSectionName;
		return;
	}
}


//void CCalcDlg::OnEnChangeEditDatainfo()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
