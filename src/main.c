#include "../include/menu.h"
#include "../include/database.h"
#include "../include/doubly_linked_list.h"

int main(void) {
    FILE* db = fopen("db.csv", "a+");
    List* list = initFromFile(db);
    if(!list) list = init();

    run(db, list);

    clearList(list);
    
    fclose(db);
    return 0;
}