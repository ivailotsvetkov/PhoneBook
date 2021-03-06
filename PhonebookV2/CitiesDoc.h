#pragma once
#include "CitiesData.h"
#include "FreeMemoryArray.h"
/// <summary>Клас за работа с документа CITIES</summary>
class CCitiesDoc : public CDocument
{
	//Constructor/Destructor
protected: // create from serialization only
	CCitiesDoc();
	virtual ~CCitiesDoc();
	DECLARE_DYNCREATE(CCitiesDoc)

	// Attributes
private:
	CCitiesData oCCitiesData;
public:
	CCitiesPtrArray  oCCitiesPtrArray;
	// Operations
public:
	BOOL SelectAll(CCitiesPtrArray& oCitiesArray);
	BOOL SelectWhereID(const long lID, CITIES& recCities);
	BOOL UpdateWhereID(const long lID, const CITIES& recCities);
	BOOL Insert(const CITIES& recCities);
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
