#include "rgbfilter.h"

// checks if compt_name match "red", "green" or "blue"
uint8_t identify(const char* compt_name)
{
	if (!strcmp("red", compt_name))
		return 'r';
	else if (!strcmp("green", compt_name))
		return 'g';
	else if (!strcmp("blue", compt_name))
		return 'b';
	else
		return '\0';
}

size_t rgbfilter(RGB*** arr, const BitmapInfoHeader* bmih,
               const char* compt_name, uint8_t compt_val)
{
    const char indicator = identify(compt_name);
        
    switch (indicator) {
        case 'r':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    arr[i][j]->r = compt_val;
            }
            printf("Red component was changed to %u\n", compt_val);
            return NO_ERROR;
        case 'g':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    arr[i][j]->g = compt_val;
            }            
            printf("Green component was changed to %u\n", compt_val);
            return NO_ERROR;
        case 'b':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    arr[i][j]->b = compt_val;
            }
            printf("Blue component was changed to %u\n", compt_val);
            return NO_ERROR;
        default:
            return WRONG_ARG;
    }
}
