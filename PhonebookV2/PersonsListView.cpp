
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhonebookV2.h"
#endif

#include "PersonsListView.h"


// CPersonsListView

IMPLEMENT_DYNCREATE(CPersonsListView, CListView)

CPersonsListView::CPersonsListView()
{

}

CPersonsListView::~CPersonsListView()
{
}

BEGIN_MESSAGE_MAP(CPersonsListView, CListView)
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_POPUP_INSERT, &CPersonsListView::OnPopupInsert)
	ON_COMMAND(ID_POPUP_DELETE, &CPersonsListView::OnPopupDelete)
	ON_COMMAND(ID_POPUP_EDIT, &CPersonsListView::OnPopupEdit)
END_MESSAGE_MAP()


// CPersonsListView diagnostics

#ifdef _DEBUG
void CPersonsListView::AssertValid() const
{
	CListView::AssertValid();
}

void CPersonsListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
// CPersonsListView message handlers
CPersonsDoc * CPersonsListView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersonsDoc)));
	return (CPersonsDoc*)m_pDocument;
}

#endif //_DEBUG




void CPersonsListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	if (!GetDocument()->m_CitiesData.SelectAll(m_CitiesPtrArray))
		return;
	for (int i = 0; i < m_CitiesPtrArray.GetCount(); i++)
	{
		mapCities.SetAt(m_CitiesPtrArray.GetAt(i)->lID, m_CitiesPtrArray.GetAt(i));
	}

	OnCreatingColumns();
	OnInsertingAllItems();

}

void CPersonsListView::OnCreatingColumns()
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	LVCOLUMN colID;
	colID.mask = LVCF_FMT | LVCF_TEXT;
	colID.pszText = _T("ID");
	colID.fmt = LVCFMT_CENTER;

	LVCOLUMN colUpdateCounter;
	colUpdateCounter.mask = LVCF_FMT | LVCF_TEXT;
	colUpdateCounter.pszText = _T("Update counter");
	colUpdateCounter.fmt = LVCFMT_CENTER;

	LVCOLUMN colFirstName;
	colFirstName.mask = LVCF_FMT | LVCF_TEXT;
	colFirstName.pszText = _T("First Name");
	colFirstName.fmt = LVCFMT_CENTER;

	LVCOLUMN colSecondName;
	colSecondName.mask = LVCF_FMT | LVCF_TEXT;
	colSecondName.pszText = _T("Second Name");
	colSecondName.fmt = LVCFMT_CENTER;

	LVCOLUMN colLastName;
	colLastName.mask = LVCF_FMT | LVCF_TEXT;
	colLastName.pszText = _T("Last Name");
	colLastName.fmt = LVCFMT_CENTER;

	LVCOLUMN colUCN;
	colUCN.mask = LVCF_FMT | LVCF_TEXT;
	colUCN.pszText = _T("UCN");
	colUCN.fmt = LVCFMT_CENTER;

	LVCOLUMN colCityName;
	colCityName.mask = LVCF_FMT | LVCF_TEXT;
	colCityName.pszText = _T("City ID");
	colCityName.fmt = LVCFMT_CENTER;

	LVCOLUMN colAddress;
	colAddress.mask = LVCF_FMT | LVCF_TEXT;
	colAddress.pszText = _T("Address");
	colAddress.fmt = LVCFMT_CENTER;

	listCtrl.InsertColumn(0, &colID);
	listCtrl.InsertColumn(1, &colUpdateCounter);
	listCtrl.InsertColumn(2, &colFirstName);
	listCtrl.InsertColumn(3, &colSecondName);
	listCtrl.InsertColumn(4, &colLastName);
	listCtrl.InsertColumn(5, &colCityName);
	listCtrl.InsertColumn(6, &colUCN);
	listCtrl.InsertColumn(7, &colAddress);

	listCtrl.SetColumn(0, &colID);
	listCtrl.SetColumn(1, &colUpdateCounter);
	listCtrl.SetColumn(2, &colFirstName);
	listCtrl.SetColumn(3, &colSecondName);
	listCtrl.SetColumn(4, &colLastName);
	listCtrl.SetColumn(5, &colCityName);
	listCtrl.SetColumn(6, &colUCN);
	listCtrl.SetColumn(7, &colAddress);

	//Set width of columns
	listCtrl.SetColumnWidth(0, 50);
	listCtrl.SetColumnWidth(1, 100);
	listCtrl.SetColumnWidth(2, 100);
	listCtrl.SetColumnWidth(3, 100);
	listCtrl.SetColumnWidth(4, 100);
	listCtrl.SetColumnWidth(5, 100);
	listCtrl.SetColumnWidth(6, 100);
	listCtrl.SetColumnWidth(7, 100);
}

void CPersonsListView::OnInsertingAllItems()
{
	CListCtrl& listCtrl = GetListCtrl();


	CString szlID;
	CString szlUpdateCounter;
	CString sznCityID;


	for (int i = 0; i < GetDocument()->m_PersonsPtrArray.GetCount(); i++)
	{
		int ncityID = GetDocument()->GetPersonByID(i)->nCityId;
		szlID.Format(_T("%ld"), GetDocument()->GetPersonByID(i)->lID);
		szlUpdateCounter.Format(_T("%ld"), GetDocument()->GetPersonByID(i)->lUpdateCounter);
		sznCityID.Format(_T("%ld"), GetDocument()->GetPersonByID(i)->nCityId);
		listCtrl.InsertItem(i, szlID);
		listCtrl.SetItemText(i, 1, szlUpdateCounter);
		listCtrl.SetItemText(i, 2, GetDocument()->GetPersonByID(i)->szFirstName);
		listCtrl.SetItemText(i, 3, GetDocument()->GetPersonByID(i)->szMiddleName);
		listCtrl.SetItemText(i, 4, GetDocument()->GetPersonByID(i)->szLastName);
		listCtrl.SetItemText(i, 5, mapCities[ncityID]->szCityName);
		listCtrl.SetItemText(i, 6, GetDocument()->GetPersonByID(i)->szUCN);
		listCtrl.SetItemText(i, 7, GetDocument()->GetPersonByID(i)->szAddress);
		listCtrl.SetItemData(i, GetDocument()->GetPersonByID(i)->lID);
	}
}


