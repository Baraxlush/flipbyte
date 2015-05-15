// лаба2.5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <cctype>

using namespace std;

void ErrorMessage(int tag)
{
	if (tag == 1)
	{
		printf("Error: unknown number!\n");
		system("pause");
		exit(1);
	}
	if (tag == 2)
	{
		printf("Error: number out of range!\n");
		system("pause");
		exit(2);
	}
	if (tag == 3)
	{
		printf("Error: cannot create file!\n");
		system("pause");
		exit(3);
	}
}

void WriteToFile(const int &number)
{
	ofstream outputFile;
	outputFile.open("output.txt", ofstream::out);

	if (outputFile.good())
	{
		outputFile << number;
	}
	else
	{
		ErrorMessage(3);
	}
}

int StringToInt(char* line)
{
	int number = 0;
	char *pLastChar = NULL;
	number = strtol(line, &pLastChar, 10);

	if (number < 0 || number > 255)
	{
		ErrorMessage(2);
	}
	return number;
}

bool CheckStringOnNumber(const char *inputString)
{
	int symbol_counter = 0;
	for (unsigned int i = 0; i < strlen(inputString); ++i)
	{
		if (isdigit(inputString[i]))
		{
			symbol_counter++;
		}
	}
	return symbol_counter == strlen(inputString);
}

void InvertNumber(const int &main, int &result)
{
	for (int i = 0; i < 8; ++i)
	{
		int temp;
		temp = (main >> i) & 1;
		result += temp << 8 - i - 1;
	}
}

int main(int argc, char* argv[])
{	
	char *inputString = argv[1];
	if (!(CheckStringOnNumber(inputString)))
	{
		ErrorMessage(1);
	}

	int mainNumber = StringToInt(inputString);
	int result = 0;
	
	InvertNumber(mainNumber, result);
	WriteToFile(result);

	return 0;
}

