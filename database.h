#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <sys/stat.h>
// #include <gio/gio.h>
// #include "cJSON.h"
#include <sqlite3.h>
#define DB_PATH "database.db"

typedef struct s_member{
    int user_id;
    int room_id;
    int date;
    int   prm;
}              t_member;

typedef struct s_db_message {
    int user_id;
    int room_id;
    int message_id;
    int date;
    int status;
    int type;
    int file_size;
    char *message;
    char *file_name;
}              t_db_message;

typedef struct s_db_user {
    int user_id;
    int date;
    char *pass;
    char *auth_token;
    char *name;
    char *login;
    char *desc;
}             t_db_user;

typedef struct s_db_room {
    char *room_name;
    int room_id;
    int user_id;
    int date;
    int type;
    char *desc;
}              t_db_room;


void create_messages_table(sqlite3 *db);
void create_members_table(sqlite3 *db);
void create_rooms_table(sqlite3 *db);
void create_users_table(sqlite3 *db);
void create_tables(sqlite3 *db);
sqlite3 *open_db();