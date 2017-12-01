#include <windows.h>
#include <string>
#include <map>
#include <array>
#include <iostream>
#include <iomanip>

using namespace std;

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

map<DWORD, Detail> PlatformId = {
	{ 2,{ "VER_PLATFORM_WIN32_NT", "The operating system is Windows 7, Windows Server 2008, Windows Vista, Windows Server 2003, Windows XP, or Windows 2000" } }
};

map<WORD, Detail> SuiteMask = {
	{ 0x00000004,{ "VER_SUITE_BACKOFFICE", "Microsoft BackOffice components are installed" } },
	{ 0x00000400,{ "VER_SUITE_BLADE", "Windows Server 2003, Web Edition is installed" } },
	{ 0x00004000,{ "VER_SUITE_COMPUTE_SERVER", "Windows Server 2003, Compute Cluster Edition is installed" } },
	{ 0x00000080,{ "VER_SUITE_DATACENTER", "Windows Server 2008 Datacenter, Windows Server 2003, Datacenter Edition, or Windows 2000 Datacenter Server is installed" } },
	{ 0x00000002,{ "VER_SUITE_ENTERPRISE", "Windows Server 2008 Enterprise, Windows Server 2003, Enterprise Edition, or Windows 2000 Advanced Server is installed. Refer to the Remarks section for more information about this bit flag" } },
	{ 0x00000040,{ "VER_SUITE_EMBEDDEDNT", "Windows XP Embedded is installed" } },
	{ 0x00000200,{ "VER_SUITE_PERSONAL", "Windows Vista Home Premium, Windows Vista Home Basic, or Windows XP Home Edition is installed" } },
	{ 0x00000100,{ "VER_SUITE_SINGLEUSERTS", "Remote Desktop is supported, but only one interactive session is supported. This value is set unless the system is running in application server mode" } },
	{ 0x00000001,{ "VER_SUITE_SMALLBUSINESS", "Microsoft Small Business Server was once installed on the system, but may have been upgraded to another version of Windows. Refer to the Remarks section for more information about this bit flag" } },
	{ 0x00000020,{ "VER_SUITE_SMALLBUSINESS_RESTRICTED", "Microsoft Small Business Server is installed with the restrictive client license in force. Refer to the Remarks section for more information about this bit flag" } },
	{ 0x00002000,{ "VER_SUITE_STORAGE_SERVER", "Windows Storage Server 2003 R2 or Windows Storage Server 2003is installed" } },
	{ 0x00000010,{ "VER_SUITE_TERMINAL", "Terminal Services is installed. This value is always set " } },
	{ 0x00008000,{ "VER_SUITE_WH_SERVER", "Windows Home Server is installed" } }
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

void systemInfo()
{
	cout << "\tSYSTEM INFO" << endl;

	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);


	cout << left;
	cout << setw(30) << " Processor Architecture: " << ProcessorArchitecture[systemInfo.wProcessorArchitecture].value << endl;
	cout << setw(30) << " Processor Type: " << ProcessorType[systemInfo.dwProcessorType].value << endl;
	cout << setw(30) << " Active Processor Mask: " << systemInfo.dwActiveProcessorMask << endl;
	cout << setw(30) << " Number Of Processors: " << systemInfo.dwNumberOfProcessors << endl;
	cout << setw(30) << " Page Size: " << systemInfo.dwPageSize << endl;
	cout << setw(30) << " Minimum Application Address: " << systemInfo.lpMinimumApplicationAddress << endl;
	cout << setw(30) << " Maximum Application Address: " << systemInfo.lpMaximumApplicationAddress << endl;
	// cout << " dwOemId: " << systemInfo.dwOemId << endl;
	// cout << " wReserved: " << systemInfo.wReserved << endl;
	// cout << " dwAllocationGranularity: " << systemInfo.dwAllocationGranularity << endl;
	// cout << " wProcessorLevel: " << systemInfo.wProcessorLevel << endl;
	// cout << " wProcessorRevision: " << systemInfo.wProcessorRevision << endl;
	cout << endl;
}


void osVersionInfo()
{
	cout << "\tOS VERSION INFO" << endl;

	OSVERSIONINFOEX osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)& osvi);

	PDWORD pdwReturnedProductType = new DWORD;
	GetProductInfo(osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.wServicePackMajor, osvi.wServicePackMinor, pdwReturnedProductType);

	cout << left;
	cout << setw(30) << " Product Type: " << ProductType[*pdwReturnedProductType].meaning << endl;
	cout << setw(30) << " Version Number: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << endl;
	cout << setw(30) << " Build Number: " << osvi.dwBuildNumber << endl;
	cout << setw(30) << " Suit Mask: " << SuiteMask[osvi.wSuiteMask].value << endl;
	cout << setw(30) << " Platform Id: " << PlatformId[osvi.dwPlatformId].value << endl;
	cout << setw(30) << " CSD Version: " << (osvi.szCSDVersion[0] != '\0' ? osvi.szCSDVersion : "No Service Pack has been installed") << endl;
	cout << setw(30) << " Service Pack: " << osvi.wServicePackMajor << "." << osvi.wServicePackMinor << endl;
	// cout << setw(30) << " Operating System: " << getOperatingSystem(to_string(osvi.dwMajorVersion) + "." + to_string(osvi.dwMinorVersion), osvi) << endl;
	// cout << setw(30) << " Product Type: " << osvi.wProductType << endl;
	// cout << setw(30) << " Reserved: " << osvi.wReserved << endl;
	// cout << setw(30) << " OS Version Info Size: " << osvi.dwOSVersionInfoSize << endl;
}

int main()
{
	systemInfo();
	osVersionInfo();


	system("pause");
	return 0;
}

/*map<string, array<string, 2>> OperatingSystem = {
{ "10.0", { "Windows 10", "Windows Server 2016" } },
{ "6.3", { "Windows 8.1", "Windows Server 2012 R2" } },
{ "6.2", { "Windows 8", "Windows Server 2012" } },
{ "6.1", { "Windows 7", "Windows Server 2008 R2" } },
{ "6.0", { "Windows Vista", "Windows Server 2008" } },
{ "5.2", { "Windows Server 2003", "Windows Server 2003 R2" } },
{ "5.1", { "Windows XP", "Windows XP" } },
{ "5.1", { "Windows 2000", "Windows 2000" } }
};*/

/*string getOperatingSystem(string& versionNumber, OSVERSIONINFOEX &osvi)
{
if (versionNumber[0] > '5')
return OperatingSystem[versionNumber][osvi.wProductType != VER_NT_WORKSTATION];
else if (versionNumber == "5.2")
return OperatingSystem[versionNumber][GetSystemMetrics(SM_SERVERR2) != 0];
else if (versionNumber == "5.1" || versionNumber == "5.0")
return OperatingSystem[versionNumber][0];
else
return "Unknown Operating System";
}*/
