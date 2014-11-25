
#include <stdio.h>
#include <string.h>
#include "hi_scores.h"

void HiScores::init()
{
	int	scr = 10000 * HS_NB_SCORES;

	for (int i = 0; i < HS_NB_SCORES; i++) {
		scores[i] = scr;
		strcpy(names[i], "LOADED STUDIO");
		scr -= 10000;
	}
}

void HiScores::add(int scr, const char * name)
{
	int		i = 0;

	while (i < HS_NB_SCORES && scores[i] > scr)
		i++;

	int		j = HS_NB_SCORES - 1;

	while (j > i) {
		scores[j] = scores[j - 1];
		strcpy(names[j], names[j - 1]);

		j--;
	}

	if (i < HS_NB_SCORES) {
		scores[i] = scr;
		strcpy(names[i], name);
	}
}

void HiScores::crypte()
{
	for (int i = 0; i < HS_NB_SCORES; i++) {
		scores[i] ^= 0x35674a1f << i;

		long * ptr = (long*) names[i];

		for (int j = 0; j < HS_NAME_LENGTH; j += 4) {
			*(ptr++) ^= 0x35674a1f << i;
		}
	}
}

bool HiScores::save(const char * file)
{
	FILE *	f;
	///MODIF path
	f = fopen(create_pathSDL(file), "wb");

	if (f == NULL)
		return false;

	int som = 0;

	for (int i = 0; i < HS_NB_SCORES; i++) {
		som += scores[i];

		for (int j = 0; j < HS_NAME_LENGTH; j++)
			som += names[i][j];
	}

	crypte();

	for (int i = 0; i < HS_NB_SCORES; i++) {
		fwrite(&scores[i], 1, sizeof(scores[i]), f);
		fwrite(names[i], 1, HS_NAME_LENGTH, f);
	}

	fwrite(&som, 1, sizeof(som), f);

	crypte();
	fclose(f);
	return true;
}

bool HiScores::load(const char * file)
{
	FILE *	f;
	int		som;
	///MODIF path
	f = fopen(create_pathSDL(file), "rb");

	if (f == NULL)
		return false;


	for (int i = 0; i < HS_NB_SCORES; i++) {
		fread(&scores[i], 1, sizeof(scores[i]), f);
		fread(names[i], 1, HS_NAME_LENGTH, f);
	}

	fread(&som, 1, sizeof(som), f);

	crypte();

	int crc = 0;

	for (int i = 0; i < HS_NB_SCORES; i++) {
		crc += scores[i];

		for (int j = 0; j < HS_NAME_LENGTH; j++)
			crc += names[i][j];
	}


	fclose(f);
	return (som == crc);
}
