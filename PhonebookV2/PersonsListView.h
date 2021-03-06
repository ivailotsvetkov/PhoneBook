#pragma once
#include "PersonsDoc.h"
#include "PersonsDialog.h"
#include "afxcview.h"


// CPersonsListView view

class CPersonsListView : public CListView
{
	DECLARE_DYNCREATE(CPersonsListView)

public:
	CPersonsListView();           // protected constructor used by dynamic creation
	virtual ~CPersonsListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;

	virtual void Dump(CDumpContext& dc) const;
public:
	CCitiesPtrArray m_CitiesPtrArray;
	CPersonsDoc * GetDocument() const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	CPERSONWITHPHONENUMBERS* m_CPersonWithPhoneNumbers;
	CMap<int, int, CITIES*, CITIES*> mapCities;
	void OnInitialUpdate();
	void OnCreatingColumns();
	void OnInsertingAllItems();

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnDraw(CDC* /*pDC*/);

	//Operations
	/// <summary>Метод за Double-Click</summary>
	afx_msg void OnLButtonDblClk(UINT flags, CPoint pt);
	/// <summary>Метод за Insert на нов ред в листа</summary>
	afx_msg void OnPopupInsert();
	/// <summary>Метод за Delete на ред в листа</summary>
	afx_msg void OnPopupDelete();
	/// <summary>Метод за Edit на ред в листа</summary>
	afx_msg void OnPopupEdit();
#ifndef _DEBUG  // debug version in PhonebookV2View.cpp
	inline CPhonebookV2Doc* CPhonebookV2View::GetDocument() const
	{
		return reinterpret_cast<CPhonebookV2Doc*>(m_pDocument);
	}
#endif
};


