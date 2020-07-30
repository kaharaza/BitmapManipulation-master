#pragma once

/*
*  image.h
*
*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

/* Struktur des Headers einer BMP Datei */
struct header {
	char bfType[2];
	unsigned int bfSize;
	unsigned int bfReserved;
	unsigned int bfOffBits;
};

/* Struktur des Info-Bereichs einer BMP Datei */
struct info {
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};

/* Struktur eines Pixels im Falle einer 24bpp BMP Datei */
struct pixel {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

/* Einlesen und Schreiben von Bitmap-Dateien */
struct pixel* readBitmap(const char *filename, struct header* pHeader, struct info* pInfo);
void writeBitmap(const char *filename, struct header* pHeader, struct info* pInfo, struct pixel* pData);
/* Funktionen zum Bearbeiten der Bilddaten */
struct pixel* mirror(struct info* pInfo, struct pixel* pData);
struct pixel* invert(struct info* pInfo, struct pixel* pData);
struct pixel* saturation(struct info* pInfo, struct pixel* pData, double wRed, double wGreen, double wBlue);


#endif /* _IMAGE_H_ */

