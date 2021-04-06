#pragma once
#include<windows.h>
#define ERROR_FILE_ISPE			0x88
#define ERROR_FILE_NOTPE		0x99
#define ERROR_FILE_READ_ERROR	0x77
#define ERROR_FILE_READ_SUCCESS	0x66
#define ERROR_OUT_OF_RANGE		0x55
typedef struct FileHeaderInfo {
	DWORD Machine;
	DWORD NumberOfSections;
	DWORD SizeOfOptionalHeader;
	DWORD Characteristics;
	DWORD TimeDataStamp;
	DWORD NtSignature;
	DWORD PointerToSymbolTable;
	DWORD NumberOfSymbols;
}*PFileHeaderInfo;

typedef struct OpHeaderInfo {
	DWORD Magic;
	DWORD SizeOfCode;
	DWORD SizeOfInitializedData;
	DWORD SizeOfUninitializedData;
	DWORD AddressOfEntryPoint;
	DWORD BaseOfCode;
	DWORD BaseOfData;
	DWORD ImageBase;
	DWORD SectionAlignment;
	DWORD FileAlignment;
	DWORD SizeOfImage;
	DWORD SizeOfHeaders;
	DWORD CheckSum;
	DWORD SubSystem;
	DWORD DllCharacteristics;
	DWORD NumberOfRvaAndSizes;
}*pOpHeaderInfo;

typedef struct DataDirInfo
{
	DWORD VirtualAddress;
	DWORD Size;
}pDataDirInfo;

struct ExportInfo
{
	DWORD Base;
	DWORD NumberOfFunctions;
	DWORD NumberOfNames;
	DWORD AddressOfFunctions;
	DWORD AddressOfNames;
	DWORD AddressOfNameOrdinals;
};

struct ImportInfo
{
	char DllName[100];
	DWORD OriginalFirstThunk;
	DWORD TimeDataStamp;
	DWORD ForwarderChain;
	DWORD Rva;
	DWORD FirstThunk;
};

struct ImportInfo2
{
	DWORD ThunkRva;
	DWORD ThunkOffset;
	DWORD ThunkValue;
	WORD Hint;
	char FuncName[40];
};

struct RelocaInfo {
	char Section[20];
	DWORD Rva;
	char Count[20];
};

struct RelocaInfo2 {
	DWORD Rva;
	DWORD Offset;
	DWORD Va;
	DWORD Data;
};

struct ResInfo {
	WCHAR szName[20];
};

struct ResInfo2 {
	WCHAR szName[70];
	DWORD Rva;
	DWORD Foa;
	DWORD Size;
};

typedef struct stcSectionInfo
{
	char sName[9];
	DWORD dwVRva;
	DWORD dwVSize;
	DWORD dwRFoa;
	DWORD dwRSize;
	DWORD dwFlag;
}stSecInfo;