#pragma once
#include "PersonsTable.h"
#include "PhoneNumbersTable.h"
#include <atldbcli.h>

/// <summary>Клас за работа с датата на PERSONS</summary>
class CPersonsData
{
public:
	CPersonsData();

	BOOL SelectAll(CPersonsPtrArray& oPersonPtrArray);
	BOOL SelectWhereID(const long lID, CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS);
	BOOL UpdateWhereID(const long lID, const CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS);
	BOOL Insert(const CPERSONWITHPHONENUMBERS & recPersonWithPhoneNumbers);
	BOOL DeleteWhereID(const long lID);

	//Members
public:
	CPersonsTable m_oPersonsTable;
	CPhoneNumbersTable m_oPhoneNumbersTable;
};