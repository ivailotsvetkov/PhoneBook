// PersonsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBookV2.h"
#include "PersonsDialog.h"
#include "afxdialogex.h"


// CPersonsDialog dialog

IMPLEMENT_DYNAMIC(CPersonsDialog, CDialog)

CPersonsDialog::CPersonsDialog(Action nAction, CPERSONWITHPHONENUMBERS* m_CPersonWithPhoneNumbers, CCitiesPtrArray* CitiesPtrArray, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PERSONSDIALOG, pParent)
{
	m_CitiesPtrArray = CitiesPtrArray;
	m_nAction = nAction;
	m_oCPersonWithPhoneNumbers = m_CPersonWithPhoneNumbers;
}

CPersonsDialog::~CPersonsDialog()
{
}

void CPersonsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITUPDATECOUNTER, m_edbUpdateCounter);
	DDX_Control(pDX, IDC_EDITSECONDNAME, m_edbSecondName);
	DDX_Control(pDX, IDC_EDITLASTNAME, m_edbLastName);
	DDX_Control(pDX, IDC_EDITID, m_edbID);
	DDX_Control(pDX, IDC_EDITFIRSTNAME, m_edbFirstName);
	DDX_Control(pDX, IDC_EDITADDRESS, m_edbAddress);
	DDX_Control(pDX, IDC_EDITUCN, m_edbUCN);
	DDX_Control(pDX, IDC_LISTPHONENUMBERS, m_PhoneNumbersListCtrl);
	DDX_Control(pDX, IDC_CITYIDCOMBO, m_comboCityID);
}

BOOL CPersonsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_PhoneNumbersListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	LVCOLUMN colPhoneNumber;
	colPhoneNumber.mask = LVCF_FMT | LVCF_TEXT;
	colPhoneNumber.pszText = _T("Phone Number");
	colPhoneNumber.fmt = LVCFMT_CENTER;

	LVCOLUMN colPhoneType;
	colPhoneType.mask = LVCF_FMT | LVCF_TEXT;
	colPhoneType.pszText = _T("Phone Type");
	colPhoneType.fmt = LVCFMT_CENTER;

	m_PhoneNumbersListCtrl.InsertColumn(0, &colPhoneNumber);
	m_PhoneNumbersListCtrl.InsertColumn(1, &colPhoneType);
	m_PhoneNumbersListCtrl.SetColumn(0, &colPhoneNumber);
	m_PhoneNumbersListCtrl.SetColumn(1, &colPhoneType);
	m_PhoneNumbersListCtrl.SetColumnWidth(0, 200);
	m_PhoneNumbersListCtrl.SetColumnWidth(1, 120);

	InsertItemsInListControl();
	InsertTextsInFields();
	InsertItemsInComboBox();
	return TRUE;
}

void CPersonsDialog::OnOK()
{
	if (m_nAction != Action::ActionSelect)
	{
		CString strName;
		CString strSecondName;
		CString strLastName;
		CString strUCN;
		CString strCityID;
		CString strAddress;
		int nCityID;

		m_comboCityID.GetWindowTextW(strCityID);
		m_edbFirstName.GetWindowTextW(strName);
		m_edbSecondName.GetWindowTextW(strSecondName);
		m_edbLastName.GetWindowTextW(strLastName);
		m_edbUCN.GetWindowTextW(strUCN);
		m_edbAddress.GetWindowTextW(strAddress);

		for (int i = 0; i < m_CitiesPtrArray->GetCount(); i++)
		{
			if (strCityID = m_CitiesPtrArray->GetAt(i)->szCityName)
			{
				nCityID = m_CitiesPtrArray->GetAt(i)->lID;
			}
		}

		_tcsncpy_s(m_oCPersonWithPhoneNumbers->m_oPersons.szFirstName, strName, _countof(m_oCPersonWithPhoneNumbers->m_oPersons.szFirstName));
		m_oCPersonWithPhoneNumbers->m_oPersons.nCityId = nCityID;
		_tcsncpy_s(m_oCPersonWithPhoneNumbers->m_oPersons.szMiddleName, strSecondName, _countof(m_oCPersonWithPhoneNumbers->m_oPersons.szMiddleName));
		_tcsncpy_s(m_oCPersonWithPhoneNumbers->m_oPersons.szLastName, strLastName, _countof(m_oCPersonWithPhoneNumbers->m_oPersons.szLastName));
		_tcsncpy_s(m_oCPersonWithPhoneNumbers->m_oPersons.szUCN, strUCN, _countof(m_oCPersonWithPhoneNumbers->m_oPersons.szUCN));
		_tcsncpy_s(m_oCPersonWithPhoneNumbers->m_oPersons.szAddress, strAddress, _countof(m_oCPersonWithPhoneNumbers->m_oPersons.szAddress));
	}



	CDialog::OnOK();
}



