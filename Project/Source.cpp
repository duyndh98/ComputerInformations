#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
//#pragma comment(lib, "Secur32.lib")

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <comdef.h>
#include <string>
#include <map>
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include <math.h>
//#include <Security.h>

using namespace std;


#define DIV 1024
#define WIDTH 30

struct Detail
{
	string value, meaning;
};

map<WORD, Detail> ProcessorArchitecture = {
	{ 9,{ "PROCESSOR_ARCHITECTURE_AMD64", "x64 (AMD or Intel)" } },
	{ 5,{ "PROCESSOR_ARCHITECTURE_ARM", "ARM" } },
	{ 6,{ "PROCESSOR_ARCHITECTURE_IA64", "Intel Itanium - based" } },
	{ 0,{ "PROCESSOR_ARCHITECTURE_INTEL", "x86" } },
	{ 0xffff,{ "PROCESSOR_ARCHITECTURE_UNKNOWN", "Unknown architecture" } }
};

map<DWORD, Detail> ProcessorType = {
	{ 386,{ "PROCESSOR_INTEL_386", "" } },
	{ 486,{ "PROCESSOR_INTEL_486", "" } },
	{ 586,{ "PROCESSOR_INTEL_PENTIUM", "" } },
	{ 2200,{ "PROCESSOR_INTEL_IA64", "" } },
	{ 8664,{ "PROCESSOR_AMD_X8664", "" } },
	{ 0,{ "PROCESSOR_ARM", "" } }
};


