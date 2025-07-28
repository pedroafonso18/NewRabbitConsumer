#ifndef INSERTTYPES_H
#define INSERTTYPES_H
#include <string>

typedef struct {
    std::string id;
    std::string gs_id;
    std::string recipient_id;
    std::string status;
    std::string gs_app_id;
    std::string timestamp;
} Enqueued;

typedef struct {
    std::string id;
    std::string display_phone_number;
    std::string phone_number_id;
    std::string conversation_expiration_timestamp;
    std::string conversation_id;
    std::string conversation_type;
    std::string gs_id;
    std::string meta_msg_id;
    bool pricing_billable;
    std::string pricing_category;
    std::string pricing_model;
    std::string recipient_id;
    std::string status;
    std::string changes_id;
    std::string gs_app_id;
    std::string timestamp;
} Sent;

typedef struct {
    std::string id;
    std::string display_phone_number;
    std::string phone_number_id;
    std::string conversation_expiration_timestamp;
    std::string conversation_id;
    std::string conversation_type;
    std::string gs_id;
    std::string meta_msg_id;
    bool pricing_billable;
    std::string pricing_category;
    std::string pricing_model;
    std::string recipient_id;
    std::string status;
    std::string changes_id;
    std::string gs_app_id;
    std::string timestamp;
} Delivered;

typedef struct {
    std::string id;
    std::string display_phone_number;
    std::string phone_number_id;
    std::string gs_id;
    std::string meta_msg_id;
    std::string recipient_id;
    std::string status;
    std::string changes_id;
    std::string gs_app_id;
    std::string timestamp;
} Read;

typedef struct {
    std::string id;
    std::string display_phone_number;
    std::string phone_number_id;
    int error_code;
    std::string error_details;
    std::string title;
    std::string gs_id;
    std::string meta_msg_id;
    std::string recipient_id;
    std::string status;
    std::string changes_id;
    std::string gs_app_id;
    std::string timestamp;
} Failed;

typedef struct {
    std::string gs_id;
    std::string recipient_id;
    int error_code;
    std::string error_title;
    std::string status;
    std::string timestamp;
    std::string raw_json;
} TemplateError;

typedef struct {
    std::string wamid;
    std::string contact_wa_id;
    std::string msg_text;
    std::string msg_timestamp;
    std::string msg_type;
    std::string display_phone_number;
    std::string phone_number_id;
    std::string changes_id;
    std::string gs_app_id;
    std::string ctwa_clid;
    std::string app;
    int version;
    std::string phone;
    std::string name;
    std::string country_code;
    std::string dial_code;
    std::string headline;
    std::string referral_body;
    std::string source_type;
    std::string source_id;
    std::string source_url;
    std::string media_type;
    std::string video_url;
    std::string thumbnail_url;
    std::string tag;
    std::string protocol_number;
} MessageLog;

typedef struct {
    std::string phone;
    std::string ctwa_clid;
    std::string source_id;
    std::string event_id;
} GTM;



#endif //INSERTTYPES_H
