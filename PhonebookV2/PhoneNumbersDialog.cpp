#include "stdafx.h"
#include "PhoneNumbersDialog.h"
#include "afxdialogex.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CPhoneNumbersDialog, CDialog)

BEGIN_MESSAGE_MAP(CPhoneNumbersDialog, CDialog)

END_MESSAGE_MAP()

CPhoneNumbersDialog::CPhoneNumbersDialog(Action nAction, PHONE_NUMBERS * oPhoneNumber, CWnd * pParent) : CDialog(IDD_PHONENUMBERSDIALOG, pParent)
{
	m_nAction = nAction;
	m_pPhoneNumbers = oPhoneNumber;
}

CPhoneNumbersDialog::~CPhoneNumbersDialog()
{
}

void CPhoneNumbersDialog::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDITNUMBER, edb_PhoneNumber);
	DDX_Control(pDX, IDC_COMBO_PHONE_TYPE, comboBox_PhoneType);
}

BOOL CPhoneNumbersDialog::OnInitDialog()
{
	CDialog::OnInitDialog();



	int nType = m_pPhoneNumbers->nPhoneTypeId;

	CString strPhoneNumber;
	strPhoneNumber.Format(_T("%ld"), m_pPhoneNumbers->nPhone);
	edb_PhoneNumber.SetWindowTextW(strPhoneNumber);

	for (int i = 0; i < phoneTypesPtrArray.GetCount(); i++)
	{
		comboBox_PhoneType.AddString(phoneTypesPtrArray.GetAt(i)->szPhoneType);
	}

	switch (nType)
	{
	case 0:
		comboBox_PhoneType.SetCurSel(2);
		break;
	case 1:
		comboBox_PhoneType.SetCurSel(1);
		break;
	case 2:
		comboBox_PhoneType.SetCurSel(0);
		break;
	case 3:
		comboBox_PhoneType.SetCurSel(3);
		break;
	default:
		break;
	}
	if (m_nAction == Action::ActionSelect)
	{
		edb_PhoneNumber.EnableWindow(false);
		comboBox_PhoneType.EnableWindow(false);
	}
	return TRUE;
}

void CPhoneNumbersDialog::OnOK()
{
	if (m_nAction != Action::ActionSelect)
	{
		CString strPhone;
		CString strType;
		int nType;

		comboBox_PhoneType.GetLBText(comboBox_PhoneType.GetCurSel(), strType);
		edb_PhoneNumber.GetWindowTextW(strPhone);

		int nPhone = _wtoi(strPhone);

		if (strType == _T("Home"))
		{
			nType = 1;
		}
		else if (strType == _T("Fax"))
		{
			nType = 2;
		}
		else if (strType == _T("Work"))
		{
			nType = 3;
		}
		else
		{
			nType = 0;
		}


		m_pPhoneNumbers->nPhone = nPhone;
		m_pPhoneNumbers->nPhoneTypeId = nType;
	}

	CDialog::OnOK();
}
