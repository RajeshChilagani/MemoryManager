#pragma once
#include <iostream>
using std::cin;
using std::cout;
char* GenString()
{
	char* TempName = nullptr;
	char* Name = nullptr;
	char inputCharacter;
	int count = 0;
	do
	{
		inputCharacter = cin.get();
		if (inputCharacter != '\n')
		{
			count++;
			TempName = reinterpret_cast<char*>(realloc(Name, count * sizeof(char)));
			if (TempName != nullptr)
			{

				TempName[count - 1] = inputCharacter;
				Name = TempName;
			}
			else {
				free(Name);
				free(TempName);
				exit(1);
			}
		}
		else
		{
			count++;
			TempName = reinterpret_cast<char*>(realloc(Name, count * sizeof(char)));
			if (TempName != nullptr)
			{
				TempName[count - 1] = '\0';
				Name = TempName;
			}
			else {
				free(Name);
				free(TempName);
				exit(1);
			}
		}

	} while (inputCharacter != '\n');
	return Name;
}
