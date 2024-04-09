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

// if returns 0, then val is match, otherwise - not
uint8_t is_byte(const char* compt_val)
{
    regex_t regex;
    int32_t reti = regcomp(&regex, "^(\\d|([1-9]\\d)|1\\d{2}|2[0-5]{2})$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex!\n");
        return 1;
    }
    
    reti = regexec(&regex, compt_val, 0, NULL, 0);
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        fprintf(stderr, "Component value must be in range [0-255]\n");
        return 1;
    } else  {
	    char err_buf[100];
		regerror(reti, &regex, err_buf, sizeof(err_buf));
		fprintf(stderr, "Regex match failed %s\n", err_buf);
		return 1;
    }
    regfree(&regex);
}

size_t rgbfilter(RGB*** arr, const BitmapInfoHeader* bmih,
                 const char* compt_name, const char* compt_val)
{
    uint8_t char_val = 0;
    const char indicator = identify(compt_name);
    if (!is_byte(compt_val))
        char_val = atoi(compt_val);
    else
        return WRONG_ARG;

    switch (indicator) {
        case 'r':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    (*arr)[i][j].r = char_val;
            }
            printf("Red component was changed to %u\n", char_val);
            return NO_ERROR;
        case 'g':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    (*arr)[i][j].g = char_val;
            }            
            printf("Green component was changed to %u\n", char_val);
            return NO_ERROR;
        case 'b':
            for (size_t i = 0; i < bmih->height; i++) {
                for (size_t j = 0; j < bmih->width; j++)
                    (*arr)[i][j].b = char_val;
            }
            printf("Blue component was changed to %u\n", char_val);
            return NO_ERROR;
        default:
            return WRONG_ARG;
    }
}
