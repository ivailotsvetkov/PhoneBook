
// PhonebookV2View.cpp : implementation of the CPhonebookV2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhonebookV2.h"
#endif


#include "CitiesListView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhonebookV2View

IMPLEMENT_DYNCREATE(CCitiesListView, CListView)

BEGIN_MESSAGE_MAP(CCitiesListView, CListView)
	// Standard printing commands
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_POPUP_INSERT, &CCitiesListView::OnPopupInsert)
	ON_COMMAND(ID_POPUP_DELETE, &CCitiesListView::OnPopupDelete)
	ON_COMMAND(ID_POPUP_EDIT, &CCitiesListView::OnPopupEdit)
END_MESSAGE_MAP()

// CPhonebookV2View construction/destruction
CCitiesListView::CCitiesListView()
{
}

CCitiesListView::~CCitiesListView()
{
}

BOOL CCitiesListView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL;

	return CListView::PreCreateWindow(cs);
}

// CPhonebookV2View drawing

void CCitiesListView::OnDraw(CDC* /*pDC*/)
{
	CCitiesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CCitiesListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	OnCreatingColumns();
	OnInsertingAllItems();
}
// CPhonebookV2View printing
void CCitiesListView::OnContextMenu(CWnd*, CPoint point)
{
	// Load the desired menu
	CMenu mnuPopupSubmit;
	mnuPopupSubmit.LoadMenu(IDR_MENUCITIES);

	// Get a pointer to the button
	CListCtrl& oCListCtrl = GetListCtrl();

	// Find the rectangle around the button
	CRect rectMenu;
	oCListCtrl.GetWindowRect(rectMenu);

	// Get a pointer to the first item of the menu
	CMenu *mnuPopupMenu = mnuPopupSubmit.GetSubMenu(0);
	ASSERT(mnuPopupMenu);

	// Find out if the user right-clicked the button
	// because we are interested only in the button
	if (rectMenu.PtInRect(point)) // Since the user right-clicked the button, display the context menu
		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CCitiesListView::OnCreatingColumns()
{
	// this code only works for a report-mode list view
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	// Insert a column. This override is the most convenient.

	LVCOLUMN colCity;
	colCity.mask = LVCF_FMT | LVCF_TEXT;
	colCity.pszText = _T("City Name");
	colCity.fmt = LVCFMT_CENTER;

	LVCOLUMN colUpdateCounter;
	colUpdateCounter.mask = LVCF_FMT | LVCF_TEXT;
	colUpdateCounter.pszText = _T("Update counter");
	colUpdateCounter.fmt = LVCFMT_CENTER;

	LVCOLUMN colID;
	colID.mask = LVCF_FMT | LVCF_TEXT;
	colID.pszText = _T("ID");
	colID.fmt = LVCFMT_CENTER;

	LVCOLUMN colArea;
	colArea.mask = LVCF_FMT | LVCF_TEXT;
	colArea.pszText = _T("Area Name");
	colArea.fmt = LVCFMT_CENTER;

	listCtrl.InsertColumn(0, &colID);
	listCtrl.InsertColumn(1, &colUpdateCounter);
	listCtrl.InsertColumn(2, &colCity);
	listCtrl.InsertColumn(3, &colArea);

	listCtrl.SetColumn(0, &colID);
	listCtrl.SetColumn(1, &colUpdateCounter);
	listCtrl.SetColumn(2, &colCity);
	listCtrl.SetColumn(3, &colArea);

	// Set reasonable widths for our columns
	listCtrl.SetColumnWidth(0, 50);
	listCtrl.SetColumnWidth(1, 100);
	listCtrl.SetColumnWidth(2, 100);
	listCtrl.SetColumnWidth(3, 100);
}

void CCitiesListView::OnInsertingAllItems()
{
	CListCtrl& listCtrl = GetListCtrl();

	//GetDocument()->SelectAll(GetDocument()->oCCitiesPtrArray);
	CString szlID;
	CString szlUpdateCounter;

	for (int i = 0; i < GetDocument()->oCCitiesPtrArray.GetCount(); i++)
	{
		szlID.Format(_T("%ld"), GetDocument()->oCCitiesPtrArray.GetAt(i)->lID);
		szlUpdateCounter.Format(_T("%ld"), GetDocument()->oCCitiesPtrArray.GetAt(i)->lUpdateCounter);
		listCtrl.InsertItem(i, szlID);
		listCtrl.SetItemText(i, 1, szlUpdateCounter);
		listCtrl.SetItemText(i, 2, GetDocument()->oCCitiesPtrArray.GetAt(i)->szCityName);
		listCtrl.SetItemText(i, 3, GetDocument()->oCCitiesPtrArray.GetAt(i)->szAreaName);
		listCtrl.SetItemData(i, GetDocument()->oCCitiesPtrArray.GetAt(i)->lID);
	}

}


// Implementation

#ifdef _DEBUG
void CCitiesListView::AssertValid() const
{
	CView::AssertValid();
}

void CCitiesListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCitiesDoc* CCitiesListView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCitiesDoc)));
	return (CCitiesDoc*)m_pDocument;
}
#endif //_DEBUG


