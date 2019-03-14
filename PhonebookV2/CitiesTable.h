#pragma once
#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "BaseTable.h"
#include "Structures.h"

class CCitiesAccessor
{
public:
	/// <summary>CITIES Accessor  </summary>
	CITIES m_recCity;

	BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
		BEGIN_ACCESSOR(0, true)
		COLUMN_ENTRY(1, m_recCity.lID)
		END_ACCESSOR()

		BEGIN_ACCESSOR(1, true)
		COLUMN_ENTRY(2, m_recCity.lUpdateCounter)
		COLUMN_ENTRY(3, m_recCity.szCityName)
		COLUMN_ENTRY(4, m_recCity.szAreaName)
		END_ACCESSOR()
	END_ACCESSOR_MAP()

};

/// <summary>Клас за работа с таблица CITIES</summary>

class CCitiesTable : public CBaseTable<CCitiesAccessor, CITIES>
{
public:
	CCitiesTable() : CBaseTable(offsetof(CITIES, lUpdateCounter))
	{}
protected:
	CITIES&	CBaseTable::GetAccessorData() {
		return m_recCity;
	}
	CString CBaseTable::GetTableName() {
		return _T("CITIES");
	}

};