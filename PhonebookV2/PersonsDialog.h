#pragma once
#include "PersonsData.h"
#include "Structures.h"
#include "PhoneNumbersDialog.h"
#include "PersonsListView.h"
#include "afxcview.h"
// CPersonsDialog dialog

class CPersonsDialog : public CDialog
{
	DECLARE_DYNAMIC(CPersonsDialog)
	DECLARE_MESSAGE_MAP()
public:
	CPersonsDialog(Action nAction, CPERSONWITHPHONENUMBERS* m_CPersonWithPhoneNumbers, CCitiesPtrArray* m_CitiesPtrArray, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPersonsDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSONSDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	//Overrides
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	//Members
private:
	CEdit m_edbAddress;
	CEdit m_edbUpdateCounter;
	CEdit m_edbSecondName;
	CEdit m_edbLastName;
	CEdit m_edbID;
	CEdit m_edbFirstName;
	CEdit m_edbUCN;
	CComboBox m_comboCityID;

	CMap<long, long, CITIES*, CITIES*> mapCities;
	CListCtrl m_PhoneNumbersListCtrl;
	CPERSONWITHPHONENUMBERS* m_oCPersonWithPhoneNumbers;
	CCitiesPtrArray* m_CitiesPtrArray;
	CPersonsData m_PersonsData;
	int m_nAction;

	void InsertItemsInComboBox();
	void InsertItemsInListControl();
	void InsertTextsInFields();
public:

	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnLButtonDblClk(NMHDR*, LRESULT*);
	afx_msg void OnPhonenumbersInsertnumber();
	afx_msg void OnPhonenumbersEditnumber();
	afx_msg void OnPhonenumbersDeletenumber();

};
