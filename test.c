#include "util.h"
#include "database.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
   int i;
   fprintf(stderr, "%s: ", (const char *)data);
   for (i = 0; i < argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
   // int i;
   // char *s = "Hello, this is a test module for the string splitting.";
   // int c = 0;
   // char **arr = NULL;

   // c = split(s, ' ', &arr);

   // printf("found %d tokens.\n", c);

   // for (i = 0; i < c; i++)
   //     printf("string #%d: %s\n", i, arr[i]);

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char *data = "Callback function called";

   /* Open database */
   db = open_db();

   /* Create SQL statement */
   sql = "SELECT * from MEMBER";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
   if (rc != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}