map<DWORD, Detail> ProductType = {
	{ 0x00000006,{ "PRODUCT_BUSINESS", "Business" } },
	{ 0x00000010,{ "PRODUCT_BUSINESS_N", "Business N" } },
	{ 0x000000B2,{ "PRODUCT_CLOUD", "Windows 10 S" } },
	{ 0x000000B3,{ "PRODUCT_CLOUDN", "Windows 10 S N" } },
	{ 0x00000012,{ "PRODUCT_CLUSTER_SERVER", "HPC Edition" } },
	{ 0x00000040,{ "PRODUCT_CLUSTER_SERVER_V", "Server Hyper Core V" } },
	{ 0x00000065,{ "PRODUCT_CORE", "Windows 10 Home" } },
	{ 0x00000063,{ "PRODUCT_CORE_COUNTRYSPECIFIC", "Windows 10 Home China" } },
	{ 0x00000062,{ "PRODUCT_CORE_N", "Windows 10 Home N" } },
	{ 0x00000064,{ "PRODUCT_CORE_SINGLELANGUAGE", "Windows 10 Home Single Language" } },
	{ 0x00000050,{ "PRODUCT_DATACENTER_EVALUATION_SERVER", "Server Datacenter (evaluation installation)" } },
	{ 0x00000008,{ "PRODUCT_DATACENTER_SERVER", "Server Datacenter (full installation)" } },
	{ 0x0000000C,{ "PRODUCT_DATACENTER_SERVER_CORE", "Server Datacenter (core installation)" } },
	{ 0x00000027,{ "PRODUCT_DATACENTER_SERVER_CORE_V", "Server Datacenter without Hyper-V (core installation)" } },
	{ 0x00000025,{ "PRODUCT_DATACENTER_SERVER_V", "Server Datacenter without Hyper-V (full installation)" } },
	{ 0x00000079,{ "PRODUCT_EDUCATION", "Windows 10 Education" } },
	{ 0x0000007A,{ "PRODUCT_EDUCATION_N", "Windows 10 Education N" } },
	{ 0x00000004,{ "PRODUCT_ENTERPRISE", "Windows 10 Enterprise" } },
	{ 0x00000046,{ "PRODUCT_ENTERPRISE_E", "Windows 10 Enterprise E" } },
	{ 0x00000048,{ "PRODUCT_ENTERPRISE_EVALUATION", "Windows 10 Enterprise Evaluation" } },
	{ 0x0000001B,{ "PRODUCT_ENTERPRISE_N", "Windows 10 Enterprise N" } },
	{ 0x00000054,{ "PRODUCT_ENTERPRISE_N_EVALUATION", "Windows 10 Enterprise N Evaluation" } },
	{ 0x0000007D,{ "PRODUCT_ENTERPRISE_S", "Windows 10 Enterprise 2015 LTSB" } },
	{ 0x00000081,{ "PRODUCT_ENTERPRISE_S_EVALUATION", "Windows 10 Enterprise 2015 LTSB Evaluation" } },
	{ 0x0000007E,{ "PRODUCT_ENTERPRISE_S_N", "Windows 10 Enterprise 2015 LTSB N" } },
	{ 0x00000082,{ "PRODUCT_ENTERPRISE_S_N_EVALUATION", "Windows 10 Enterprise 2015 LTSB N Evaluation" } },
	{ 0x0000000A,{ "PRODUCT_ENTERPRISE_SERVER", "Server Enterprise (full installation)" } },
	{ 0x0000000E,{ "PRODUCT_ENTERPRISE_SERVER_CORE", "Server Enterprise (core installation)" } },
	{ 0x00000029,{ "PRODUCT_ENTERPRISE_SERVER_CORE_V", "Server Enterprise without Hyper-V (core installation)" } },
	{ 0x0000000F,{ "PRODUCT_ENTERPRISE_SERVER_IA64", "Server Enterprise for Itanium-based Systems" } },
	{ 0x00000026,{ "PRODUCT_ENTERPRISE_SERVER_V", "Server Enterprise without Hyper-V (full installation)" } },
	{ 0x0000003C,{ "PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL", "Windows Essential Server Solution Additional" } },
	{ 0x0000003E,{ "PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC", "Windows Essential Server Solution Additional SVC" } },
	{ 0x0000003B,{ "PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT", "Windows Essential Server Solution Management" } },
	{ 0x0000003D,{ "PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC", "Windows Essential Server Solution Management SVC" } },
	{ 0x00000002,{ "PRODUCT_HOME_BASIC", "Home Basic" } },
	{ 0x00000043,{ "PRODUCT_HOME_BASIC_E", "Not supported" } },
	{ 0x00000005,{ "PRODUCT_HOME_BASIC_N", "Home Basic N" } },
	{ 0x00000003,{ "PRODUCT_HOME_PREMIUM", "Home Premium" } },
	{ 0x00000044,{ "PRODUCT_HOME_PREMIUM_E", "Not supported" } },
	{ 0x0000001A,{ "PRODUCT_HOME_PREMIUM_N", "Home Premium N" } },
	{ 0x00000022,{ "PRODUCT_HOME_PREMIUM_SERVER", "Windows Home Server 2011" } },
	{ 0x00000013,{ "PRODUCT_HOME_SERVER", "Windows Storage Server 2008 R2 Essentials" } },
	{ 0x0000002A,{ "PRODUCT_HYPERV", "Microsoft Hyper-V Server" } },
	{ 0x0000007B,{ "PRODUCT_IOTUAP", "Windows 10 IoT Core" } },
	{ 0x00000083,{ "PRODUCT_IOTUAPCOMMERCIAL", "Windows 10 IoT Core Commercial" } },
	{ 0x0000001E,{ "PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT", "Windows Essential Business Server Management Server" } },
	{ 0x00000020,{ "PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING", "Windows Essential Business Server Messaging Server" } },
	{ 0x0000001F,{ "PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY", "Windows Essential Business Server Security Server" } },
	{ 0x00000068,{ "PRODUCT_MOBILE_CORE", "Windows 10 Mobile" } },
	{ 0x00000085,{ "PRODUCT_MOBILE_ENTERPRISE", "Windows 10 Mobile Enterprise" } },
	{ 0x0000004D,{ "PRODUCT_MULTIPOINT_PREMIUM_SERVER", "Windows MultiPoint Server Premium (full installation)" } },
	{ 0x0000004C,{ "PRODUCT_MULTIPOINT_STANDARD_SERVER", "Windows MultiPoint Server Standard (full installation)" } },
	{ 0x00000030,{ "PRODUCT_PROFESSIONAL", "Windows 10 Pro" } },
	{ 0x00000045,{ "PRODUCT_PROFESSIONAL_E", "Not supported" } },
	{ 0x00000031,{ "PRODUCT_PROFESSIONAL_N", "Windows 10 Pro N" } },
	{ 0x00000067,{ "PRODUCT_PROFESSIONAL_WMC", "Professional with Media Center" } },
	{ 0x00000032,{ "PRODUCT_SB_SOLUTION_SERVER", "Windows Small Business Server 2011 Essentials" } },
	{ 0x00000036,{ "PRODUCT_SB_SOLUTION_SERVER_EM", "Server For SB Solutions EM" } },
	{ 0x00000033,{ "PRODUCT_SERVER_FOR_SB_SOLUTIONS", "Server For SB Solutions" } },
	{ 0x00000037,{ "PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM", "Server For SB Solutions EM" } },
	{ 0x00000018,{ "PRODUCT_SERVER_FOR_SMALLBUSINESS", "Windows Server 2008 for Windows Essential Server Solutions" } },
	{ 0x00000023,{ "PRODUCT_SERVER_FOR_SMALLBUSINESS_V", "Windows Server 2008 without Hyper-V for Windows Essential Server Solutions" } },
	{ 0x00000021,{ "PRODUCT_SERVER_FOUNDATION", "Server Foundation" } },
	{ 0x00000009,{ "PRODUCT_SMALLBUSINESS_SERVER", "Windows Small Business Server" } },
	{ 0x00000019,{ "PRODUCT_SMALLBUSINESS_SERVER_PREMIUM", "Small Business Server Premium" } },
	{ 0x0000003F,{ "PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE", "Small Business Server Premium (core installation)" } },
	{ 0x00000038,{ "PRODUCT_SOLUTION_EMBEDDEDSERVER", "Windows MultiPoint Server" } },
	{ 0x0000004F,{ "PRODUCT_STANDARD_EVALUATION_SERVER", "Server Standard (evaluation installation)" } },
	{ 0x00000007,{ "PRODUCT_STANDARD_SERVER", "Server Standard" } },
	{ 0x0000000D,{ "PRODUCT_STANDARD_SERVER_CORE", "Server Standard (core installation)" } },
	{ 0x00000028,{ "PRODUCT_STANDARD_SERVER_CORE_V", "Server Standard without Hyper-V (core installation)" } },
	{ 0x00000024,{ "PRODUCT_STANDARD_SERVER_V", "Server Standard without Hyper-V" } },
	{ 0x00000034,{ "PRODUCT_STANDARD_SERVER_SOLUTIONS", "Server Solutions Premium" } },
	{ 0x00000035,{ "PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE", "Server Solutions Premium (core installation)" } },
	{ 0x0000000B,{ "PRODUCT_STARTER", "Starter" } },
	{ 0x00000042,{ "PRODUCT_STARTER_E", "Not supported" } },
	{ 0x0000002F,{ "PRODUCT_STARTER_N", "Starter N" } },
	{ 0x00000017,{ "PRODUCT_STORAGE_ENTERPRISE_SERVER", "Storage Server Enterprise" } },
	{ 0x0000002E,{ "PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE", "Storage Server Enterprise (core installation)" } },
	{ 0x00000014,{ "PRODUCT_STORAGE_EXPRESS_SERVER", "Storage Server Express" } },
	{ 0x0000002B,{ "PRODUCT_STORAGE_EXPRESS_SERVER_CORE", "Storage Server Express (core installation)" } },
	{ 0x00000060,{ "PRODUCT_STORAGE_STANDARD_EVALUATION_SERVER", "Storage Server Standard (evaluation installation)" } },
	{ 0x00000015,{ "PRODUCT_STORAGE_STANDARD_SERVER", "Storage Server Standard" } },
	{ 0x0000002C,{ "PRODUCT_STORAGE_STANDARD_SERVER_CORE", "Storage Server Standard (core installation)" } },
	{ 0x0000005F,{ "PRODUCT_STORAGE_WORKGROUP_EVALUATION_SERVER", "Storage Server Workgroup (evaluation installation)" } },
	{ 0x00000016,{ "PRODUCT_STORAGE_WORKGROUP_SERVER", "Storage Server Workgroup" } },
	{ 0x0000002D,{ "PRODUCT_STORAGE_WORKGROUP_SERVER_CORE", "Storage Server Workgroup (core installation)" } },
	{ 0x00000001,{ "PRODUCT_ULTIMATE", "Ultimate" } },
	{ 0x00000047,{ "PRODUCT_ULTIMATE_E", "Not supported" } },
	{ 0x0000001C,{ "PRODUCT_ULTIMATE_N", "Ultimate N" } },
	{ 0x00000000,{ "PRODUCT_UNDEFINED", "An unknown product" } },
	{ 0x00000011,{ "PRODUCT_WEB_SERVER", "Web Server (full installation)" } },
	{ 0x0000001D,{ "PRODUCT_WEB_SERVER_CORE", "Web Server (core installation)" } }
};

