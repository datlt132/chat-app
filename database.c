#include <sqlite3.h>
#include "database.h"


void create_messages_table(sqlite3 *db)
{
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS MESSAGES("
                     "MESSAGE_ID    INTEGER PRIMARY KEY NOT NULL,"
                     "USER_ID       INTEGER             NOT NULL,"
                     "ROOM_ID       INTEGER             NOT NULL,"
                     "DATE          INTEGER             NOT NULL,"
                     "MESSAGE       TEXT                        ,"
                     "TYPE          INTEGER             NOT NULL,"
                     "FILE_SIZE     INTEGER                     ,"
                     "FILE_NAME     TEXT                        ,"
                     "STATUS        INTEGER             NOT NULL);",
                 0, 0, 0);
}

void create_members_table(sqlite3 *db)
{
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS MEMBERS("
                     "USER_ID        INTEGER NOT NULL,"
                     "ROOM_ID        INTEGER NOT NULL,"
                     "DATE           INTEGER NOT NULL,"
                     "PERMISSION     INTEGER NOT NULL);",
                 0, 0, 0);
}

void create_rooms_table(sqlite3 *db)
{
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS ROOMS("
                     "ID                 INTEGER PRIMARY KEY NOT NULL,"
                     "NAME               TEXT                NOT NULL,"
                     "USER_ID            INTEGER             NOT NULL,"
                     "DATE               INT                 NOT NULL,"
                     "DESC               TEXT                        ,"
                     "TYPE               INT                 NOT NULL);",
                 0, 0, 0);
}

void create_users_table(sqlite3 *db)
{
    sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS USERS("
                     "ID             INTEGER PRIMARY KEY NOT NULL,"
                     "NAME           TEXT                NOT NULL,"
                     "LOGIN          TEXT  UNIQUE        NOT NULL,"
                     "PASS           TEXT                NOT NULL,"
                     "AUTH_TOKEN     TEXT                NOT NULL,"
                     "DATE           INTEGER             NOT NULL,"
                     "DESC           TEXT                );",
                 0, 0, 0);
}

void create_tables(sqlite3 *db)
{
    create_users_table(db);
    create_rooms_table(db);
    create_members_table(db);
    create_messages_table(db);
}

sqlite3 *open_db()
{
    sqlite3 *db;
    int rc;

    rc = sqlite3_open(DB_PATH, &db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }
    else
    {
        printf("Opened database successfully\n");
    }
    create_tables(db);
    return db;
}