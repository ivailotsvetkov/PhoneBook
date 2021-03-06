#pragma once
#include "CitiesDoc.h"
#include "CitiesDialog.h"
#include "afxcview.h"

/// <summary>Клас за работа с листа CITIES</summary>
class CCitiesListView : public CListView
{
	//Constructor/Destructor
protected:
	CCitiesListView();
	virtual ~CCitiesListView();

	DECLARE_DYNCREATE(CCitiesListView)

	// Attributes
public:
	CCitiesDoc * GetDocument() const;

	// Overrides
private:
	void OnInitialUpdate();
	void OnContextMenu(CWnd *, CPoint point);
	void OnCreatingColumns();
	void OnInsertingAllItems();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()


	//Operations
public:
	/// <summary>Метод за Double-Click</summary>
	afx_msg void OnLButtonDblClk(UINT flags, CPoint pt);
	/// <summary>Метод за Insert на нов ред в листа</summary>
	afx_msg void OnPopupInsert();
	/// <summary>Метод за Delete на ред в листа</summary>
	afx_msg void OnPopupDelete();
	/// <summary>Метод за Edit на ред в листа</summary>
	afx_msg void OnPopupEdit();
};

#ifndef _DEBUG  // debug version in PhonebookV2View.cpp
inline CPhonebookV2Doc* CPhonebookV2View::GetDocument() const
{
	return reinterpret_cast<CPhonebookV2Doc*>(m_pDocument);
}
#endif

