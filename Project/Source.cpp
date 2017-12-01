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

map<string, array<string, 2>> OperatingSystem = {
	{ "10.0", { "Windows 10", "Windows Server 2016" } },
	{ "6.3", { "Windows 8.1", "Windows Server 2012 R2" } },
	{ "6.2", { "Windows 8", "Windows Server 2012" } },
	{ "6.1", { "Windows 7", "Windows Server 2008 R2" } },
	{ "6.0", { "Windows Vista", "Windows Server 2008" } },
	{ "5.2", { "Windows Server 2003", "Windows Server 2003 R2" } },
	{ "5.1", { "Windows XP", "Windows XP" } },
	{ "5.1", { "Windows 2000", "Windows 2000" } }
};

string getOperatingSystem(string& versionNumber, OSVERSIONINFOEX &osvi)
{
	if (versionNumber[0] > '5')
		return OperatingSystem[versionNumber][osvi.wProductType != VER_NT_WORKSTATION];
	else if (versionNumber == "5.2")
		return OperatingSystem[versionNumber][GetSystemMetrics(SM_SERVERR2) != 0];
	else if (versionNumber == "5.1" || versionNumber == "5.0")
		return OperatingSystem[versionNumber][0];
	else
		return "Unknown Operating System";
}


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

	cout << left;
	cout << setw(30) << " Operating System: " << getOperatingSystem(to_string(osvi.dwMajorVersion) + "." + to_string(osvi.dwMinorVersion), osvi) << endl;
	cout << setw(30) << " Version Number: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << endl;
	cout << setw(30) << " Build Number: " << osvi.dwBuildNumber << endl;
	cout << setw(30) << " Platform Id: " << PlatformId[osvi.dwPlatformId].value << endl;
	cout << setw(30) << " Suit Mask: " << SuiteMask[osvi.wSuiteMask].value << endl;
	cout << setw(30) << " CSD Version: " << (osvi.szCSDVersion[0] != '\0' ? osvi.szCSDVersion : "No Service Pack has been installed") << endl;
	cout << setw(30) << " Service Pack: " << osvi.wServicePackMajor << "." << osvi.wServicePackMinor << endl;
	//cout << setw(30) << " Product Type: " << osvi.wProductType << endl;
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
