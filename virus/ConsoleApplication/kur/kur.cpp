#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <fstream> 
#include <string> 

using namespace std; 


void spoilFile(char *str) {
	string line;
	ifstream myfile(str);//������� ���� ��� ������ 
	if (myfile.is_open())//���� ������ 
	{
		while (!myfile.eof())//� ������ �� ����� 
		{
			getline(myfile, line);//���������� ������ 
			//cout << line << endl;//�������� ������ 
			for (size_t i = 1; i < line.length(); i += i) {
				line[i] = (int)(line[i]) - 10;//�������� ������� � ������ 

			}
			//cout << line << endl;//������ � ������� ��� ����� ��� ��� �� 
		}
		myfile.close();//������� ���� 
	}
	else 
		cout << "ne otkrilsya((" << endl;

	ofstream out; // ����� ��� ������ 
	out.open(str); // �������� ���� ��� ������ 
	if (out.is_open()) //���� ������ 
	{
		out << line << endl;//�� ������� ����� ������ � ���� 
	}
}


int seek(LPCTSTR lpszFileName, BOOL bInnerFolders)
{
	LPTSTR part;
	char tmp[MAX_PATH];				// temporary array
	char name[MAX_PATH];

	HANDLE hSearch = NULL;
	WIN32_FIND_DATA wfd;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

	//search in embeded folders for first
	if (bInnerFolders)
	{
		if (GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0)
			return 0 ;
		lstrcpy(name, part);
		lstrcpy(part, "*.*");

		//if folder exists, down to it
		wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
		if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
			do
			{
				//if current folder is a service folders? which no need to check
				if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
					continue;
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //if it's a folder
				{
					// making a new path
					char next[MAX_PATH];
					if (GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return 0 ;
					lstrcpy(part, wfd.cFileName);
					lstrcat(next, "\\");
					//SetWindowText(window, next);

					//cout << next << endl;
					//cout << next << endl; 
					//cout << "ISCHEM" << endl;
					//printf(next);
					//printf("\n");

					lstrcat(next, name);

					//recourse down
					seek(next, TRUE);
				}
			} while (FindNextFile(hSearch, &wfd)); //finding next file in folder
			FindClose(hSearch); // closing a search descriptor
	}
	if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
		return 1;
	do
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // is it's a file
		{
			char file[MAX_PATH];
			if (GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return 0;
			lstrcpy(part, wfd.cFileName);

			//adding its to a result list
			//AddFileToList(file);

			//cout << "VSE" << endl;
			//cout << file << endl; // ����� ���������� ����� 
			spoilFile(file); 
			

			//printf(file);
			//printf("\n");
		}
	while (FindNextFile(hSearch, &wfd));	// next file in folder
	FindClose(hSearch);					// close search descriptor

	return 1;
}



int main() {
	if(!seek("c:\\users\\user\\desktop\\*.pdf", true))
		cout << "Searching failed" << endl;

	//"c:\\users\\user\\desktop\\aaa.pdf"

	//spoilFile("c:\\users\\user\\desktop\\aaa.pdf");

	//getch();
	return 0;
}