// CPersonsDialog message handlers

BEGIN_MESSAGE_MAP(CPersonsDialog, CDialog)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LISTPHONENUMBERS, &CPersonsDialog::OnLButtonDblClk)
	ON_COMMAND(ID_PHONENUMBERS_INSERTNUMBER, &CPersonsDialog::OnPhonenumbersInsertnumber)
	ON_COMMAND(ID_PHONENUMBERS_EDITNUMBER, &CPersonsDialog::OnPhonenumbersEditnumber)
	ON_COMMAND(ID_PHONENUMBERS_DELETENUMBER, &CPersonsDialog::OnPhonenumbersDeletenumber)
END_MESSAGE_MAP()



void CPersonsDialog::InsertItemsInComboBox()
{
	for (int i = 0; i < m_CitiesPtrArray->GetCount(); i++)
	{
		mapCities[m_CitiesPtrArray->GetAt(i)->lID] = m_CitiesPtrArray->GetAt(i);
		m_comboCityID.AddString(m_CitiesPtrArray->GetAt(i)->szCityName);
	}
	m_comboCityID.SetCurSel(m_oCPersonWithPhoneNumbers->m_oPersons.nCityId);
}

void CPersonsDialog::InsertItemsInListControl()
{
	CString strID;
	CString strPhoneNumber;
	CString strPhoneType;
	for (int i = 0; i < m_oCPersonWithPhoneNumbers->m_PhoneNumberPtrArray.GetCount(); i++)
	{

		strPhoneNumber.Format(_T("%ld"), m_oCPersonWithPhoneNumbers->m_PhoneNumberPtrArray.GetAt(i)->nPhone);
		strPhoneType.Format(_T("%d"), m_oCPersonWithPhoneNumbers->m_PhoneNumberPtrArray.GetAt(i)->nPhoneTypeId);
		m_PhoneNumbersListCtrl.InsertItem(i, strPhoneNumber);
		m_PhoneNumbersListCtrl.SetItemText(i, 0, strPhoneNumber);
		m_PhoneNumbersListCtrl.SetItemText(i, 1, strPhoneType);
		m_PhoneNumbersListCtrl.SetItemData(i, m_oCPersonWithPhoneNumbers->m_PhoneNumberPtrArray.GetAt(i)->lID);
	}
}

void CPersonsDialog::InsertTextsInFields()
{
	CString strID;
	CString strUCounter;
	strID.Format(_T("%ld"), m_oCPersonWithPhoneNumbers->m_oPersons.lID);
	strUCounter.Format(_T("%ld"), m_oCPersonWithPhoneNumbers->m_oPersons.lUpdateCounter);


	m_edbID.SetWindowTextW(strID);
	m_edbUpdateCounter.SetWindowTextW(strUCounter);
	m_edbFirstName.SetWindowTextW(m_oCPersonWithPhoneNumbers->m_oPersons.szFirstName);
	m_edbSecondName.SetWindowTextW(m_oCPersonWithPhoneNumbers->m_oPersons.szMiddleName);
	m_edbLastName.SetWindowTextW(m_oCPersonWithPhoneNumbers->m_oPersons.szLastName);
	m_edbUCN.SetWindowTextW(m_oCPersonWithPhoneNumbers->m_oPersons.szUCN);
	m_edbAddress.SetWindowTextW(m_oCPersonWithPhoneNumbers->m_oPersons.szAddress);

	m_edbID.EnableWindow(false);
	m_edbUpdateCounter.EnableWindow(false);

	if (m_nAction == Action::ActionSelect)
	{
		m_edbFirstName.EnableWindow(false);
		m_edbSecondName.EnableWindow(false);
		m_edbLastName.EnableWindow(false);

		m_edbUCN.EnableWindow(false);
		m_edbAddress.EnableWindow(false);

	}
}

void CPersonsDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu mnuPopupSubmit;
	mnuPopupSubmit.LoadMenu(IDR_MENUPHONENUMBERS);

	// Find the rectangle around the button
	CRect rectMenu;
	m_PhoneNumbersListCtrl.GetWindowRect(rectMenu);

	// Get a pointer to the first item of the menu
	CMenu *mnuPopupMenu = mnuPopupSubmit.GetSubMenu(0);
	ASSERT(mnuPopupMenu);

	// Find out if the user right-clicked the button
	// because we are interested only in the button
	if (rectMenu.PtInRect(point)) // Since the user right-clicked the button, display the context menu
		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPersonsDialog::OnLButtonDblClk(NMHDR*, LRESULT*)
{
	PHONE_NUMBERS* oPhoneNumbers = new PHONE_NUMBERS;
	if (m_PhoneNumbersListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)m_PhoneNumbersListCtrl.GetItemData(m_PhoneNumbersListCtrl.GetSelectionMark());

	m_PersonsData.m_oPhoneNumbersTable.SelectWhereID(lID, *oPhoneNumbers);
	CPhoneNumbersDialog oPhoneNumbersDialog(Action::ActionSelect, oPhoneNumbers);
	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}
}


void CPersonsDialog::OnPhonenumbersInsertnumber()
{
	PHONE_NUMBERS* oPhoneNumbers = new PHONE_NUMBERS;
	CPhoneNumbersDialog oPhoneNumbersDialog(Action::ActionInsert, oPhoneNumbers);

	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}

	CString strPhoneNumber;
	CString strPhoneType;
	strPhoneNumber.Format(_T("%ld"), oPhoneNumbers->nPhone);
	strPhoneType.Format(_T("%d"), oPhoneNumbers->nPhoneTypeId);
	m_PhoneNumbersListCtrl.InsertItem(m_PhoneNumbersListCtrl.GetItemCount() - 1, strPhoneNumber);
	m_PhoneNumbersListCtrl.SetItemText(m_PhoneNumbersListCtrl.GetItemCount() - 1, 1, strPhoneNumber);
	m_PhoneNumbersListCtrl.SetItemText(m_PhoneNumbersListCtrl.GetItemCount() - 1, 2, strPhoneType);
	m_PhoneNumbersListCtrl.SetItemData(m_PhoneNumbersListCtrl.GetItemCount() - 1, m_PhoneNumbersListCtrl.GetItemCount() - 1);
	m_PersonsData.m_oPhoneNumbersTable.Insert(*oPhoneNumbers);
}


void CPersonsDialog::OnPhonenumbersEditnumber()
{
	PHONE_NUMBERS* oPhoneNumbers = new PHONE_NUMBERS;
	if (m_PhoneNumbersListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)m_PhoneNumbersListCtrl.GetItemData(m_PhoneNumbersListCtrl.GetSelectionMark());
	m_PersonsData.m_oPhoneNumbersTable.SelectWhereID(lID, *oPhoneNumbers);

	CPhoneNumbersDialog oPhoneNumbersDialog(Action::ActionEdit, oPhoneNumbers);
	if (oPhoneNumbersDialog.DoModal() != IDOK)
	{
		return;
	}
	CString strPhoneNumber;
	CString strPhoneType;
	strPhoneNumber.Format(_T("%ld"), oPhoneNumbers->nPhone);
	strPhoneType.Format(_T("%d"), oPhoneNumbers->nPhoneTypeId);
	m_PhoneNumbersListCtrl.SetItemText(lID, 0, strPhoneNumber);
	m_PhoneNumbersListCtrl.SetItemText(lID, 1, strPhoneType);

	m_PersonsData.m_oPhoneNumbersTable.UpdateWhereID(lID, *oPhoneNumbers);

}


void CPersonsDialog::OnPhonenumbersDeletenumber()
{
	if (m_PhoneNumbersListCtrl.GetSelectionMark() == -1)
	{
		return;
	}
	long lID = (long)m_PhoneNumbersListCtrl.GetItemData(m_PhoneNumbersListCtrl.GetSelectionMark());
	m_PersonsData.m_oPhoneNumbersTable.DeleteWhereID(lID);
}
