#pragma once
#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "BaseTable.h"
#include "Structures.h"

class CPersonAccessor
{
public:
	/// <summary>Person Accessor  </summary>
	PERSONS m_recPerson;

	BEGIN_ACCESSOR_MAP(CPersonAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recPerson.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recPerson.lUpdateCounter)
		COLUMN_ENTRY(3, m_recPerson.szFirstName)
		COLUMN_ENTRY(4, m_recPerson.szMiddleName)
		COLUMN_ENTRY(5, m_recPerson.szLastName)
		COLUMN_ENTRY(6, m_recPerson.szUCN)
		COLUMN_ENTRY(7, m_recPerson.nCityId)
		COLUMN_ENTRY(8, m_recPerson.szAddress)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

};

/// <summary>Клас за работа с таблица PERSONS</summary>
class CPersonsTable : public CBaseTable<CPersonAccessor, PERSONS>
{
public:
	CPersonsTable(CSession& oCSession) : CBaseTable(offsetof(PERSONS, lUpdateCounter), oCSession)
	{

	}
	CPersonsTable() : CBaseTable(offsetof(PERSONS, lUpdateCounter))
	{

	}
	CSession CPersonsTable::getCSession()
	{
		return m_CSession;
	}
protected:
	PERSONS& CBaseTable::GetAccessorData() {
		return m_recPerson;
	}
	CString CBaseTable::GetTableName() {
		return _T("PERSONS");
	}

	CSession m_CSession;
};