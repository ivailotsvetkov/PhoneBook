
// PhonebookV2.h : main header file for the PhonebookV2 application
//
#pragma once
#include "stdafx.h"
#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "DataSourceSingleton.h"
#include "resource.h"       // main symbols


// CPhonebookV2App:
// See PhonebookV2.cpp for the implementation of this class
//

class CPhonebookV2App : public CWinApp
{
public:
	CPhonebookV2App();


	// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Implementation
	afx_msg void OnAppAbout();
	void OnNewdocumentPersons();
	DECLARE_MESSAGE_MAP()
};


