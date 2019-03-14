#pragma once
#include <afxtempl.h>
#include "FreeMemoryArray.h"

#define SMALL_STRING_SIZE 8
#define DEFAULT_STRING_SIZE 32
#define LARGE_STRING_SIZE 64
struct CITIES
{
	long lID;
	long lUpdateCounter;
	TCHAR szCityName[DEFAULT_STRING_SIZE + 1];
	TCHAR szAreaName[SMALL_STRING_SIZE + 1];
	CITIES() {
		SecureZeroMemory(this, sizeof(*this));
	}
};

struct PERSONS
{
	long lID;
	long lUpdateCounter;
	TCHAR szFirstName[DEFAULT_STRING_SIZE + 1];
	TCHAR szMiddleName[DEFAULT_STRING_SIZE + 1];
	TCHAR szLastName[DEFAULT_STRING_SIZE + 1];
	TCHAR szUCN[DEFAULT_STRING_SIZE + 1];
	int nCityId;
	TCHAR szAddress[LARGE_STRING_SIZE + 1];
	PERSONS() {
		SecureZeroMemory(this, sizeof(*this));
	}
};

struct PHONE_NUMBERS
{
	long lID;
	long lUpdateCounter;
	long nPersonId;
	long nPhoneTypeId;
	long nPhone;
	PHONE_NUMBERS() {
		SecureZeroMemory(this, sizeof(*this));
	}
};

struct PHONE_TYPES
{
	long lID;
	long lUpdateCounter;
	TCHAR szPhoneType[DEFAULT_STRING_SIZE + 1];
	PHONE_TYPES() {
		SecureZeroMemory(this, sizeof(*this));
	}
};

typedef CFreeMemoryArray<PHONE_NUMBERS> CPhoneNumbersPtrArray;

class CPERSONWITHPHONENUMBERS
{

public:
	CPERSONWITHPHONENUMBERS::CPERSONWITHPHONENUMBERS()
	{
	}

	PERSONS  m_oPersons;
	CPhoneNumbersPtrArray m_PhoneNumberPtrArray;

};
typedef CFreeMemoryArray<CPERSONWITHPHONENUMBERS> CPersonWithPhoneNumbersPtrArray;

typedef CFreeMemoryArray<CITIES> CCitiesPtrArray;
typedef CFreeMemoryArray<PERSONS> CPersonsPtrArray;
typedef CFreeMemoryArray<PHONE_TYPES> CPhoneTypesPtrArray;



/// <summary>Enum съдържащ различните действия, които могат да бъдат изпълнени</summary>
enum Action
{
	ActionSelect,
	ActionEdit,
	ActionInsert,
	ActionDelete
};