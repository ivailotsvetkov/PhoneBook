// CCitiesEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBookV2.h"
#include "CitiesDialog.h"
#include "afxdialogex.h"
#include "Structures.h"

IMPLEMENT_DYNAMIC(CCitiesDialog, CDialog)

//Constructor/Destructor
CCitiesDialog::CCitiesDialog(Action nAction, CITIES* city, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CITYDIALOG, pParent)
{
	this->m_pCities = city;
	m_nAction = nAction;
}
CCitiesDialog::~CCitiesDialog()
{
}

void CCitiesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, EditTextCity, m_edbName);
	DDX_Control(pDX, EditTextArea, m_edbArea);
	DDX_Control(pDX, EditTextCityID, m_edbCityID);
	DDX_Control(pDX, EditTextCityUpdateCounter, m_edbUCounter);
}

BEGIN_MESSAGE_MAP(CCitiesDialog, CDialog)

END_MESSAGE_MAP()


// CCitiesEditDialog message handlers


BOOL CCitiesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strID;
	strID.Format(_T("%ld"), m_pCities->lID);
	CString strUCounter;
	strUCounter.Format(_T("%ld"), m_pCities->lUpdateCounter);

	m_edbCityID.SetWindowTextW(strID);
	m_edbUCounter.SetWindowTextW(strUCounter);
	m_edbName.SetWindowTextW(m_pCities->szCityName);
	m_edbArea.SetWindowTextW(m_pCities->szAreaName);

	m_edbCityID.EnableWindow(false);
	m_edbUCounter.EnableWindow(false);

	if (m_nAction == Action::ActionSelect)
	{
		m_edbArea.EnableWindow(false);
		m_edbName.EnableWindow(false);
	}

	return TRUE;
}

void CCitiesDialog::OnOK()
{
	if (m_nAction != Action::ActionSelect)
	{
		CString strName;
		CString strArea;

		m_edbName.GetWindowTextW(strName);
		_tcsncpy_s(m_pCities->szCityName, strName, _countof(m_pCities->szCityName));

		m_edbArea.GetWindowTextW(strArea);
		_tcsncpy_s(m_pCities->szAreaName, strArea, _countof(m_pCities->szAreaName));
	}

	CDialog::OnOK();
}