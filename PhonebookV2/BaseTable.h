#pragma once
#include <atldbcli.h>
#include <iostream>
#include "stdafx.h"
#include "FreeMemoryArray.h"
#include "DataSourceSingleton.h"

template<class ACCESSOR, class TYPE>
class CBaseTable :protected CCommand<CAccessor<ACCESSOR>>
{
public:
	CBaseTable(long lUpdateCounterOffset);
	CBaseTable(long lUpdateCounterOffset, CSession& oCSession);
	virtual ~CBaseTable();
	BOOL OpenSession();
	BOOL CloseSession();
	BOOL OuterSession = FALSE;
	/// <summary>����� �� �������� �� ������ TYPE ������ �� ������
	/// <para>freeMemoryArray � �����, ����� �� ���� �������� ��� TYPE pointers</para>  
	/// <seealso cref="CCitiesDoc::SelectAll"/>  
	///<returns>����� TRUE ��� �����, FALSE ��� �������</returns>
	/// </summary>  
	BOOL SelectAll(CFreeMemoryArray<TYPE>& freeMemoryArray);
	/// <summary>����� �� �������� �� TYPE ����� �� ������
	/// <para>recStruct � �����, ����� �� ���� �������� ��� TYPE pointer</para>  
	/// <seealso cref="CCitiesDoc::SelectWhereID"/>  
	///<returns>����� TRUE ��� �����, FALSE ��� �������</returns>
	/// </summary>  

	BOOL SelectWhereID(const long lID, TYPE& recStruct);
	/// <summary>����� �� ����������� �� TYPE ����� �� ������
	/// /// <para>recStruct � �����, ����� �� ���� �������� ��� TYPE pointer</para>  
	/// <seealso cref="CCitiesDoc::UpdateWhereID"/>  
	///<returns>����� TRUE ��� �����, FALSE ��� �������</returns>
	/// </summary>  
	BOOL SelectWhereID(const long lID, CFreeMemoryArray<TYPE> & freeMemoryArray, CString strForeignKey);
	BOOL UpdateWhereID(const long lID, const TYPE& recStruct);
	/// <summary>����� �� �������� �� TYPE ����� � ������
  /// <para>recStruct � �����, ����� �� ���� ������ � ������</para>  
	/// <seealso cref="CCitiesDoc::Insert"/>  
	///<returns>����� TRUE ��� �����, FALSE ��� �������</returns>
	/// </summary>  

	/// <summary>����� �� ���������� �� TYPE ����� �� ������
	/// /// <para>lID � long, ����� ������� ID �� ������, ����� �� ���� ���������</para>  
	/// <seealso cref="CCitiesDoc::DeleteWhereID"/>  
	///<returns>����� TRUE ��� �����, FALSE ��� �������</returns>
	/// </summary>  
	BOOL Insert(const TYPE& recStruct);
	BOOL DeleteWhereID(const long lID);

	BOOL DeleteWhereID(const long lID, CString strForeignKey);
protected:
	virtual	TYPE& GetAccessorData() = 0;
	virtual	CString GetTableName() = 0;

private:
	long m_lUpdateCounterOffset;
	CSession * m_CSession;
	BOOL getUpdatePropSet(CDBPropSet& oCDBPropSet);
};

template<class ACCESSOR, class TYPE>
CBaseTable<ACCESSOR, TYPE>::CBaseTable(long lUpdateCounter)
{
	m_lUpdateCounterOffset = lUpdateCounter;
	m_CSession = new CSession();
}

template<class ACCESSOR, class TYPE>
CBaseTable<ACCESSOR, TYPE>::CBaseTable(long lUpdateCounterOffset, CSession& oCSession)
{
	m_lUpdateCounterOffset = lUpdateCounterOffset;
	m_CSession = &oCSession;
	OuterSession = TRUE;
}