void CPersonsListView::OnLButtonDblClk(UINT flags, CPoint pt)
{
	CListCtrl& oCListCtrl = GetListCtrl();
	m_CPersonWithPhoneNumbers = new CPERSONWITHPHONENUMBERS;
	if (oCListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oCListCtrl.GetItemData(oCListCtrl.GetSelectionMark());
	GetDocument()->SelectWhereID(lID, *m_CPersonWithPhoneNumbers);
	CPersonsDialog oPersonsDialog(Action::ActionSelect, m_CPersonWithPhoneNumbers, &m_CitiesPtrArray);
	if (oPersonsDialog.DoModal() != IDOK)
	{
		return;
	}

}

void CPersonsListView::OnPopupInsert()
{
	m_CPersonWithPhoneNumbers = new CPERSONWITHPHONENUMBERS;
	CPersonsDialog oPersonsDialog(Action::ActionInsert, m_CPersonWithPhoneNumbers, &m_CitiesPtrArray);
	if (oPersonsDialog.DoModal() != IDOK)
	{
		return;
	}
	if (!GetDocument()->Insert(*m_CPersonWithPhoneNumbers))
		return;
	GetDocument()->UpdateAllViews(NULL, Action::ActionInsert, (CObject*)m_CPersonWithPhoneNumbers);
}

void CPersonsListView::OnPopupDelete()
{
	CListCtrl& oListCtrl = GetListCtrl();
	m_CPersonWithPhoneNumbers = new CPERSONWITHPHONENUMBERS;
	if (oListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oListCtrl.GetItemData(oListCtrl.GetSelectionMark());
	if (!GetDocument()->SelectWhereID(lID, *m_CPersonWithPhoneNumbers))
		return;
	if (!GetDocument()->DeleteWhereID(lID))
		return;
	GetDocument()->UpdateAllViews(NULL, Action::ActionDelete, (CObject*)m_CPersonWithPhoneNumbers);
}

void CPersonsListView::OnPopupEdit()
{
	CListCtrl& oCListCtrl = GetListCtrl();
	m_CPersonWithPhoneNumbers = new CPERSONWITHPHONENUMBERS;
	if (oCListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)oCListCtrl.GetItemData(oCListCtrl.GetSelectionMark());
	if (!GetDocument()->SelectWhereID(lID, *m_CPersonWithPhoneNumbers))
		return;
	CPersonsDialog oPeroonsDialog(Action::ActionEdit, m_CPersonWithPhoneNumbers, &m_CitiesPtrArray);

	if (oPeroonsDialog.DoModal() != IDOK)
	{
		return;
	}

	GetDocument()->UpdateWhereID(lID, *m_CPersonWithPhoneNumbers);
	GetDocument()->UpdateAllViews(NULL, Action::ActionEdit, (CObject*)m_CPersonWithPhoneNumbers);
}


void CPersonsListView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
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


BOOL CPersonsListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT | LVS_NOSORTHEADER | LVS_SINGLESEL;
	return CListView::PreCreateWindow(cs);
}


void CPersonsListView::OnUpdate(CView* /*pSender*/, LPARAM lHint, CObject* pHint)
{
	CListCtrl& oCListCtrl = GetListCtrl();
	CPERSONWITHPHONENUMBERS* oPersons = (CPERSONWITHPHONENUMBERS*)pHint;

	if (lHint == Action::ActionDelete)
	{
		for (int i = 0; i < oCListCtrl.GetItemCount(); i++)
		{
			if (oCListCtrl.GetItemData(i) == oPersons->m_oPersons.lID)
			{
				oCListCtrl.DeleteItem(i);
			}
		}
	}

	else if (lHint == Action::ActionInsert)
	{
		CString szlID;
		CString szlUpdateCounter;
		CString sznCityID;

		szlID.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lID);
		szlUpdateCounter.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lUpdateCounter);
		sznCityID.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->nCityId);
		oCListCtrl.InsertItem(oCListCtrl.GetItemCount(), szlID);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 1, szlUpdateCounter);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 2, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szFirstName);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 3, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szMiddleName);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 4, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szLastName);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 5, mapCities[GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->nCityId]->szCityName);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 6, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szUCN);
		oCListCtrl.SetItemText(oCListCtrl.GetItemCount(), 7, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szAddress);
		oCListCtrl.SetItemData(oCListCtrl.GetItemCount(), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lID);

	}

	else if (lHint == Action::ActionEdit)
	{
		CString szlID;
		CString szlUpdateCounter;
		CString sznCityID;

		szlID.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lID);
		szlUpdateCounter.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lUpdateCounter);
		sznCityID.Format(_T("%ld"), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->nCityId);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 0, szlID);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 1, szlUpdateCounter);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 2, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szFirstName);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 3, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szMiddleName);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 4, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szLastName);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 5, sznCityID);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 6, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szUCN);
		oCListCtrl.SetItemText(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), 7, GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->szAddress);
		oCListCtrl.SetItemData(oCListCtrl.GetNextItem(-1, LVNI_SELECTED), GetDocument()->GetPersonByID(oPersons->m_oPersons.lID)->lID);
	}
}


void CPersonsListView::OnDraw(CDC* /*pDC*/)
{
	// TODO: Add your specialized code here and/or call the base class
	CPersonsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}