string getActiveProcessorMask(DWORD dwActiveProcessorMask)
{
	string s;
	while (dwActiveProcessorMask)
	{
		s = s + string(1, dwActiveProcessorMask % 2 + '0') + " ";
		dwActiveProcessorMask /= 2;
	}
	return s;
}

void systemInfo()
{
	cout << "\t\tSYSTEM INFO" << endl;

	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);


	cout << left;

	cout << setw(WIDTH) << " Processor Architecture: " << ProcessorArchitecture[systemInfo.wProcessorArchitecture].value << endl;
	cout << setw(WIDTH) << "" << ProcessorArchitecture[systemInfo.wProcessorArchitecture].meaning << endl;

	cout << setw(WIDTH) << " Processor Type: " << ProcessorType[systemInfo.dwProcessorType].value << endl;

	cout << setw(WIDTH) << " Number Of Processors: " << systemInfo.dwNumberOfProcessors << endl;

	cout << setw(WIDTH) << " Active Processor Mask: " << getActiveProcessorMask(systemInfo.dwActiveProcessorMask) << endl;

	cout << setw(WIDTH) << " Page Size: " << systemInfo.dwPageSize << endl;

	// cout << setw(WIDTH) << " Minimum Application Address: " << systemInfo.lpMinimumApplicationAddress << endl;
	// cout << setw(WIDTH) << " Maximum Application Address: " << systemInfo.lpMaximumApplicationAddress << endl;
	// cout << " dwOemId: " << systemInfo.dwOemId << endl;
	// cout << " wReserved: " << systemInfo.wReserved << endl;
	// cout << " dwAllocationGranularity: " << systemInfo.dwAllocationGranularity << endl;
	// cout << " wProcessorLevel: " << systemInfo.wProcessorLevel << endl;
	// cout << " wProcessorRevision: " << systemInfo.wProcessorRevision << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}


