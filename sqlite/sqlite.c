#include <stdint.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>


typedef struct {
    const char *createQuery;
    const char *insertQuery;
} Queries;

typedef struct {
    unsigned char *blob;
    const char *text;
} Data; 


int main() {
    Queries Q;
    Data D;
    sqlite3 *ppDb;
    sqlite3_stmt *stmt;

    Q.createQuery = "CREATE TABLE IF NOT EXISTS tb (k INTEGER PRIMARY KEY, y VARCHAR(69),z BLOB);";
    Q.insertQuery = "INSERT INTO tb (y, z) VALUES (?, ?);";


    int rc = sqlite3_open("test.db", &ppDb);
    if (rc) {
        fprintf(stderr, "%s", sqlite3_errmsg(ppDb));
        return 1;
    }

    sqlite3_exec(ppDb, Q.createQuery, NULL, NULL, NULL);
    sqlite3_prepare_v2(ppDb, Q.insertQuery, -1, &stmt, NULL);
    
    D.blob = (unsigned char *)malloc(5);

    sqlite3_bind_text(stmt, 1, "_", -1, NULL);
    sqlite3_bind_blob(stmt, 2, D.blob, 5, NULL);
    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(ppDb);
    return 0;
}
