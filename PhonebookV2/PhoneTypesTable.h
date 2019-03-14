#pragma once
#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "BaseTable.h"
#include "Structures.h"

class CPhoneTypesAccessor
{
public:
	/// <summary> PHONE_TYPES Accessor </summary>
	PHONE_TYPES m_recPhoneTypes;

	BEGIN_ACCESSOR_MAP(CPhoneTypesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPhoneTypes.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPhoneTypes.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPhoneTypes.szPhoneType)

		END_ACCESSOR()
	END_ACCESSOR_MAP()

};

/// <summary>Клас за работа с таблица PHONE_TYPES</summary>
class CPhoneTypesTable : public CBaseTable<CPhoneTypesAccessor, PHONE_TYPES>
{
public:
	CPhoneTypesTable() : CBaseTable(offsetof(PHONE_TYPES, lUpdateCounter))
	{}
protected:
	PHONE_TYPES& CBaseTable::GetAccessorData() {
		return m_recPhoneTypes;
	}
	CString CBaseTable::GetTableName() {
		return _T("PHONE_TYPES");
	}
};