void osVersionInfo()
{
	cout << "\t\tOS VERSION INFO" << endl;

	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)& osvi);

	PDWORD pdwReturnedProductType = new DWORD;
	GetProductInfo(osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.wServicePackMajor, osvi.wServicePackMinor, pdwReturnedProductType);

	cout << left;

	cout << setw(WIDTH) << " Product Type: " << ProductType[*pdwReturnedProductType].value << endl;
	cout << setw(WIDTH) << "" << ProductType[*pdwReturnedProductType].meaning << endl;

	cout << setw(WIDTH) << " Build Number: " << osvi.dwBuildNumber << endl;

	cout << setw(WIDTH) << " CSD Version: " << (osvi.szCSDVersion[0] != '\0' ? (_bstr_t)osvi.szCSDVersion : "No Service Pack has been installed") << endl;
	
	cout << setw(WIDTH) << " Service Pack: " << osvi.wServicePackMajor << "." << osvi.wServicePackMinor << endl;
	
	// cout << setw(WIDTH) << " Version Number: " << osvi.dwMajorVersion <<5 "." << osvi.dwMinorVersion << endl;
	//cout << setw(WIDTH) << " Suit Mask: " << SuiteMask[osvi.wSuiteMask].value << endl;
	//cout << setw(WIDTH) << "" << SuiteMask[osvi.wSuiteMask].meaning << endl;
	// cout << setw(WIDTH) << " Platform Id: " << PlatformId[osvi.dwPlatformId].value << endl;
	// cout << setw(WIDTH) << "" << PlatformId[osvi.dwPlatformId].meaning << endl;
	// cout << setw(WIDTH) << " Operating System: " << getOperatingSystem(to_string(osvi.dwMajorVersion) + "." + to_string(osvi.dwMinorVersion), osvi) << endl;
	// cout << setw(WIDTH) << " Product Type: " << osvi.wProductType << endl;
	// cout << setw(WIDTH) << " Reserved: " << osvi.wReserved << endl;
	// cout << setw(WIDTH) << " OS Version Info Size: " << osvi.dwOSVersionInfoSize << endl;
	
	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}


