#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

int RestFile(const FILE* myfile);
int CompFile(const FILE* myfile);
void Compact(const char* buf, FILE* second, int count);
void Restore(const FILE* third, const FILE* second);

int main()
{
	FILE* myf;
	myf = fopen("secinfo.bin", "rb");
	if (myf == NULL)
		printf("File with this name doesn't exist"); // Open file
	else 
	{
		int fl = 0;
		printf("Choose option:\n1. Compact a string.\n2. Restore the line\n");
		scanf("%d", &fl);
		if (fl == 1)
			fl = CompFile(myf);	// to compact
		else
			fl = RestFile(myf); // to restore
	}
	return 0;
}

int CompFile(const FILE* myfile)
{
	char symb = "", slide[101] = "";
	FILE* sec = fopen("secinfo.bin", "wb");
	if (sec == NULL)
		printf("File didn't opened");
	else
	{
		int count = 0;
		count = fread(slide, sizeof(char), 100, myfile);
		while (count) // read every 100 symbols while number of read symbols won't be equal zero
		{
			printf("%s\n", slide);
			Compact(slide, sec, count);
			count = fread(slide, sizeof(char), 100, myfile);
		}
		symb = '\0';
		fwrite(&count, 1, sizeof(int), sec);
		fwrite(&count, 1, sizeof(int), sec);
		fwrite(&symb, 1, sizeof(char), sec);
		fclose(myfile);
		fclose(sec);
		sec = fopen("secinfo.bin", "rb");
		int off = 0;
		do
		{
			int dop = 0;
			fread(&dop, sizeof(int), 1, sec);
			printf("%d%s", dop, " ");
			fread(&dop, sizeof(int), 1, sec);
			printf("%d%s", dop, " ");
			fread(&symb, sizeof(char), 1, sec);
			switch(symb)
			{
			case '\t':
				printf("%s", "'t'  ");
				break;
			case '\n':
				printf("%s", "'n'  ");
				break;
			case ' ':
				printf("%s", "' '  ");
				break;
			default:
				printf("%c%s", symb, "  ");
				break;
			}
		} while (symb != '\0');
		return 1;
	}
	return 0;
}

void Compact(const char* buf, FILE* second, int count)
{
	char dict, symb;
	int mainin = 0, buf_ind = 0, eof = 0;
	for (; mainin < count;)	// while didn't check all string
	{
		int offset = 0, max_length = 0, dop_ind = 0;
		while (dop_ind < mainin)	// find coincidences
		{
			int length = 0, dop_off = mainin - dop_ind;
			symb = buf[mainin];
			dict = buf[dop_ind];
			buf_ind = mainin + length;
			while ((buf_ind < count) && (dict == symb))
			{
				length++;
				buf_ind = dop_ind + length;
				dict = buf[buf_ind];
				buf_ind = mainin + length;
				symb = buf[buf_ind];
			}
			if (length > max_length)
			{
				max_length = length;
				offset = dop_off;
			}
			dop_ind++;
		}
		fwrite(&offset, sizeof(int), 1, second);		// write the offset
		fwrite(&max_length, sizeof(int), 1, second);		// write the length of repeated string
		buf_ind = mainin + max_length;
		if (buf_ind >= count)
		{
			symb = '\n';
			fwrite(&symb, sizeof(char), 1, second);
			eof = 1;
		}
		else
			fwrite(buf + buf_ind, sizeof(char), 1, second);	// write symbol
		buf_ind = max_length + 1;
		mainin += buf_ind;	// change indexes
		if ((mainin >= count) && (!eof))
		{
			fwrite(&eof, sizeof(int), 1, second);
			fwrite(&eof, sizeof(int), 1, second);
			symb = '\n';
			fwrite(&symb, sizeof(char), 1, second);
		}
	}
}

int RestFile(const FILE* myfile)
{
	char symb = "";
	FILE* thir = fopen("thirdinfo.bin", "wb");
	if (thir == NULL)
		printf("File didn't opened");
	else
	{
		Restore(thir, myfile);
		fclose(myfile);
		fclose(thir);
		thir = fopen("thirdinfo.bin", "rb");
		do
		{
			fread(&symb, sizeof(char), 1, thir);
			printf("%c%s", symb, " ");
		} while (symb != '\0');
		return 1;
	}
	return 0;
}

void Restore(const FILE* third, const FILE* second)
{
	char dict, symb, slice[100];
	int length = 0, offset = 0, index = 0;
	do
	{
		fread(&offset, sizeof(int), 1, second);
		fread(&length, sizeof(int), 1, second);
		fread(&symb, sizeof(char), 1, second);
		for (int i = 0, bind = index; i < length; i++, index++)
		{
			int dop = bind - offset + i;
			slice[index] = slice[dop];
		}
		slice[index] = symb;
		index++;
		if (index == 100)
		{
			fwrite(slice, sizeof(char), index, third);
			index = 0;
		}
	} while (symb != '\0');
	fwrite(slice, sizeof(char), index, third);
}