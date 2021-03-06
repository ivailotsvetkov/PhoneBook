#pragma once
#include "Structures.h"

/// <summary>Клас за работа с диалога CITIES</summary>
class CCitiesDialog : public CDialog
{
	DECLARE_DYNAMIC(CCitiesDialog)
	//Constructor - Destructor
public:
	CCitiesDialog(Action nAction, CITIES * city, CWnd* pParent = nullptr);
	virtual ~CCitiesDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CITYDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	//Overrides
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//Members
private:
	CEdit m_edbName;
	CEdit m_edbArea;
	CITIES * m_pCities;
	CEdit m_edbCityID;
	CEdit m_edbUCounter;
	int m_nAction;
};
