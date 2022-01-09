#include "util.h"

int validate_alphanumber(char *str)
{
   while (*str)
   {
      if (!isalnum(*str))
      {
         return 0;
      }
      str++;
   }
   return 1;
}

int validate_blank(char *str)
{
   while (*str)
   {
      if (isblank(*str))
      {
         return 0;
      }
      str++;
   }
   return 1;
}
// Check num
int validate_number(char *str)
{
   while (*str)
   {
      if (!isdigit(*str))
      {
         return 0;
      }
      str++;
   }
   return 1;
}
int validate_ip(char *ip)
{
   int i, num, dots = 0;
   char *ptr;
   if (ip == NULL)
      return 0;
   ptr = strtok(ip, ".");
   if (ptr == NULL)
      return 0;
   while (ptr)
   {
      if (!validate_number(ptr))
         return 0;
      num = atoi(ptr);
      if (num >= 0 && num <= 255)
      {
         ptr = strtok(NULL, ".");
         if (ptr != NULL)
            dots++;
      }
      else
         return 0;
   }
   if (dots != 3)
      return 0;
   return 1;
}

// split string with delim
int split( char *str, char c, char ***arr)
{
   int count = 1;
   int token_len = 1;
   int i = 0;
   char *p;
   char *t;

   p = str;
   while (*p != '\0')
   {
      if (*p == c)
         count++;
      p++;
   }

   *arr = (char **)malloc(sizeof(char *) * count);
   if (*arr == NULL)
      exit(1);

   p = str;
   while (*p != '\0')
   {
      if (*p == c)
      {
         (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
         if ((*arr)[i] == NULL)
            exit(1);

         token_len = 0;
         i++;
      }
      p++;
      token_len++;
   }
   (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
   if ((*arr)[i] == NULL)
      exit(1);

   i = 0;
   p = str;
   t = ((*arr)[i]);
   while (*p != '\0')
   {
      if (*p != c && *p != '\0')
      {
         *t = *p;
         t++;
      }
      else
      {
         *t = '\0';
         i++;
         t = ((*arr)[i]);
      }
      p++;
   }

   return count;
}