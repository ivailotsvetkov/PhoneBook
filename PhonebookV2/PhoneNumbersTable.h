#pragma once
#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "BaseTable.h"
#include "Structures.h"

class CPhoneNumbersAccessor
{
public:
	/// <summary> Phone Numbers Accessor </summary>
	PHONE_NUMBERS m_recPhoneNumbers;

	BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPhoneNumbers.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPhoneNumbers.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneNumbers.nPersonId)
		COLUMN_ENTRY(4, m_recPhoneNumbers.nPhoneTypeId)
		COLUMN_ENTRY(5, m_recPhoneNumbers.nPhone)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

};

/// <summary>Клас за работа с таблица PHONE_NUMBERS</summary>
class CPhoneNumbersTable : public CBaseTable<CPhoneNumbersAccessor, PHONE_NUMBERS>
{
public:
	CPhoneNumbersTable::CPhoneNumbersTable() : CBaseTable(offsetof(PHONE_NUMBERS, lUpdateCounter))
	{

	}

	CPhoneNumbersTable(CSession& oCSession) : CBaseTable(offsetof(PHONE_NUMBERS, lUpdateCounter), oCSession)
	{
		m_CSession = oCSession;
	}
protected:
	PHONE_NUMBERS& CBaseTable::GetAccessorData() {
		return m_recPhoneNumbers;
	}
	CString CBaseTable::GetTableName() {
		return _T("PHONE_NUMBERS");
	}
	CSession m_CSession;
};