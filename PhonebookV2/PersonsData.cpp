#include "stdafx.h"
#include "PersonsData.h"

CPersonsData::CPersonsData()
{

}

BOOL CPersonsData::SelectAll(CPersonsPtrArray& oPersonPtrArray)
{
	return	m_oPersonsTable.SelectAll(oPersonPtrArray);
}

BOOL CPersonsData::SelectWhereID(const long lID, CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS)
{
	if (!m_oPersonsTable.SelectWhereID(lID, oCPERSONWITHPHONENUMBERS.m_oPersons))
	{
		return FALSE;
	}
	return m_oPhoneNumbersTable.SelectWhereID(lID, oCPERSONWITHPHONENUMBERS.m_PhoneNumberPtrArray, _T("PERSON_ID"));
}

BOOL CPersonsData::UpdateWhereID(const long lID, const CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS)
{
	CSession oCSession;
	oCSession.Open(CDataSourceSingleton::getInstance()->getSource());
	CPersonsTable oPersonTable(oCSession);
	CPhoneNumbersTable oPhoneNumbersUpdateSession(oCSession);
	oCSession.StartTransaction();

	if (!oPersonTable.UpdateWhereID(lID, oCPERSONWITHPHONENUMBERS.m_oPersons))
	{
		oCSession.Abort();
		return FALSE;
	}

	CPhoneNumbersTable oPhoneNumbersTable;
	CPhoneNumbersPtrArray oDBArray;
	oPhoneNumbersTable.SelectWhereID(lID, oDBArray, _T("PERSON_ID"));
	// ííì
	BOOL bFound = FALSE;
	for (int i = 0; i < oDBArray.GetCount(); i++)
	{
		bFound = FALSE;
		PHONE_NUMBERS* pDBPhoneNumber = oDBArray.GetAt(i);
		for (int j = 0; j < oCPERSONWITHPHONENUMBERS.m_PhoneNumberPtrArray.GetCount(); j++)
		{
			PHONE_NUMBERS* pPhoneNumber = oCPERSONWITHPHONENUMBERS.m_PhoneNumberPtrArray.GetAt(j);
			if (pPhoneNumber->lID == 0)
			{
				continue;
			}
			if (pPhoneNumber->lID == pDBPhoneNumber->lID)
			{
				if (!oPhoneNumbersUpdateSession.UpdateWhereID(pPhoneNumber->lID, *pPhoneNumber))
				{
					oCSession.Abort();
					return FALSE;
				}
				bFound = TRUE;
			}

		}

		if (!bFound)
		{
			if (!oPhoneNumbersUpdateSession.DeleteWhereID(pDBPhoneNumber->lID))
			{
				oCSession.Abort();
				return FALSE;
			}
		}
	}


	for (int i = 0; i < oCPERSONWITHPHONENUMBERS.m_PhoneNumberPtrArray.GetCount(); i++)
	{
		PHONE_NUMBERS* pPhoneNumber = oCPERSONWITHPHONENUMBERS.m_PhoneNumberPtrArray.GetAt(i);
		if (pPhoneNumber->lID == 0)
		{
			if (!oPhoneNumbersUpdateSession.Insert(*pPhoneNumber))
			{
				oCSession.Abort();
				return FALSE;
			}
		}
	}// for

	oCSession.Commit();
	return TRUE;
}



BOOL CPersonsData::Insert(const CPERSONWITHPHONENUMBERS & recPersonWithPhoneNumbers)
{
	CSession oCSession;
	oCSession.Open(CDataSourceSingleton::getInstance()->getSource());
	CPersonsTable oPersonTable(oCSession);
	CPhoneNumbersTable oPhoneNumbersTable(oCSession);

	oCSession.StartTransaction();

	if (oPersonTable.Insert(recPersonWithPhoneNumbers.m_oPersons))
	{
		oCSession.Abort();
		return FALSE;
	}
	for (int i = 0; i < recPersonWithPhoneNumbers.m_PhoneNumberPtrArray.GetCount(); i++)
	{
		recPersonWithPhoneNumbers.m_PhoneNumberPtrArray.GetAt(i)->nPersonId = recPersonWithPhoneNumbers.m_oPersons.lID;
		if (!oPhoneNumbersTable.Insert(*recPersonWithPhoneNumbers.m_PhoneNumberPtrArray.GetAt(i)))
		{
			oCSession.Abort();
			return FALSE;
		}

	}
	oCSession.Commit();
	return	TRUE;
}



BOOL CPersonsData::DeleteWhereID(const long lID)
{
	CSession oCSession;
	oCSession.Open(CDataSourceSingleton::getInstance()->getSource());
	CPersonsTable oPersonTable(oCSession);
	CPhoneNumbersTable oPhoneNumbersTable(oCSession);
	CPhoneNumbersPtrArray oPhoneNumbersPtrArray;
	oCSession.StartTransaction();

	if (!oPhoneNumbersTable.SelectWhereID(lID, oPhoneNumbersPtrArray, _T("PERSON_ID")))
	{
		oCSession.Abort();
		return FALSE;
	}
	for (int i = 0; i < oPhoneNumbersPtrArray.GetCount(); i++)
	{
		if (oPhoneNumbersTable.DeleteWhereID(oPhoneNumbersPtrArray.GetAt(i)->lID));
	}
	if (!oPersonTable.DeleteWhereID(lID))
	{
		oCSession.Abort();
		return FALSE;
	}
	oCSession.Commit();
	return TRUE;
}