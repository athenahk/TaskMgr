#include"pch.h"
#include"CPe.h"

void CPe::SetFilePath(TCHAR* szFilePath)
{
	m_szFilePath = szFilePath;
}
void CPe::ReadPE()
{
	HANDLE hFile = CreateFile(m_szFilePath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	m_pBuf = new char [dwFileSize] {0};
	DWORD dwRealSize = 0;
	ReadFile(hFile, m_pBuf, dwFileSize, &dwRealSize, NULL);
	CloseHandle(hFile);
}

DWORD CPe::RvaToFoa(char* pBuf, DWORD dwRva)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pBuf;
	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)(pBuf + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);

	if (dwRva < pSectionHeader->PointerToRawData)
	{
		return dwRva;
	}
	for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++)
	{
		if (dwRva >= pSectionHeader[i].VirtualAddress && dwRva < pSectionHeader[i].VirtualAddress + pSectionHeader[i].SizeOfRawData)
			return dwRva - pSectionHeader[i].VirtualAddress + pSectionHeader[i].PointerToRawData;
	}
	return -1;
}

BOOL CPe::IsPeFile()
{
	m_pDos = (PIMAGE_DOS_HEADER)m_pBuf;
	if (m_pDos->e_magic != 0x5A4D)
		return FALSE;
	m_pNt = (PIMAGE_NT_HEADERS)(m_pBuf + m_pDos->e_lfanew);
	if (m_pNt->Signature != 0x4550)
		return FALSE;
	m_pFileHeader = (PIMAGE_FILE_HEADER)&m_pNt->FileHeader;
	m_pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)&m_pNt->OptionalHeader;
	m_pData = (PIMAGE_DATA_DIRECTORY)m_pOptionalHeader->DataDirectory;
	m_pExport = (PIMAGE_EXPORT_DIRECTORY)(m_pBuf + RvaToFoa(m_pBuf, m_pData[0].VirtualAddress));
	m_pImport = (PIMAGE_IMPORT_DESCRIPTOR)(m_pBuf + RvaToFoa(m_pBuf, m_pData[1].VirtualAddress));
	return TRUE;
}

void CPe::InitVectorSec()
{
	stSecInfo tempSec = { 0 };
	m_pSection = GetSectionHeader();
	for (int i = 0; i < m_pFileHeader->NumberOfSections; i++)
	{
		tempSec.dwRFoa = m_pSection[i].PointerToRawData;
		tempSec.dwRSize = m_pSection[i].SizeOfRawData;
		tempSec.dwVRva = m_pSection[i].VirtualAddress;
		tempSec.dwRSize = m_pSection[i].Misc.VirtualSize;
		strcpy_s(tempSec.sName, 9, (char*)m_pSection[i].Name);
		m_vecSecInfo.push_back(tempSec);
	}
}

PFileHeaderInfo CPe::GetFileHeaderInfo()
{
	m_FileHeaderInfo.Machine = m_pFileHeader->Machine;
	m_FileHeaderInfo.Characteristics = m_pFileHeader->Characteristics;
	m_FileHeaderInfo.NtSignature = m_pNt->Signature;
	m_FileHeaderInfo.NumberOfSections = m_pFileHeader->NumberOfSections;
	m_FileHeaderInfo.NumberOfSymbols = m_pFileHeader->NumberOfSymbols;
	m_FileHeaderInfo.PointerToSymbolTable = m_pFileHeader->PointerToSymbolTable;
	m_FileHeaderInfo.SizeOfOptionalHeader = m_pFileHeader->SizeOfOptionalHeader;
	m_FileHeaderInfo.TimeDataStamp = m_pFileHeader->TimeDateStamp;
	return &m_FileHeaderInfo;
}

pOpHeaderInfo CPe::GetOpHeaderInfo()
{
	m_OpHeaderInfo.AddressOfEntryPoint = m_pOptionalHeader->AddressOfEntryPoint;
	m_OpHeaderInfo.BaseOfCode = m_pOptionalHeader->BaseOfCode;
	m_OpHeaderInfo.BaseOfData = m_pOptionalHeader->BaseOfData;
	m_OpHeaderInfo.CheckSum = m_pOptionalHeader->CheckSum;
	m_OpHeaderInfo.DllCharacteristics = m_pOptionalHeader->DllCharacteristics;
	m_OpHeaderInfo.FileAlignment = m_pOptionalHeader->FileAlignment;
	m_OpHeaderInfo.ImageBase = m_pOptionalHeader->ImageBase;
	m_OpHeaderInfo.Magic = m_pOptionalHeader->Magic;
	m_OpHeaderInfo.NumberOfRvaAndSizes = m_pOptionalHeader->NumberOfRvaAndSizes;
	m_OpHeaderInfo.SectionAlignment = m_pOptionalHeader->SectionAlignment;
	m_OpHeaderInfo.SizeOfCode = m_pOptionalHeader->SizeOfCode;
	m_OpHeaderInfo.SizeOfHeaders = m_pOptionalHeader->SizeOfHeaders;
	m_OpHeaderInfo.SizeOfImage = m_pOptionalHeader->SizeOfImage;
	m_OpHeaderInfo.SizeOfInitializedData = m_pOptionalHeader->SizeOfInitializedData;
	m_OpHeaderInfo.SizeOfUninitializedData = m_pOptionalHeader->SizeOfUninitializedData;
	m_OpHeaderInfo.SubSystem = m_pOptionalHeader->Subsystem;
	return &m_OpHeaderInfo;
}

