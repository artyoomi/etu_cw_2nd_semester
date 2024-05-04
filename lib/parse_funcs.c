#include "../include/parse_funcs.h"

// -1 if parse failed else parsed number
int32_t parse_unsigned_char(const char* arg, uint8_t* val)
{
    regex_t regex;
    int32_t reti = regcomp(&regex,
                           "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$",
                           REG_EXTENDED);
    if (reti) {
        error_return("Could not compile regex\n", PARSE_ERROR);
    }
    
    reti = regexec(&regex, arg, 0, NULL, 0);
    if (!reti) {
        *val = atoi(arg);
        regfree(&regex);
        return NO_ERROR;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        error_return("Component value must be in range [0..255]\n",
                     PARSE_ERROR);
    } else {
	    char err_buf[100];
		regerror(reti, &regex, err_buf, sizeof(err_buf));
        regfree(&regex);
		error_return_warg("Regex match failed %s\n",
		                  PARSE_ERROR, err_buf);
    }
}

int32_t parse_coords(const char* arg, int64_t** val_arr)
{
    const uint32_t max_groups = 3;
    regex_t regex;
    regmatch_t groups[max_groups];
    
    const char* reg_str = "^(-?[0-9]+)\\.(-?[0-9]+)$";    
    int32_t reti = regcomp(&regex, reg_str, REG_EXTENDED);
    if (reti) {
        error_return("Could not compile regex\n", PARSE_ERROR);
    }
    
    reti = regexec(&regex, arg, max_groups, groups, 0);
    uint8_t buf_ind = 0;
    char buffer[100];

    // alloc memory to array with x and y component
    *val_arr = (int64_t*)malloc((max_groups - 1) * sizeof(int64_t));
    if (!reti) {
        //*val_arr = 
        for (size_t i = 1; i < max_groups; i++) {
				if (groups[i].rm_so == -1)
					break;

				for (size_t j = groups[i].rm_so; j < groups[i].rm_eo; j++)
					//printf("%c", arg[j]);
				    buffer[buf_ind++] = arg[j];
				    
				buffer[buf_ind] = '\0';
				(*val_arr)[i - 1] = atoi(buffer);
				buf_ind = 0;
		}
		        
        regfree(&regex);
        
        return NO_ERROR;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
            error_return("Components values must be greater or equal to 0\n",
                         PARSE_ERROR);
    } else {
        char err_buf[100];
        regerror(reti, &regex, err_buf, sizeof(err_buf));
        regfree(&regex);
        error_return_warg("Regex match failed %s\n", PARSE_ERROR, err_buf);
    }
}

int32_t parse_posit_number(const char* arg, uint32_t* val)
{
    regex_t regex;
    int32_t reti = regcomp(&regex, "^[1-9][0-9]*$", REG_EXTENDED);
    if (reti)
        error_return("Could not compile regex\n", PARSE_ERROR);
    
    reti = regexec(&regex, arg, 0, NULL, 0);
    if (!reti) {
        *val = atoi(arg);
        regfree(&regex);
        return NO_ERROR;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        error_return("Component value must be greater than 0\n",
                     PARSE_ERROR);
    } else {
	    char err_buf[100];
		regerror(reti, &regex, err_buf, sizeof(err_buf));
        regfree(&regex);
		error_return_warg("Regex match failed %s\n",
		                  PARSE_ERROR, err_buf);
    }
}

int32_t parse_comps(const char* arg, RGB* color)
{
    const uint32_t max_groups = 4;
    regex_t regex;
    regmatch_t groups[max_groups];
    
    const char* reg_str = "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])"
                          "\\." 
                          "([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])"
                          "\\."
                          "([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$";    
    int32_t reti = regcomp(&regex, reg_str, REG_EXTENDED);
    if (reti) {
        error_return("Could not compile regex\n", PARSE_ERROR);
    }
    
    reti = regexec(&regex, arg, max_groups, groups, 0);
    uint8_t buf_ind = 0;
    char buffer[100] = "";

    // alloc memory to array with r, g and b components
    if (!reti) {
        for (size_t i = 1; i < max_groups; i++) {
				if (groups[i].rm_so == -1)
					break;

				for (size_t j = groups[i].rm_so; j < groups[i].rm_eo; j++)
				    buffer[buf_ind++] = arg[j];
				    
				buffer[buf_ind] = '\0';
				//(*val_arr)[i - 1] = atoi(buffer);
				if (i - 1 == 0)
				    color->r = atoi(buffer);
				else if (i - 2 == 0)
				    color->g = atoi(buffer);
				else if (i - 3 == 0)
				    color->b = atoi(buffer);
				buf_ind = 0;
		}
		        
        regfree(&regex);
        return NO_ERROR;
    } else if (reti == REG_NOMATCH) {
        regfree(&regex);
        error_return("Component values must be in range [0..255]\n", 
                     PARSE_ERROR);
    } else {
        char err_buf[100];
        regerror(reti, &regex, err_buf, sizeof(err_buf));
        regfree(&regex);
        error_return_warg("Regex match failed %s\n",
                          PARSE_ERROR, err_buf);
    }
}
