#ifndef D_INSERT_H
#define D_INSERT_H

#include "Database.h"
#include "InsertTypes.h"
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

    void insertEnqueued(Enqueued &enqueued);
    void insertSent(Sent &sent);
    void insertDelivered(Delivered &delivered);
    void insertRead(Read &read);
    void insertFailed(Failed &failed);
    void insertUnmapped(std::string &data);
    void insertTemplateError(TemplateError &err);
    void insertErrorPayload(std::string &payload);
    void insertMessageLogs(MessageLog &log);
    void insertGtm(GTM &gtm);
    void insertIssue(std::string app_id);
    void insertBan(std::string app_id);
};

#endif // D_INSERT_H
