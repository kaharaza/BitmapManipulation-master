/*
*  image.c
*
*/

#include "image.h"
#include <stdio.h>

struct pixel* readBitmap(const char *filename, struct header* pHeader, struct info* pInfo)
{
	struct pixel *pData;
	FILE* fp;

	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("Datei %s kann nicht geoeffnet werden!\n", filename);
		return NULL;
	}

	/* fread dient zum Einlesen von Binärdateien. fread-Parameter:
	1.: Zeiger auf den Speicherbereich in den die eingelesenen Daten geschrieben werden
	2.: Groesse eines Elements welches eingelesen werden soll
	3.: Anzahl der Elemente die eingelesen werden sollen
	4.: Datei von der gelesen werden soll
	*/
	/* elemente muessen einzeln eingelesen werden, da ints immer an einer
	4-byte grenze ausgerichtet werden und das erste feld nur aus 2 byte besteht */
	fread(&pHeader->bfType, sizeof(char), 2, fp);
	fread(&pHeader->bfSize, sizeof(unsigned int), 1, fp);
	fread(&pHeader->bfReserved, sizeof(unsigned int), 1, fp);
	fread(&pHeader->bfOffBits, sizeof(unsigned int), 1, fp);
	fread(pInfo, sizeof(struct info), 1, fp);

	/*
	* TODO IMPLEMENTIEREN SIE AN DIESER STELLE DAS EINLESEN DER BILDDATEN (PIXEL)
	*/

	pData = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel));	//Allocate enough memory
	fread(pData, sizeof(struct pixel), pInfo->biHeight * pInfo->biWidth,fp);


	fclose(fp);

	return pData;
}

void writeBitmap(const char *filename, struct header* pHeader, struct info* pInfo, struct pixel* pData)
{
	FILE* fp;		//Pointer for source file;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		printf("Datei %s kann nicht geoeffnet werden!\n", filename);
		return;
	}

	fwrite(&pHeader->bfType, sizeof(char), 2, fp);
	fwrite(&pHeader->bfSize, sizeof(unsigned int), 1, fp);
	fwrite(&pHeader->bfReserved, sizeof(unsigned int), 1, fp);
	fwrite(&pHeader->bfOffBits, sizeof(unsigned int), 1, fp);		//save bitmap...
	fwrite(pInfo, sizeof(struct info), 1, fp);
	fwrite(pData, sizeof(struct pixel), pInfo->biHeight * pInfo->biWidth, fp);

	
	fclose(fp);
	

	
}



struct pixel* mirror(struct info* pInfo, struct pixel* pData)
{

	struct pixel *mirrorData;
	struct pixel *temp;	//Temporary memory
	mirrorData = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel));	//Allocate enough memory and initialize mirror data
	temp = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel));	//Allocate enough memory for our temporary memory.

	for (int i = 0; i < (pInfo->biHeight * pInfo->biWidth); i++) {	//Loop until the parimeter of the image size.
		mirrorData[i] = *(pData + (pInfo->biHeight * pInfo->biWidth) - i - 1);	//Store our pData in the mirror data
	}

	/*
	* TODO IMPLEMENTIEREN SIE AN DIESER STELLE DAS HORIZONTALE UND VERTIKALE SPIEGELN
	* ERSETZEN SIE "RETURN NULL" DURCH EIN SINNVOLLES RETURN STATEMENT
	*/


	return mirrorData;
}

struct pixel* invert(struct info* pInfo, struct pixel* pData)
{
	struct pixel *invertData;
	struct pixel *temp;	//Temporary memory
	int size = sizeof(struct pixel);	//We take the size of the structure

	invertData = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel));	//Allocate enough memory and initialize mirror data
	temp = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel));	//Allocate enough memory for our temporary memory.

	for (int i = 0; i < pInfo->biSizeImage / size; i++) {	//Loop until the parimeter of the image size.

		invertData[i].red = 255 - pData[i].red;		//manipulate the GRB values.
		invertData[i].green = 255 - pData[i].green;
		invertData[i].blue = 255 - pData[i].blue;
	}
	/*
	* TODO IMPLEMENTIEREN SIE AN DIESER STELLE DAS HORIZONTALE UND VERTIKALE SPIEGELN
	* ERSETZEN SIE "RETURN NULL" DURCH EIN SINNVOLLES RETURN STATEMENT
	*/
	return invertData;
}

struct pixel* saturation(struct info* pInfo, struct pixel* pData, double wRed, double wGreen, double wBlue)
{

	const double Pr = .299;
	const double  Pg = .587;
	const double  Pb = .114;
	const change = 1;

	double  P = sqrt((wRed)*(wRed) *Pr + (wGreen)*(wGreen) *Pg + (wBlue)*(wBlue) *Pb); 
	wRed = P + ((wRed) - P)*change;
	wGreen = P + ((wGreen) - P)*change;
	wBlue = P + ((wBlue) - P)*change;


	struct pixel *saturationData;
	int size = sizeof(struct pixel);	//We take the size of the structure

	saturationData = (struct pixel *)malloc(pInfo->biHeight*pInfo->biWidth * sizeof(struct pixel)*pData->green * pData->red * pData->blue);	//Allocate enough memory and initialize mirror data

	printf("This is reddddd   %d", wRed);
	for (int i = 0; i < pInfo->biSizeImage / size; i++) {	//Loop until the parimeter of the image size.

		

		saturationData[i].red = pData[i].red + wRed;		//manipulate the GRB values so that the saturation colours are inputed.
		saturationData[i].green = pData[i].green + wGreen;
		saturationData[i].blue = pData[i].blue + wBlue;
	}


	return saturationData;

	/*
	* TODO IMPLEMENTIEREN SIE AN DIESER STELLE DAS ÄNERDN DER FARBSÄTTIGUNG
	* ERSETZEN SIE "RETURN NULL" DURCH EIN SINNVOLLES RETURN STATEMENT
	*/
	
}


