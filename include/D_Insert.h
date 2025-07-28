#ifndef D_INSERT_H
#define D_INSERT_H

#include "Database.h"
#include <memory>
#include <string>

class Insert {
private:
    std::unique_ptr<Database> ownedDb;
    Database* db;
public:
    explicit Insert(Database& db) : db(&db) {}

    explicit Insert(std::string dbUrl)
        : ownedDb(std::make_unique<Database>(dbUrl)), db(ownedDb.get()) {}

    void insertEnqueued();
    void insertSent();
    void insertDeliveredSafe();
    void insertRead();
    void insertFailed();
    void insertUnmapped();
    void insertTemplateError();
    void insertErrorPayload();
    void insertMessageLogs();
    void insertGtm();
    void insertIssue();
    void insertBan();
};

#endif // D_INSERT_H
