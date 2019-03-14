#include "stdafx.h"
#include "DataSourceSingleton.h"

CDataSourceSingleton* CDataSourceSingleton::instance = NULL;

CDataSourceSingleton::CDataSourceSingleton()
{

}

CDataSourceSingleton * CDataSourceSingleton::getInstance()
{
	if (!instance)
		instance = new CDataSourceSingleton;
	return instance;
}

CDataSource& CDataSourceSingleton::getSource()
{
	return m_oCDataSource;
}

BOOL CDataSourceSingleton::OpenSource()
{
	HRESULT hr = S_OK;
	if (!isOpened)
	{
		CDBPropSet oCDBPropSet(DBPROPSET_DBINIT);
		getDBPropSet(oCDBPropSet);
		hr = m_oCDataSource.Open(_T("SQLOLEDB.1"), &oCDBPropSet);
	}

	if (hr != S_OK)
		return FALSE;

	isOpened = true;
	return TRUE;
}

BOOL CDataSourceSingleton::CloseSource()
{
	if (isOpened)
		m_oCDataSource.Close();
	return TRUE;
}

void CDataSourceSingleton::getDBPropSet(CDBPropSet& oCDBPropSet)
{
	oCDBPropSet.AddProperty(DBPROP_INIT_DATASOURCE, _T("IVKO"));
	oCDBPropSet.AddProperty(DBPROP_AUTH_INTEGRATED, _T("SSPI"));
	oCDBPropSet.AddProperty(DBPROP_TRUSTEE_AUTHENTICATION, _T("Yes"));
	oCDBPropSet.AddProperty(DBPROP_INIT_CATALOG, _T("PhoneBook"));
	oCDBPropSet.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	oCDBPropSet.AddProperty(DBPROP_INIT_LCID, 1033L);
	oCDBPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oCDBPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	oCDBPropSet.AddProperty(DBPROP_INIT_LCID, static_cast<short>(4));
}
