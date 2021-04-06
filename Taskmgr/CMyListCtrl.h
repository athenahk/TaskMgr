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
	typedef struct _ITEM_COLOR // ����ɫ
	{
		COLORREF clrtextColor; // �ı���ɫ 
		COLORREF clrBkColor;   // ������ɫ
		_ITEM_COLOR() :clrtextColor(RGB(0, 0, 0)), // Ĭ���ı���ɫ��������ɫ  
			clrBkColor(RGB(255, 255, 255))
		{
		}
	}ITEM_COLOR, * PITEM_COLOR;
public:
	virtual void PreSubclassWindow();	//��ʼ��֮ǰ���á������ڴ��޸��б���ʽ

	//afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);

	void InsertCol(DWORD dwCount, ...);
	void InsertOnLineItem(DWORD dwCount, ...);
	//void SetItemColor(DWORD dwIndex,COLORREF clrTextColor=RGB(0,0,0),COLORREF clrBkColor=RGB(255,255,255));
	//int m_nItem;
	DWORD m_dwColCount;
	DWORD m_dwItemCount;
	//vector<ITEM_COLOR> m_vecItemColor;

};