// Overrides

void CCitiesListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oCListCtrl = GetListCtrl();
	CITIES* oCities = (CITIES*)pHint;
	if (lHint == Action::ActionDelete)
	{
		for (int i = 0; i < oCListCtrl.GetItemCount(); i++)
		{
			if (oCListCtrl.GetItemData(i) == oCities->lID)
			{
				oCListCtrl.DeleteItem(i);
			}
		}
	}

	else if (lHint == Action::ActionInsert)
	{
		CString strlID;
		CString strlUpdateCounter;
		strlID.Format(_T("%ld"), GetDocument()->oCCitiesPtrArray.GetAt(oCities->lID)->lID);
		strlUpdateCounter.Format(_T("%ld"), 0);
		oCListCtrl.InsertItem(oCListCtrl.GetItemCount(), strlID);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 1, strlUpdateCounter);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 2, GetDocument()->oCCitiesPtrArray.GetAt(oCities->lID)->szCityName);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 3, GetDocument()->oCCitiesPtrArray.GetAt(oCities->lID)->szAreaName);
		oCListCtrl.SetItemData(oCListCtrl.GetItemCount(), GetDocument()->oCCitiesPtrArray.GetAt(oCities->lID)->lID);
	}

	else if (lHint == Action::ActionEdit)
	{
		CString szlID;
		CString szlUpdateCounter;
		szlID.Format(_T("%ld"), oCities->lID);
		szlUpdateCounter.Format(_T("%ld"), oCities->lUpdateCounter);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 0, szlID);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 1, szlUpdateCounter);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 2, GetDocument()->oCCitiesPtrArray[oCities->lID]->szCityName);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 3, GetDocument()->oCCitiesPtrArray[oCities->lID]->szAreaName);
		oCListCtrl.SetItemData(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), GetDocument()->oCCitiesPtrArray[oCities->lID]->lID);
	}
}

void CCitiesListView::OnLButtonDblClk(UINT flags, CPoint pt)
{
	CListCtrl& oCListCtrl = GetListCtrl();
	CITIES* oCities = new CITIES;
	if (oCListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oCListCtrl.GetItemData(oCListCtrl.GetSelectionMark());
	GetDocument()->SelectWhereID(lID, *oCities);
	CCitiesDialog oCitiesDialog(Action::ActionSelect, oCities);
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}
}


void CCitiesListView::OnPopupInsert()
{
	CITIES* oCities = new CITIES;
	CCitiesDialog oCitiesDialog(Action::ActionInsert, oCities);
	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}
	GetDocument()->Insert(*oCities);
	GetDocument()->UpdateAllViews(NULL, Action::ActionInsert, (CObject*)oCities);
}


void CCitiesListView::OnPopupDelete()
{
	CListCtrl& oListCtrl = GetListCtrl();
	CITIES* oCities = new CITIES;
	if (oListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oListCtrl.GetItemData(oListCtrl.GetSelectionMark());
	GetDocument()->SelectWhereID(lID, *oCities);
	GetDocument()->DeleteWhereID(lID);
	GetDocument()->UpdateAllViews(NULL, Action::ActionDelete, (CObject*)oCities);
}


void CCitiesListView::OnPopupEdit()
{
	CListCtrl& oCListCtrl = GetListCtrl();
	CITIES* oCities = new CITIES;
	if (oCListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oCListCtrl.GetItemData(oCListCtrl.GetSelectionMark());
	GetDocument()->SelectWhereID(lID, *oCities);
	CCitiesDialog oCitiesDialog(Action::ActionEdit, oCities);

	if (oCitiesDialog.DoModal() != IDOK)
	{
		return;
	}

	GetDocument()->UpdateWhereID(lID, *oCities);
	//GetDocument()->oCCitiesPtrArray.SetAt(oCities->lID, oCities);
	GetDocument()->UpdateAllViews(NULL, Action::ActionEdit, (CObject*)oCities);
}