template<class ACCESSOR, class TYPE>
CBaseTable<ACCESSOR, TYPE>::~CBaseTable()
{
	if (!OuterSession)
		delete m_CSession;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::OpenSession()
{
	if (!OuterSession)
	{
		if (m_CSession->Open(CDataSourceSingleton::getInstance()->getSource()))
		{
			return FALSE;
		}
	}
	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::CloseSession()
{
	if (!OuterSession)
		m_CSession->Close();

	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::SelectAll(CFreeMemoryArray<TYPE> & freeMemoryArray)
{

	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"));
		return FALSE;
	}

	CString strQuery;
	strQuery.Format(_T("SELECT * FROM %s"), GetTableName());
	// ����������� ���������
	HRESULT hResult = Open(*m_CSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();


		return FALSE;
	}
	// ��������� ������ �����
	while ((hResult = MoveNext()) == S_OK)
	{
		TYPE* pType = new TYPE;
		*pType = GetAccessorData();
		freeMemoryArray.Add(pType);
	}

	if (hResult != DB_S_ENDOFROWSET)
	{
		AfxMessageBox(_T("Row ended" + hResult));
		CloseSession();
		return FALSE;
	}

	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();
	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::SelectWhereID(const long lID, TYPE & recStruct)
{



	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"));
		return FALSE;
	}


	CString strQuery;// = _T("SELECT * FROM %s WHERE ID=%ld", GetTableName(), ID);
	strQuery.Format(_T("SELECT * FROM %s WHERE ID=%ld"), GetTableName(), lID);
	// ����������� ���������
	HRESULT  hResult = Open(*m_CSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ������ �����
	if ((hResult = MoveFirst()) == S_OK)
	{
		recStruct = GetAccessorData();
	}
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();
	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::SelectWhereID(const long lID, CFreeMemoryArray<TYPE> & freeMemoryArray, CString strForeignKey)
{

	HRESULT hResult = S_OK;
	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		return FALSE;
	}


	CString strQuery;// = _T("SELECT * FROM %s WHERE ID=%ld", GetTableName(), ID);
	strQuery.Format(_T("SELECT * FROM %s WHERE %s=%ld"), GetTableName(), strForeignKey, lID);
	// ����������� ���������
	hResult = Open(*m_CSession, strQuery);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ������ �����
	while ((hResult = MoveNext()) == S_OK)
	{
		TYPE* pType = new TYPE;
		*pType = GetAccessorData();
		freeMemoryArray.Add(pType);
	}
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();


	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::UpdateWhereID(const long lID, const TYPE & recStruct)
{

	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	getUpdatePropSet(oUpdateDBPropSet);

	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"));
		return FALSE;
	}


	CString strQuery;//= _T("SELECT * FROM %s WHERE ID=%ld"), GetTableName, lID);
	strQuery.Format(_T("SELECT * FROM %s WHERE ID=%ld"), GetTableName(), lID);
	// ����������� ���������
	HRESULT hResult = Open(*m_CSession, strQuery, &oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ������ �����
	if (MoveFirst() == S_OK)
	{
		BYTE* pRecDBStruct = (BYTE*)&recStruct;
		BYTE* pAccessorDBStruct = (BYTE*)&GetAccessorData();
		long* pUpdateCounter = (long*)(pRecDBStruct + m_lUpdateCounterOffset);
		long* pAccessorUpdateCounter = (long*)(pAccessorDBStruct + m_lUpdateCounterOffset);
		if (*pUpdateCounter != *pAccessorUpdateCounter)
		{
			AfxMessageBox(_T("The current roll is being updated right now " + hResult));
			Close();
			CloseSession();
			return FALSE;
		}
		GetAccessorData() = recStruct;
		*pAccessorUpdateCounter++;
	}
	hResult = SetData(1);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to update. Error: %d"), hResult);

		Close();
		CloseSession();
		return FALSE;
	}
	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();
	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::DeleteWhereID(const long lID)
{

	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	getUpdatePropSet(oUpdateDBPropSet);
	HRESULT hResult = S_OK;

	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		return FALSE;
	}


	CString strQuery; //= _T("SELECT * FROM %s WHERE ID=%ld"), GetTableName, lID);
	strQuery.Format(_T("SELECT * FROM %s WHERE ID=%ld"), GetTableName(), lID);
	// ����������� ���������
	hResult = Open(*m_CSession, strQuery, &oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();
		return FALSE;
	}
	// ��������� ������ �����
	hResult = MoveFirst();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to find an element "), hResult);
		Close();
		CloseSession();
		return FALSE;
	}
	hResult = Delete();
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to delete " + hResult));
		Close();
		CloseSession();
		return FALSE;
	}

	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();
	return TRUE;
}

template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::getUpdatePropSet(CDBPropSet& oCDPropSet)
{
	oCDPropSet.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
	oCDPropSet.AddProperty(DBPROP_IRowsetScroll, true);
	oCDPropSet.AddProperty(DBPROP_IRowsetChange, true);
	oCDPropSet.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE);
	return TRUE;
}


template<class ACCESSOR, class TYPE>
BOOL CBaseTable<ACCESSOR, TYPE>::Insert(const TYPE & recStruct)
{

	CDBPropSet oUpdateDBPropSet(DBPROPSET_ROWSET);
	getUpdatePropSet(oUpdateDBPropSet);
	HRESULT hResult = NULL;

	if (!OpenSession())
	{
		AfxMessageBox(_T("Unable to open session. Error: %d"), hResult);
		return FALSE;
	}



	CString strQuery;// = _T("SELECT * FROM %s WHERE ID=%ld"), GetTableName, lID);
	strQuery.Format(_T("SELECT TOP 0 * FROM %s"), GetTableName());
	// ����������� ���������
	hResult = Open(*m_CSession, strQuery, &oUpdateDBPropSet);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Error executing query. Error: " + hResult));
		CloseSession();

		return FALSE;
	}
	// ��������� ������ �����
	TYPE* oType = new TYPE;
	while (MoveFirst() == S_OK) {

		*oType = recStruct;
	}
	hResult = Insert(*oType);
	if (FAILED(hResult))
	{
		AfxMessageBox(_T("Unable to insert. Error: %d"), hResult);
		Close();
		CloseSession();
		return FALSE;
	}
	// ��������� ���������, ������� � �������� � ������ �����. 
	Close();
	CloseSession();

	return TRUE;
}