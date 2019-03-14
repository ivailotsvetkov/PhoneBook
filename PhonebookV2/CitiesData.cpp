#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "CitiesData.h"

using namespace std;


BOOL CCitiesData::SelectAll(CCitiesPtrArray& oCitiesArray)
{
	return m_oCititesTable.SelectAll(oCitiesArray);
}

BOOL CCitiesData::SelectWhereID(const long lID, CITIES& recCities)
{
	return m_oCititesTable.SelectWhereID(lID, recCities);
}

BOOL CCitiesData::UpdateWhereID(const long lID, const CITIES& recCities)
{
	return m_oCititesTable.UpdateWhereID(lID, recCities);
}

BOOL CCitiesData::Insert(const CITIES& recCities)
{
	return  m_oCititesTable.Insert(recCities);
}

BOOL CCitiesData::DeleteWhereID(const long lID)
{
	return m_oCititesTable.DeleteWhereID(lID);
}
