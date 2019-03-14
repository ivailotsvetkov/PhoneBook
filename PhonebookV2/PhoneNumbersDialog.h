#pragma once
#include "Structures.h"
#include "PersonsDoc.h"
#include "PhoneTypesTable.h"
#include "afxcview.h"
// CPersonsDialog dialog

class CPhoneNumbersDialog : public CDialog
{
	DECLARE_DYNAMIC(CPhoneNumbersDialog)

public:
	CPhoneNumbersDialog(Action nAction, PHONE_NUMBERS* oPhoneNumber, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDialog();

	DECLARE_MESSAGE_MAP()
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONENUMBERSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	//Overrides
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//Members
private:
	CPhoneTypesTable oPhoneTypesTable;
	PHONE_TYPES m_PhoneTyope;
	CPhoneTypesPtrArray phoneTypesPtrArray;
	CComboBox comboBox_PhoneType;
	CEdit edb_PhoneNumber;
	int m_nAction;
	PHONE_NUMBERS* m_pPhoneNumbers;
};