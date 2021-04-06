#pragma once


// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
private:
	typedef struct _ITEM_COLOR // 行颜色
	{
		COLORREF clrtextColor; // 文本颜色 
		COLORREF clrBkColor;   // 背景颜色
		_ITEM_COLOR() :clrtextColor(RGB(0, 0, 0)), // 默认文本黑色，背景白色  
			clrBkColor(RGB(255, 255, 255))
		{
		}
	}ITEM_COLOR, * PITEM_COLOR;
public:
	virtual void PreSubclassWindow();	//初始化之前调用。可以在此修改列表样式

	//afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

	void InsertCol(DWORD dwCount, ...);
	void InsertOnLineItem(DWORD dwCount, ...);
	//void SetItemColor(DWORD dwIndex,COLORREF clrTextColor=RGB(0,0,0),COLORREF clrBkColor=RGB(255,255,255));
	//int m_nItem;
	DWORD m_dwColCount;
	DWORD m_dwItemCount;
	//vector<ITEM_COLOR> m_vecItemColor;

};


