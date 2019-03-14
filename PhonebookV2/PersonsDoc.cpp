#include "stdafx.h"
#include "PersonsDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CPersonsDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersonsDoc, CDocument)


END_MESSAGE_MAP()

CPersonsDoc::CPersonsDoc()
{

}

CPersonsDoc::~CPersonsDoc()
{

}

PERSONS * CPersonsDoc::GetPersonByID(const long lID)
{
	return m_PersonsPtrArray.GetAt(lID);
}

BOOL CPersonsDoc::SelectAll(CPersonsPtrArray& oPersonsPtrArray)
{

	return m_PersonData.SelectAll(oPersonsPtrArray);

}

BOOL CPersonsDoc::SelectWhereID(const long lID, CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS)
{

	return m_PersonData.SelectWhereID(lID, oCPERSONWITHPHONENUMBERS);
}

BOOL CPersonsDoc::UpdateWhereID(const long lID, const CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS)
{


	for (int i = 0; i < m_PersonsPtrArray.GetCount(); i++)
	{
		if (m_PersonsPtrArray.GetAt(i)->lID = oCPERSONWITHPHONENUMBERS.m_oPersons.lID)
		{
			*m_PersonsPtrArray.GetAt(i) = oCPERSONWITHPHONENUMBERS.m_oPersons;
			break;
		}
	}
	return m_PersonData.UpdateWhereID(lID, oCPERSONWITHPHONENUMBERS);

}

BOOL CPersonsDoc::Insert(const CPERSONWITHPHONENUMBERS& recPersonWithPhoneNumbers)
{
	if (!m_PersonData.Insert(recPersonWithPhoneNumbers))
	{
		return FALSE;
	}
	m_PersonsPtrArray.Add(new PERSONS(recPersonWithPhoneNumbers.m_oPersons));
	return TRUE;
}


BOOL CPersonsDoc::DeleteWhereID(const long lID)
{

	for (int i = 0; i < m_PersonsPtrArray.GetCount(); i++)
	{
		if (m_PersonsPtrArray.GetAt(i)->lID == lID)
		{
			m_PersonsPtrArray.RemoveAt(lID);
		}
	}
	return	m_PersonData.DeleteWhereID(lID);
}

BOOL CPersonsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (!m_PersonData.SelectAll(m_PersonsPtrArray))
	{
		return FALSE;
	}
	return TRUE;
}

void CPersonsDoc::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

void CPersonsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersonsDoc::Dump(CDumpContext & dc) const
{
	CDocument::Dump(dc);
}



