#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "CitiesTable.h"

using namespace std;
//Operations
/*
BOOL CCitiesTable::SelectAll(CCitiesPtrArray& oCitiesArray)
{
	CDataSource oDataSource;
	CSession oSession;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));

	//Свързване към база данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}

	CString strQuery = _T("SELECT * FROM CITIES");

	// Изпълняваме командата
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}
	// Прочитаме всички данни
	while (MoveNext() == S_OK && DB_S_ENDOFROWSET)
	{
		CITIES* city = new CITIES;
		*city = m_recCity;
		oCitiesArray.Add(city);
	}
	// Затваряме командата, сесията и връзката с базата данни.
	Close();
	oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CCitiesTable::SelectWhereID(const long lID, CITIES& recCities)
{
	CDataSource oDataSource;
	CSession oSession;


	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));

	//Свързване към база данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}
	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID=%ld"), lID);
	// Изпълняваме командата
	hResult = Open(oSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Query: " + strQuery));
		Close();
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}
	while (MoveNext() == S_OK && DB_S_ENDOFROWSET)
	{
		recCities = m_recCity;
	}
	Close();
	oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CCitiesTable::DeleteWhereID(long lID) {
	CDataSource oDataSource;
	CSession oSession;

	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));
	CDBPropSet queuerPropSet;
	queuerPropSet.SetGUID(DBPROPSET_ROWSET);
	queuerPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetChange, true);
	queuerPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	//Свързване към база данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);


	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}
	// Конструираме заявката


	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID=%ld"), lID);

	// Изпълняваме командата
	hResult = Open(oSession, strQuery, &queuerPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		AfxMessageBox(_T("Query: " + strQuery));
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}
	if (hResult = MoveFirst() != S_OK)
	{
		AfxMessageBox(_T("No element found " + hResult));

		oSession.Close();
		oDataSource.Close();
		return FALSE;
	}

	hResult = __super::Delete();

	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to delete. Error: %d"), hResult);
		Close();
		oDataSource.Close();
		oSession.Close();
		return FALSE;
	}

	Close();
	oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CCitiesTable::Insert(const CITIES& recCities) {
	CDataSource oDataSource;
	CSession oSession;


	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));
	CDBPropSet queuerPropSet;
	queuerPropSet.SetGUID(DBPROPSET_ROWSET);
	queuerPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetChange, true);
	queuerPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	//Свързване към база данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}
	// Конструираме заявката
	CString strQuery;
	strQuery.Format(_T("SELECT TOP 0 * FROM CITIES"));
	// Изпълняваме командата
	hResult = Open(oSession, strQuery, &queuerPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Query: " + strQuery));
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}
	while (MoveFirst() == S_OK) {
		CITIES* city = new CITIES;
		*city = recCities;
	}
	hResult = __super::Insert(1);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to insert. Error: %d"), hResult);
		Close();
		oDataSource.Close();
		oSession.Close();
		return FALSE;
	}
	Close();
	oSession.Close();
	oDataSource.Close();
	return TRUE;
}

BOOL CCitiesTable::UpdateWhereID(const long lID, const CITIES& recCities) {
	CDataSource oDataSource;
	CSession oSession;


	CDBPropSet oDBPropSet(DBPROPSET_DBINIT);
	oDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));
	CDBPropSet queuerPropSet;
	queuerPropSet.SetGUID(DBPROPSET_ROWSET);
	queuerPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	queuerPropSet.AddProperty(DBPROP_IRowsetChange, true);
	queuerPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	//Свързване към база данни
	HRESULT hResult = oDataSource.Open(_T("SQLOLEDB.1"), &oDBPropSet);


	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to connect to SQL Server database. Error: %d"), hResult);
		return FALSE;
	}

	// Отваряме сесия
	hResult = oSession.Open(oDataSource);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		oDataSource.Close();

		return FALSE;
	}
	// Конструираме заявката

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM CITIES WHERE ID=%d"), lID);
	// Изпълняваме командата
	hResult = Open(oSession, strQuery, &queuerPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		oSession.Close();
		oDataSource.Close();

		return FALSE;
	}
	if ((hResult = MoveFirst()) == S_OK)
	{
		if (recCities.lUpdateCounter != m_recCity.lUpdateCounter)
		{
			Close();
			oDataSource.Close();
			oSession.Close();
			return FALSE;
		}
		m_recCity = recCities;
		m_recCity.lUpdateCounter++;
	}
	hResult = __super::SetData(1);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to update. Error: %d"), hResult);
		Close();
		oDataSource.Close();
		oSession.Close();
		return FALSE;
	}
	Close();
	oSession.Close();
	oDataSource.Close();
	return TRUE;
}
*/