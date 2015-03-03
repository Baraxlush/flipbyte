// лаба2.5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <cctype>
#include <malloc.h>

void Error_Message(int tag)
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
		exit(1);
	}
}

void Open_File_To_Write(int number)
{
	FILE *output = fopen("output.txt", "w");
	if (output == NULL)
	{
		Error_Message(3);
	}
	fprintf(output, "%d", number);
	fclose(output);
}

int String_To_Int(char* line)
{
	int number = 0;
	char *pLastChar = NULL;
	number = strtol(line, &pLastChar, 10);
	if (number < 0 || number > 255)
	{
		Error_Message(2);
	}
	return number;
}

void From_Bits_To_Decimal(int* bits_array)
{
	int i = 0, end_counter = 7, intermediate_result = 0;
	while (i < 8)
	{
		intermediate_result += bits_array[i] * pow(2, end_counter);
		i++;
		end_counter--;
	}
	Open_File_To_Write(intermediate_result);
}

int* Divide_for_bits(int number)
{
	int* bits_array = new int[8];
	int i = 0, division = 128, temp = 0;
	while (i < 8)
	{
		temp = number / division;
		number = number - temp * division;
		bits_array[i] = temp;
		division = division / 2;
		i++;
	}
	return bits_array;
}

int* Invert_Array(int* bits_array)
{
	int end_counter = 7, intermediate_result = 0;
	for (int i = 0; i < 4; i++)
	{
		intermediate_result = bits_array[i];
		bits_array[i] = bits_array[end_counter];
		bits_array[end_counter] = intermediate_result;
		end_counter--;
	}
	return bits_array;
}

void Processing_String(char* line)
{
	int symbol_counter = 0, main_number = 0;
	int* bits_array;
	for (unsigned int i = 0; i < strlen(line); i++)
	{
		if (isdigit(line[i]))
			symbol_counter++;
	}

	if (symbol_counter != strlen(line))
	{
		Error_Message(1);
	}
	main_number = String_To_Int(line);
	bits_array = Divide_for_bits(main_number);
	bits_array = Invert_Array(bits_array);
	From_Bits_To_Decimal(bits_array);
	delete[] bits_array;
}

int main(int argc, char* argv[])
{	
	char *string = argv[1];
	Processing_String(string);

	return 0;
}

