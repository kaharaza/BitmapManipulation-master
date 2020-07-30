#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main(int argc, const char **argv)
{
	struct header bmpHeader;
	struct info bmpInfo;
	struct pixel *data;
	struct pixel *mirrorData;
	struct pixel *invertData;
	struct pixel *saturationData;

	printf("count %i: %s,%s,%s", argc, argv[0], argv[1], argv[2]);
	data = readBitmap(argv[1], &bmpHeader, &bmpInfo);
	mirrorData = mirror(&bmpInfo, data);
	invertData = invert(&bmpInfo, data);
	saturationData = saturation(&bmpInfo, data, 5, 5 , 5);

	writeBitmap(argv[2], &bmpHeader, &bmpInfo, saturationData);

	/*
	* TODO GEBEN SIE NICHT MEHR BENÖTIGTE SPEICHERBEREICHE SPÄTESTENS AN DIESER STELLE
	* WIEDER FREI.
	*/

	return 0;
}