vector<DataDirInfo> CPe::GetDataDirInfo()
{
	vector<DataDirInfo> vDataDirInfo;
	DataDirInfo temp;
	for (int i = 0; i < 16; i++)
	{
		temp.VirtualAddress = m_pData[i].VirtualAddress;
		temp.Size = m_pData[i].Size;
		vDataDirInfo.push_back(temp);
	}
	return vDataDirInfo;
}


ExportInfo CPe::GetExportInfo()
{
	ExportInfo temp;
	temp.Base = m_pExport->Base;
	temp.NumberOfFunctions = m_pExport->NumberOfFunctions;
	temp.NumberOfNames = m_pExport->NumberOfNames;
	temp.AddressOfFunctions = m_pExport->AddressOfFunctions;
	temp.AddressOfNameOrdinals = m_pExport->AddressOfNameOrdinals;
	temp.AddressOfNames = m_pExport->AddressOfNames;
	return temp;
}

PIMAGE_DATA_DIRECTORY CPe::GetPData()
{
	return m_pData;
}

DWORD CPe::CalcFromRva(_In_ DWORD Rva, _Out_ DWORD& Foa, _Out_ DWORD& Va, _Out_ char* szName)
{
	if (Rva<m_vecSecInfo[0].dwVRva || Rva > m_vecSecInfo[m_pNt->FileHeader.NumberOfSections - 1].dwVRva + m_vecSecInfo[m_pNt->FileHeader.NumberOfSections - 1].dwVSize)
	{
		return ERROR_OUT_OF_RANGE;
	}
	// 先判断这个RVA 落在了哪个区段中
	PIMAGE_SECTION_HEADER p = m_pSection;
	DWORD i = 0;
	while (i < m_pNt->FileHeader.NumberOfSections)
	{
		// Foa = Rva - va + pData;

		// 当前目录大小
		if (Rva >= m_vecSecInfo[i].dwVRva && Rva < m_vecSecInfo[i].dwVRva + m_vecSecInfo[i].dwRSize)
		{

			//printf( "0x%08x-----", RVA );
				// 落在这个段中
				// VA -> RVA ： RVA = VA - 加载基址(去掉随机基址后的加载基址为默认加载基址)
				// 运行中程序 VA 为 0x41A000 它的 RVA 为： 41A000 - 400000 = 1A000
			Foa = Rva - m_vecSecInfo[i].dwVRva + m_vecSecInfo[i].dwRFoa;
			if (!Foa)
				return ERROR_OUT_OF_RANGE;
			if (szName)
			{
				memcpy_s(szName, 8, p->Name, 8);
			}
			Va = Rva + m_pNt->OptionalHeader.ImageBase;
			return ERROR_SUCCESS;
		}
		i++;
		p = (PIMAGE_SECTION_HEADER)((DWORD)m_pSection + i * sizeof(IMAGE_SECTION_HEADER));
	}
	return ERROR_OUT_OF_RANGE;
}

DWORD CPe::CalcFromVa(_In_ DWORD Va, _Out_ DWORD& Rva, _Out_ DWORD& Foa, _Out_ char* szName)
{
	if (Va < m_pNt->OptionalHeader.ImageBase || Va > m_pNt->OptionalHeader.ImageBase + m_pNt->OptionalHeader.SizeOfImage)
	{
		return ERROR_OUT_OF_RANGE;
	}
	Rva = Va - m_pNt->OptionalHeader.ImageBase;
	CalcFromRva(Rva, Foa, Va, szName);
	return 0;
}
DWORD CPe::CstringToHex(CString str)
{
	// TODO: 在此处添加实现代码.
	DWORD nLen = str.GetLength();
	TCHAR* p = str.GetBuffer();
	DWORD dwVal = 0;
	TCHAR t = 0;
	for (DWORD i = 0; i < nLen; i++)
	{
		t = p[i];
		switch (t)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			t -= 0x30;
			dwVal += t * pow(16, nLen - 1 - i);
		}
		break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		{
			t -= 0x37;
			dwVal += t * pow(16, nLen - 1 - i);
		}
		break;
		default:
			break;
		}
	}
	return dwVal;
}
DWORD CPe::CalcFromFoa(_In_ DWORD Foa, _Out_ DWORD& Rva, _Out_ DWORD& Va, _Out_ char* szName)
{
	// 先判断 FOA 是否合法
	if ((Foa <= 0) && Foa > (m_vecSecInfo[m_pNt->FileHeader.NumberOfSections - 1].dwRFoa + m_vecSecInfo[m_pNt->FileHeader.NumberOfSections - 1].dwRSize))
	{
		return ERROR_OUT_OF_RANGE;
	}
	PIMAGE_SECTION_HEADER p = GetSectionHeader();

	for (DWORD i = 0; i < m_pNt->FileHeader.NumberOfSections; i++)
	{
		// Rva = Foa + va - pData;
		if (Foa >= m_vecSecInfo[i].dwRFoa && Foa <= m_vecSecInfo[i].dwRFoa + m_vecSecInfo[i].dwRSize)
		{
			Rva = m_vecSecInfo[i].dwVRva + Foa - m_vecSecInfo[i].dwRFoa;
			Va = Rva + m_pNt->OptionalHeader.ImageBase;
			return ERROR_SUCCESS;
		}
	}

	return ERROR_OUT_OF_RANGE;
}

PIMAGE_SECTION_HEADER CPe::GetSectionHeader()
{
	return IMAGE_FIRST_SECTION(m_pNt);
}