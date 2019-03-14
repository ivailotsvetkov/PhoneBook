#pragma once
#include "CitiesTable.h"


/// <summary>���� �� ������ � ������ �� CITIES</summary>
class CCitiesData
{
	//Operations
public:
	BOOL SelectAll(CCitiesPtrArray& oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);
	BOOL Insert(const CITIES& recCities);
	BOOL DeleteWhereID(const long lID);

	//Members
private:
	CCitiesTable m_oCititesTable;
};