#include "../include/D_Insert.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "../include/Utils.h"

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
            std::clog << "ERROR: error when inserting Sent.\n";
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
    pqxx::work transaction(*c);
    try {
        auto result = transaction.exec_params("INSERT INTO delivered(id, display_phone_number, phone_number_id, conversation_id, conversation_type, gs_id, meta_msg_id, pricing_billable, pricing_category, pricing_model, recipient_id, status, changes_id, gs_app_id, timestamp) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15) ON CONFLICT (id) DO NOTHING", delivered.id, delivered.display_phone_number, delivered.phone_number_id, delivered.conversation_id, delivered.conversation_id, delivered.conversation_id, delivered.conversation_type, delivered.gs_id, delivered.meta_msg_id, delivered.pricing_billable, delivered.pricing_category, delivered.pricing_model, delivered.recipient_id, delivered.status, delivered.changes_id, delivered.gs_app_id, delivered.timestamp);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Delivered.\n";
        }

    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertRead(Read &read) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        auto result = transaction.exec_params("INSERT INTO read(id, display_phone_number, phone_number_id, gs_id, meta_msg_id, recipient_id, status, changes_id, gs_app_id, timestamp) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10) ON CONFLICT (id) DO NOTHING", read.id, read.display_phone_number, read.phone_number_id, read.gs_id, read.meta_msg_id, read.recipient_id, read.status, read.changes_id, read.status, read.changes_id, read.gs_app_id, read.timestamp);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Read.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertFailed(Failed &failed) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        auto result = transaction.exec_params("INSERT INTO failed(id, display_phone_number, phone_number_id, erro_code, erro_details, erro_message, title, gs_id, meta_msg_id, recipient_id, status, changes_id, gs_app_id, timestamp) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14)", failed.id, failed.display_phone_number, failed.phone_number_id, failed.error_code, failed.error_details, failed.error_message, failed.title, failed.gs_id, failed.meta_msg_id, failed.recipient_id, failed.recipient_id, failed.status, failed.changes_id, failed.gs_app_id, failed.timestamp);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Failed.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertUnmapped(std::string &data) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        auto result = transaction.exec_params("INSERT INTO unmapped(valor) VALUES ($1)", data);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting Unmapped.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertTemplateError(TemplateError &err) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        auto result = transaction.exec_params("INSERT INTO template_errors(gs_id, recipient_id, error_code, error_title, status, timestamp, raw_json) VALUES ($1, $2, $3, $4, $5, $6, $7)", err.gs_id, err.recipient_id, err.error_code, err.error_title, err.status, err.timestamp, err.raw_json);
        if (!result.affected_rows() == 0) {
            std::clog << "ERROR: error when inserting TemplateError.\n";
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertErrorPayload(std::string &payload) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    try {
        nlohmann::json error_json = nlohmann::json::parse(payload);

        if (error_json.contains("gs_id") && error_json["gs_id"].is_string() &&
            error_json.contains("recipient_id") && error_json["recipient_id"].is_string() &&
            error_json.contains("status") && error_json["status"].is_string() &&
            error_json.contains("timestamp") && error_json["timestamp"].is_number()) {

            std::string gs_id_str = error_json["gs_id"].get<std::string>();
            std::string recipient_id = error_json["recipient_id"].get<std::string>();
            std::string status = error_json["status"].get<std::string>();
            int64_t timestamp_val = error_json["timestamp"].get<int64_t>();

            int64_t timestamp_secs = timestamp_val / 1000;

            time_t time_val = static_cast<time_t>(timestamp_secs);
            char time_buf[30];
            std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", std::gmtime(&time_val));
            std::string timestamp_str(time_buf);

            if (error_json.contains("errors") && error_json["errors"].is_array() && !error_json["errors"].empty()) {
                const nlohmann::json& first_error = error_json["errors"][0];

                int error_code = 0;
                if (first_error.contains("code") && first_error["code"].is_number()) {
                    error_code = first_error["code"].get<int>();
                }

                std::string error_title = "Unknown error";
                if (first_error.contains("title") && first_error["title"].is_string()) {
                    error_title = first_error["title"].get<std::string>();
                }

                TemplateError err;
                err.gs_id = gs_id_str;
                err.recipient_id = recipient_id;
                err.error_code = error_code;
                err.error_title = error_title;
                err.status = status;
                err.timestamp = timestamp_str;
                err.raw_json = payload;

                insertTemplateError(err);
                return;
            }
        }
    } catch (const nlohmann::json::exception& e) {
        std::clog << "JSON parsing error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::clog << "Error processing payload: " << e.what() << "\n";
    }

    insertUnmapped(payload);
}

