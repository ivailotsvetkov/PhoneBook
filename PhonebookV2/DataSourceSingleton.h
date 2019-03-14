#pragma once
#include <atldbcli.h>
#include <iostream>
class CDataSourceSingleton
{
private:
	CDataSourceSingleton();
	static CDataSourceSingleton* instance;
	CDataSource m_oCDataSource;
	BOOL isOpened = false;
	void getDBPropSet(CDBPropSet& oCDBPropSet);
public:
	static CDataSourceSingleton* getInstance();
	CDataSource& getSource();
	BOOL OpenSource();
	BOOL CloseSource();
};