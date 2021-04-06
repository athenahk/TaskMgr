// CResDlg.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CResDlg.h"
#include "afxdialogex.h"


// CResDlg 对话框

IMPLEMENT_DYNAMIC(CResDlg, CDialogEx)

CResDlg::CResDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RES, pParent)
	, m_szResRva(_T(""))
	, m_szResOffset(_T(""))
	, m_szResSize(_T(""))
{

}
CResDlg::CResDlg(CPe* pe, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_RES, pParent)

{
	m_Pe = pe;
}

CResDlg::~CResDlg()
{
}

void CResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_Res, m_TreeCtrlRes);
	DDX_Text(pDX, IDC_EDIT_RESRVA, m_szResRva);
	DDX_Text(pDX, IDC_EDIT_RESOFFSET, m_szResOffset);
	DDX_Text(pDX, IDC_EDIT_RESSIZE, m_szResSize);
}


BEGIN_MESSAGE_MAP(CResDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE_Res, &CResDlg::OnNMClickTreeRes)
END_MESSAGE_MAP()


// CResDlg 消息处理程序


BOOL CResDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	long flag = 0;
	int n = 0, m = 0;
	// TODO:  在此添加额外的初始化
	AnalyzeRes(m_Pe->m_pBuf, vecResInfo, vecResInfo2);
	for (int i = 0; i < vecResInfo.size(); i++)
	{
		CString szName(vecResInfo[i].szName);
		HTREEITEM ItemLevel12 = m_TreeCtrlRes.InsertItem(szName);
		for (int j = 0; j < vecResInfo2[i].size(); j++)
		{
			/*CString* pNodeData = new CString;
			(*pNodeData).Format(L"%d", flag);
			flag++;*/
			m_TreeCtrlRes.InsertItem(vecResInfo2[i][j].szName, ItemLevel12);
			//n = m_TreeCtrlRes.SetItemData(ItemLevel12, (DWORD_PTR)pNodeData);

		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CResDlg::OnNMClickTreeRes(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//CPoint point;
	//GetCursorPos(&point);//获得鼠标点击的位置
	//m_TreeCtrlRes.ScreenToClient(&point);//转化为客户坐标
	//UINT uFlags;

	//HTREEITEM CurrentItem;
	//CurrentItem = m_TreeCtrlRes.HitTest(point, &uFlags);//获得当前点击节点的ITEM
 //  //获得该节点的父节点
	//HTREEITEM ParentItem=m_videotree.GetParentItem(CurrentItem);
	//CString CurrentVideo = m_TreeCtrlRes.GetItemText(CurrentItem);//获得节点值
	//HTREEITEM hItem = m_TreeCtrlRes.GetSelectedItem();
	////long n = m_TreeCtrlRes.GetItemData(hItem);
	//CString* data = (CString*)m_TreeCtrlRes.GetItemData(hItem);
	CString szStr;
	CString tmp = m_TreeCtrlRes.GetItemText(m_TreeCtrlRes.GetSelectedItem());
	for (int i = 0; i < vecResInfo2.size(); i++)
	{
		for (int j = 0; j < vecResInfo2[i].size(); j++)
		{
			if (!wcscmp(vecResInfo2[i][j].szName, tmp))
			{
				m_szResRva.Format(L"%08x", vecResInfo2[i][j].Rva);
				m_szResOffset.Format(L"%08x", vecResInfo2[i][j].Foa);
				m_szResSize.Format(L"%08x", vecResInfo2[i][j].Size);
				UpdateData(FALSE);
				goto end;
				
			}
		}
	}
end:
	*pResult = 0;
}
