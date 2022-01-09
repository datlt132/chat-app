#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int validate_alphanumber(char *str);
int validate_blank(char *str);
int validate_number(char *str);
int validate_ip(char *ip);

int split( char *str, char c, char ***arr);