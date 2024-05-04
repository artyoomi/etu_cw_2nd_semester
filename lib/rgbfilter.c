#include "../include/rgbfilter.h"

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

int32_t rgbfilter(RGB*** arr,
                  const char* compt_name, const uint8_t compt_val,
                  uint32_t H, uint32_t W)
{   
    const char indicator = identify(compt_name);
    
    switch (indicator) {
        case 'r':
            for (size_t i = 0; i < H; i++) {
                for (size_t j = 0; j < W; j++)
                    (*arr)[i][j].r = compt_val;
            }
            printf("Red component was changed to %u\n", compt_val);
            return NO_ERROR;
        case 'g':
            for (size_t i = 0; i < H; i++) {
                for (size_t j = 0; j < W; j++)
                    (*arr)[i][j].g = compt_val;
            }            
            printf("Green component was changed to %u\n", compt_val);
            return NO_ERROR;
        case 'b':
            for (size_t i = 0; i < H; i++) {
                for (size_t j = 0; j < W; j++)
                    (*arr)[i][j].b = compt_val;
            }
            printf("Blue component was changed to %u\n", compt_val);
            return NO_ERROR;
        default:
            error_return("The --component_name flag takes one of the arguments: red, blue, green\n", ARG_ERROR);
    }
}
