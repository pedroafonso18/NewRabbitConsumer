#include "../include/D_Fetch.h"

#include <iostream>

bool Fetch::recordExists(std::string table, std::string id) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);

    try {
        std::string query = "SELECT 1 FROM " + table + " WHERE id = $1";

        auto result = transaction.exec_params(query, id);
        return !result.empty();
    } catch (std::exception& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}