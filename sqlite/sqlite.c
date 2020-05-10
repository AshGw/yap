#include <stdint.h>
#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *ppDb;
    int rc = sqlite3_open("test.db", &ppDb);
    if (rc) {
        fprintf(stderr,"%s",sqlite3_errmsg(ppDb));
        return 1;
    }
    const char *createQuery = "CREATE TABLE IF NOT EXISTS tb (k INTEGER PRIMARY KEY, y VARCHAR(69),z BLOB);"; 
    rc = sqlite3_exec(ppDb,createQuery,NULL,NULL,NULL);
    if (rc){
        fprintf(stderr,"%s",sqlite3_errmsg(ppDb)); 
    }
    const char *insertQuery = "INSERT INTO tb (y, z) VALUES ('_', x'01020304');";
    rc = sqlite3_exec(ppDb,insertQuery,NULL,NULL,NULL);
    if (rc){
        fprintf(stderr,"%s",sqlite3_errmsg(ppDb)); 
    }
    sqlite3_close(ppDb);
    return 0; 
}