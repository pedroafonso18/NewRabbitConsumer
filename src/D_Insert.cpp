#include "../include/D_Insert.h"

#include <iostream>

void Insert::insertEnqueued(Enqueued &enqueued) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);

    try {
        auto result = transaction.exec_params("INSERT INTO queue(id, gs_id, recipient_id, status, gs_app_id, timestamp) VALUES ($1, $2, $3, $4, $5, $6)", enqueued.id, enqueued.gs_id, enqueued.recipient_id, enqueued.status,enqueued.gs_app_id, enqueued.timestamp);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Enqueued.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertSent(Sent &sent) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);

    try {
        auto result = transaction.exec_params("INSERT INTO sent(id, display_phone_number, phone_number_id, conversation_expiration_timestamp, conversation_id, conversation_type, gs_id, meta_msg_id, pricing_billable, pricing_category, pricing_model, recipient_id, status, changes_id, gs_app_id, timestamp) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16)",
            sent.id, sent.display_phone_number, sent.phone_number_id, sent.conversation_expiration_timestamp, sent.conversation_id, sent.conversation_type, sent.gs_id, sent.meta_msg_id, sent.pricing_billable, sent.pricing_category, sent.pricing_model, sent.recipient_id, sent.status, sent.changes_id, sent.gs_app_id, sent.timestamp);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Enqueued.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertDelivered(Delivered &delivered) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }

}
