#include <stdint.h>
#include <stdio.h>
#include <sqlite3.h>

typedef struct {
    const char *createQuery;
    const char *insertQuery;
} Queries;

typedef struct {
    unsigned char *blob;
    unsigned long blob_size;
    const char *text;
} Data; 


int main() {
    Queries Q;
    Data D;

    Q.createQuery = "CREATE TABLE IF NOT EXISTS tb (k INTEGER PRIMARY KEY, y VARCHAR(69),z BLOB);";
    Q.insertQuery = "INSERT INTO tb (y, z) VALUES (?, ?);";

    sqlite3 *ppDb;

    int rc = sqlite3_open("test.db", &ppDb);
    if (rc) {
        fprintf(stderr, "%s", sqlite3_errmsg(ppDb));
        return 1;
    }

    sqlite3_exec(ppDb, Q.createQuery, NULL, NULL, NULL);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(ppDb, Q.insertQuery, -1, &stmt, NULL);

    D.blob[] = {0x01,0x02,0x03,0x04};

    const unsigned char blob[] = {0x01, 0x02, 0x03, 0x04};
    sqlite3_bind_text(stmt, 1, "_", -1, NULL);
    sqlite3_bind_blob(stmt, 2, blob, sizeof(blob), NULL);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(ppDb));
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(ppDb);
    return 0;
}
