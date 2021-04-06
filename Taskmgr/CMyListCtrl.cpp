// CMyListCtrl.cpp: 实现文件
//

#include "pch.h"
#include "ProcessExlpore.h"
#include "CMyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序

void CMyListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	SetExtendedStyle(LVS_EX_CHECKBOXES |       // 设置列表框属性第一列有Checkbox     
		LVS_EX_FULLROWSELECT |    // 设置列样式表框属性可以选中整行
		LVS_EX_GRIDLINES 		  // 设置列表框有表格样式
	);
	CListCtrl::PreSubclassWindow();
}


void CMyListCtrl::InsertCol(DWORD dwCount, ...)
{
	va_list argptr;
	va_start(argptr, dwCount);
	for (DWORD i = 0; i < dwCount; i++)
	{
		TCHAR* pStrTabName = va_arg(argptr, TCHAR*);//列名
		DWORD  dwWidth = va_arg(argptr, UINT);  //列宽
		InsertColumn(i, pStrTabName, 0, dwWidth);
	}
	va_end(argptr);
	m_dwColCount = dwCount;
}


void CMyListCtrl::InsertOnLineItem(DWORD dwCount, ...)
{
	va_list argptr;
	va_start(argptr, dwCount);
	TCHAR* pStrItemName = va_arg(argptr, TCHAR*);//第一列
	InsertItem(m_dwItemCount, pStrItemName);
	for (DWORD i = 1; i < dwCount; i++)
	{
		TCHAR* pStrItemName = va_arg(argptr, TCHAR*);//第n列
		SetItemText(m_dwItemCount, i, pStrItemName);
	}
	va_end(argptr);
	m_dwItemCount++;
}

