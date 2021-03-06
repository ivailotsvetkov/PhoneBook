
// PhonebookV2Doc.cpp : implementation of the CPhonebookV2Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PhonebookV2.h"
#endif

#include "CitiesDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPhonebookV2Doc

IMPLEMENT_DYNCREATE(CCitiesDoc, CDocument)




// CPhonebookV2Doc construction/destruction

CCitiesDoc::CCitiesDoc()
{
	// TODO: add one-time construction code here

}

CCitiesDoc::~CCitiesDoc()
{

}
//Operations
BOOL CCitiesDoc::SelectAll(CCitiesPtrArray & oCitiesArray)
{
	return oCCitiesData.SelectAll(oCCitiesPtrArray);
}

BOOL CCitiesDoc::SelectWhereID(const long lID, CITIES & recCities)
{
	return oCCitiesData.SelectWhereID(lID, recCities);
}

BOOL CCitiesDoc::UpdateWhereID(const long lID, const CITIES & recCities)
{
	CITIES * m_pCities = new CITIES;
	*m_pCities = recCities;
	for (int i = 0; i < oCCitiesPtrArray.GetCount(); i++)
	{
		if (oCCitiesPtrArray.GetAt(i)->lID == lID)
		{
			oCCitiesPtrArray.SetAt(i, m_pCities);
		}
	}
	return oCCitiesData.UpdateWhereID(lID, recCities);

}

BOOL CCitiesDoc::Insert(const CITIES & recCities)
{
	CITIES* oCities = new CITIES;
	*oCities = recCities;
	oCCitiesPtrArray.Add(oCities);
	return oCCitiesData.Insert(recCities);
}

BOOL CCitiesDoc::DeleteWhereID(const long lID)
{
	for (int i = 0; i < oCCitiesPtrArray.GetCount(); i++)
	{
		if (oCCitiesPtrArray.GetAt(i)->lID == lID)
		{
			oCCitiesPtrArray.RemoveAt(i);
		}
	}
	return oCCitiesData.DeleteWhereID(lID);
}

BOOL CCitiesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	oCCitiesData.SelectAll(oCCitiesPtrArray);
	return TRUE;
}




// CPhonebookV2Doc serialization

void CCitiesDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPhonebookV2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPhonebookV2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPhonebookV2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPhonebookV2Doc diagnostics

#ifdef _DEBUG
void CCitiesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCitiesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

BEGIN_MESSAGE_MAP(CCitiesDoc, CDocument)


END_MESSAGE_MAP()

// CPhonebookV2Doc commands
