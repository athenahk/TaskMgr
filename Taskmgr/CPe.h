#pragma once
#include"data.h"
#include<vector>
#include "afxdialogex.h"
using std::vector;
class CPe {
private:
	//char* m_pBuf;
	CString m_szFilePath;
	PIMAGE_DOS_HEADER m_pDos;
	
	PIMAGE_FILE_HEADER m_pFileHeader;
	PIMAGE_OPTIONAL_HEADER m_pOptionalHeader;
	PIMAGE_DATA_DIRECTORY m_pData;
	PIMAGE_EXPORT_DIRECTORY m_pExport;
	PIMAGE_IMPORT_DESCRIPTOR m_pImport;
	PIMAGE_SECTION_HEADER m_pSection;
	FileHeaderInfo m_FileHeaderInfo;
	OpHeaderInfo m_OpHeaderInfo;
public:
	char* m_pBuf;
	vector<stSecInfo>m_vecSecInfo;
	PIMAGE_NT_HEADERS m_pNt;
	CPe() {};
	~CPe() { delete[] m_pBuf; }
	void SetFilePath(TCHAR* szFilePath);
	void  ReadPE();
	void InitVectorSec();
	BOOL IsPeFile();
	PIMAGE_SECTION_HEADER GetSectionHeader();
	PFileHeaderInfo GetFileHeaderInfo();
	pOpHeaderInfo GetOpHeaderInfo();
	vector<DataDirInfo> GetDataDirInfo();
	DWORD RvaToFoa(char* pBuf, DWORD dwRva);
	ExportInfo GetExportInfo();
	PIMAGE_DATA_DIRECTORY GetPData(); 
	DWORD CalcFromFoa(_In_ DWORD Foa, _Out_ DWORD& Rva, _Out_ DWORD& Va, _Out_ char* szName);
	DWORD CstringToHex(CString str);
	DWORD CalcFromRva(_In_ DWORD Rva, _Out_ DWORD& Foa, _Out_ DWORD& Va, _Out_ char* szName);
	DWORD CalcFromVa(_In_ DWORD Va, _Out_ DWORD& Rva, _Out_ DWORD& Foa, _Out_ char* szName);
};