void Insert::insertMessageLogs(MessageLog &log) {
    std::clog << "STEAK: Attempting to insert message into logs database - WAMID: " << log.wamid << '\n';

    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);

    auto utc_timestamp = Utils::getTimestamp(log.msg_timestamp);

    try {
        transaction.exec("SET statement_timeout = '30s'");
        transaction.exec("SET idle_in_transaction_session_timeout = '30s'");
        auto result = transaction.exec_params("INSERT INTO logstrafegohuggy(wamid, contact_wa_id, msg_text, timestamp, type, display_phone_number, phone_number_id, changes_id, gs_app_id, ctwa_clid, app, version, phone, name, country_code, dial_code, headline, referral_body,source_type, source_id, source_url, media_type, video_url, thumbnail_url, tag, protocol_number) VALUES ( $1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12,$13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, $25, $26)", log.wamid, log.contact_wa_id, log.msg_text, utc_timestamp, log.msg_type, log.display_phone_number, log.phone_number_id, log.changes_id, log.gs_app_id, log.ctwa_clid, log.app, log.version, log.phone, log.name, log.country_code, log.dial_code, log.headline, log.referral_body, log.source_type, log.source_id, log.source_url, log.media_type, log.video_url, log.thumbnail_url, log.tag, log.protocol_number);

        if (result.affected_rows() == 0) {
            std::clog << "STEAK: SUCCESSFULLY INSERTED MESSAGE INTO THE LOGS DATABASE - WAMID: " << log.wamid << '\n';
        } else {
            std::clog << "STEAK: FAILED TO INSERT MESSAGE INTO THE LOGS DATABASE - WAMID: " << log.wamid << '\n';
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}


void Insert::insertGtm(GTM &gtm) {
    std::clog << "RICE: Attempting to insert message into gtm database - CTWA_CLID: " << gtm.ctwa_clid << '\n';

    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);

    try {
        transaction.exec("SET statement_timeout = '30s'");
        transaction.exec("SET idle_in_transaction_session_timeout = '30s'");
        auto result = transaction.exec_params("INSERT INTO logs_gtm(phone, ctwa_clid, source_id, event_id) VALUES ($1, $2, $3, $4) ON CONFLICT (event_id) DO NOTHING", gtm.phone, gtm.ctwa_clid, gtm.source_id, gtm.event_id);
        if (result.affected_rows() == 0) {
            std::clog << "RICE: SUCCESFULLY INSERTED MESSAGE INTO THE GTM DATABASE - CTWA_CLID: " << gtm.ctwa_clid << '\n';
        } else {
            std::clog << "RICE: FAILED TO INSERT MESSAGE INTO THE GTM DATABASE - CTWA_CLID: " << gtm.ctwa_clid << '\n';
        }
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}


void Insert::insertIssue(std::string app_id) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        transaction.exec("SET statement_timeout = '30s'");
        transaction.exec("SET idle_in_transaction_session_timeout = '30s'");
        auto result = transaction.exec_params("UPDATE parametros SET issues = issues + 1, ultima_issue_dia = NOW() WHERE app_id = $1", app_id);
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}

void Insert::insertBan(std::string app_id) {
    auto c = db->getConnection();
    if (!c->is_open()) {
        std::clog << "ERROR: db connection is not open.\n";
        throw std::runtime_error("DB CONNECTION IS NOT ACTIVE");
    }
    pqxx::work transaction(*c);
    try {
        transaction.exec("SET statement_timeout = '30s'");
        transaction.exec("SET idle_in_transaction_session_timeout = '30s'");
        auto result = transaction.exec_params("UPDATE parametros SET restriction = 'BANNED' WHERE app_id = $1", app_id);
    } catch (pqxx::sql_error& e) {
        transaction.abort();
        throw std::runtime_error("Database error: " + std::string(e.what()));
    }
}