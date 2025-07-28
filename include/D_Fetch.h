#ifndef D_FETCH_H
#define D_FETCH_H
#include "Database.h"

class Fetch {
private:
    std::unique_ptr<Database> ownedDb;
    Database* db;
public:
    explicit Fetch(Database& db) : db(&db) {}

    explicit Fetch(std::string dbUrl)
        : ownedDb(std::make_unique<Database>(dbUrl)), db(ownedDb.get()) {}

    bool recordExists(std::string table, std::string id);

};

#endif //D_FETCH_H
