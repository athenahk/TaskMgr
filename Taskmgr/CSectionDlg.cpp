// CSectionDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CSectionDlg.h"
#include "afxdialogex.h"


// CSectionDlg 对话框

IMPLEMENT_DYNAMIC(CSectionDlg, CDialogEx)

CSectionDlg::CSectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SECTION, pParent)
{

}
CSectionDlg::CSectionDlg(CPe* Pe,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SECTION, pParent)
{
	m_Pe = Pe;
}


CSectionDlg::~CSectionDlg()
{
}

void CSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECTION, m_MyListCtrl);
}


BEGIN_MESSAGE_MAP(CSectionDlg, CDialogEx)
END_MESSAGE_MAP()


// CSectionDlg 消息处理程序
void EnumSection(CMyListCtrl& m_MyListCtrl, CPe** Pe)
{

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)(*Pe)->m_pBuf;
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((*Pe)->m_pBuf + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);
	//wchar_t str[20] = { 0 };
	for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++)
	{
		CString str(pSectionHeader[i].Name);
		//_stprintf_s(str, 20, L"%s", pSectionHeader[i].Name);
		m_MyListCtrl.InsertItem(i, str);
		//printf("Name: %s\n", pSectionHeader[i].Name);
		//_stprintf_s(str, 20, L"%d", pSectionHeader[i].VirtualAddress);
		str.Format(L"0x%08x", pSectionHeader[i].VirtualAddress);
		m_MyListCtrl.SetItemText(i, 1, str);
		//printf("VirtualAddress: %x\n", pSectionHeader[i].VirtualAddress);
		str.Format(L"0x%08x", pSectionHeader[i].Misc.VirtualSize);
		m_MyListCtrl.SetItemText(i, 2, str);
		//节在文件中对齐后的大小
		str.Format(L"0x%08x", pSectionHeader[i].PointerToRawData);
		m_MyListCtrl.SetItemText(i, 3, str);
		//printf("SizeOfRawData: %x\n", pSectionHeader[i].SizeOfRawData);
		str.Format(L"0x%08x", pSectionHeader[i].SizeOfRawData);
		m_MyListCtrl.SetItemText(i, 4, str);
		str.Format(L"0x%08x", pSectionHeader[i].Characteristics);
		m_MyListCtrl.SetItemText(i, 5, str);
		//printf("PointerOfRawData: %x\n", pSectionHeader[i].PointerToRawData);
		//未对齐节的大小
	//	printf("VirtualSize: %x\n", pSectionHeader[i].Misc.VirtualSize);
	}
	/*m_MyListCtrl.InsertItem(0, L"0x04", 0);
	m_MyListCtrl.SetItemText(0, 1, L"qq.exe");
	m_MyListCtrl.SetItemText(0, 2, L"C:\\app\\qq.exe");
	m_MyListCtrl.InsertItem(1, L"0x08", 1);
	m_MyListCtrl.SetItemText(1, 1, L"wechat.exe");
	m_MyListCtrl.SetItemText(1, 2, L"C:\\app\\wechat.exe");
	m_MyListCtrl.InsertItem(2, L"0x0C", 2);
	m_MyListCtrl.SetItemText(2, 1, L"tim.exe");
	m_MyListCtrl.SetItemText(2, 2, L"C:\\app\\tim.exe");*/
}

BOOL CSectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_MyListCtrl.InsertColumn(1, L"名称", LVCFMT_CENTER, 100);
	m_MyListCtrl.InsertColumn(2, L"RVA", LVCFMT_CENTER, 100);
	m_MyListCtrl.InsertColumn(3, L"VSize", LVCFMT_CENTER, 100);
	m_MyListCtrl.InsertColumn(4, L"FOA", LVCFMT_CENTER, 100);
	m_MyListCtrl.InsertColumn(5, L"RSize", LVCFMT_CENTER, 100);
	m_MyListCtrl.InsertColumn(6, L"标志", LVCFMT_CENTER, 100);
	EnumSection(m_MyListCtrl, &m_Pe);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
