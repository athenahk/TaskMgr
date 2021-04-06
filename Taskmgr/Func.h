#pragma once
#include<windows.h>
#include<vector>
#include"data.h"
struct CExport {
	DWORD Ordinal;
	DWORD Rva;
	DWORD Foa;
	CHAR szString[100];
};
struct st {
	CExport* p1;
	int count1;
};
extern "C" _declspec(dllexport) BOOL isPeFile(char* pBuf);
extern "C" _declspec(dllexport) void AnalysisFileHeader(char* pBuf);
extern "C" _declspec(dllexport) void AnalysisOptionalHeader(char* pBuf);
extern "C" _declspec(dllexport) void AnalysisSectionHeader(char* pBuf);
extern "C" _declspec(dllexport) DWORD RvaToFoa(char* pBuf, DWORD dwRva);
extern "C" _declspec(dllexport) st AnalysisExport(char* pBuf);
extern "C" _declspec(dllexport) void AnalysisImportTable(char* pBuf, vector<ImportInfo> & vecImporta, vector<vector<ImportInfo2>> & vecImportb);
extern "C" _declspec(dllexport) void AnalyzeBaseReloc(char* pBuf, vector<RelocaInfo> & vecRelocaInfo1, vector<vector<RelocaInfo2>> & vecRelocaInfo2);
extern "C" _declspec(dllexport) void AnalyzeRes(char* pBuf, vector<ResInfo>& vecResInfo1, vector<vector<ResInfo2>>& vecResInfo2);

