#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    sqlite3 *ppDb;
    int rc = sqlite3_open("test.db", &ppDb);
    if (rc) {
        return 1;
    }
    
    fprintf(stderr,"Some error hit");
    return 0; 
}