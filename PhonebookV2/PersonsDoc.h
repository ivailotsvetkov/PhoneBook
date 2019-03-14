#pragma once
#include "FreeMemoryArray.h"
#include "PersonsData.h"
#include "CitiesData.h"
/// <summary>Клас за работа с документа CITIES</summary>
class CPersonsDoc : public CDocument
{
	//Constructor/Destructor
protected: // create from serialization only
	CPersonsDoc();
	virtual ~CPersonsDoc();
	DECLARE_DYNCREATE(CPersonsDoc)
	// Attributes
public:
	CCitiesData m_CitiesData;
	CPersonsData m_PersonData;
	CPersonsPtrArray m_PersonsPtrArray;
	// Operations
public:
	PERSONS* GetPersonByID(const long lID);
	BOOL SelectAll(CPersonsPtrArray& oPersonsPtrArray);
	BOOL SelectWhereID(const long lID, CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS);
	BOOL UpdateWhereID(const long lID, const CPERSONWITHPHONENUMBERS& oCPERSONWITHPHONENUMBERS);
	BOOL Insert(const CPERSONWITHPHONENUMBERS& recPersonWithPhoneNumbers);
	BOOL DeleteWhereID(const long lID);
	// Overrides
public:
	virtual BOOL OnNewDocument();

	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS


};