// x byte -> B/KB/MB/GB/
string unitConversion(DWORDLONG x)
{
	const vector<string> unitType = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
	
	WORD id = log(x) / log(DIV); // log1024(x)
	DWORDLONG y = round(((float)x / pow(2, 10 * id)) * 100);
	
	return to_string(y / 100) + "." + to_string(y % 100) + " " + unitType[id];
}

void globalMemoryStatus()
{
	cout << "\t\tGLOBAL MEMORY STATUS" << endl;

	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);


	cout << setw(WIDTH) << " Total of physical memory: " << unitConversion(statex.ullTotalPhys) << endl;

	cout << setw(WIDTH) << " Total of paging file: " << unitConversion(statex.ullTotalPageFile) << endl;

	cout << setw(WIDTH) << " Total of virtual memory: " << unitConversion(statex.ullTotalVirtual) << endl;

	// cout << setw(WIDTH) << " Memory in use: " << statex.dwMemoryLoad << " %" << endl;
	// cout << setw(WIDTH) << " Free of physical memory: " << statex.ullAvailPhys / DIV << " KB" << endl;
	// cout << setw(WIDTH) << " Free of paging file: " << statex.ullAvailPageFile / DIV << " KB" << endl;
	// cout << setw(WIDTH) << " Free of virtual memory: " << statex.ullAvailVirtual / DIV << " KB" << endl;
	// cout << setw(WIDTH) << " Free of extended memory: " << statex.ullAva ilExtendedVirtual / DIV << " KB" << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << endl;
}

void netUserEnum()
{
	cout << "\t\tACCOUNT" << endl;
	
	LPTSTR pszServerName = NULL;
	DWORD dwLevel = 0;
	DWORD dwFilter = FILTER_NORMAL_ACCOUNT; // global users
	LPUSER_INFO_0 pBuf = NULL;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;

	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;

	nStatus = NetUserEnum((LPCWSTR)pszServerName,
		dwLevel,
		dwFilter,
		(LPBYTE*)&pBuf,
		dwPrefMaxLen,
		&dwEntriesRead,
		&dwTotalEntries,
		&dwResumeHandle);

	cout << " Number of user account: " << dwEntriesRead << endl;

	LPUSER_INFO_0 pTmpBuf = pBuf;

	for (DWORD i = 0; i < dwEntriesRead; i++)
	{
		wcout << "\t- " << pTmpBuf->usri0_name << endl;
		
		pTmpBuf++;
		dwTotalCount++;
	}
	if (pBuf != NULL)
	{
		NetApiBufferFree(pBuf);
		pBuf = NULL;
	}

	DWORD size = UNLEN + 1;
	LPWSTR lpBuffer = new WCHAR[size];
	GetUserNameW(lpBuffer, &size);
	wcout << " Current user: " << lpBuffer << endl;
	delete[] lpBuffer;
	cout << "-----------------------------------------------------" << endl; 
	cout << endl;
}

void ipConfig()
{
	system("ipconfig");
	cout << "-----------------------------------------------------" << endl; 
	cout << endl;
}

int main()
{
	cout << endl;
	cout << "\t\tCOMPUTER INFO" << endl;
	cout << "=====================================================" << endl;
	cout << endl;
	
	systemInfo();
	osVersionInfo();
	globalMemoryStatus();
	netUserEnum();
	ipConfig();
	
	system("pause");
	return 0;
}