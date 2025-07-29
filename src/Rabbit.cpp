#include "../include/Rabbit.h"
#include <rabbitmq-c/framing.h>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <optional>

Rabbit::Rabbit(const std::string& host, int port, const std::string& user,
               const std::string& pass, const std::string& vhost)
    : hostname(host), port(port), username(user), password(pass), vhost(vhost), conn(nullptr), socket(nullptr) {
}

Rabbit::~Rabbit() {
    disconnect();
}

void Rabbit::checkReply(amqp_rpc_reply_t reply, const std::string& context) {
    switch (reply.reply_type) {
        case AMQP_RESPONSE_NORMAL:
            return;
        case AMQP_RESPONSE_NONE:
            throw std::runtime_error(context + ": missing RPC reply");
        case AMQP_RESPONSE_LIBRARY_EXCEPTION:
            throw std::runtime_error(context + ": " + amqp_error_string2(reply.library_error));
        case AMQP_RESPONSE_SERVER_EXCEPTION:
            if (reply.reply.id == AMQP_CHANNEL_CLOSE_METHOD) {
                amqp_channel_close_t *close = (amqp_channel_close_t *)reply.reply.decoded;
                throw std::runtime_error(context + ": channel closed - " +
                    std::string((char *)close->reply_text.bytes, close->reply_text.len));
            } else if (reply.reply.id == AMQP_CONNECTION_CLOSE_METHOD) {
                amqp_connection_close_t *close = (amqp_connection_close_t *)reply.reply.decoded;
                throw std::runtime_error(context + ": connection closed - " +
                    std::string((char *)close->reply_text.bytes, close->reply_text.len));
            }
            throw std::runtime_error(context + ": server exception");
        default:
            throw std::runtime_error(context + ": unknown reply type");
    }
}

bool Rabbit::connect() {
    conn = amqp_new_connection();
    if (!conn) {
        std::cerr << "Failed to create connection" << std::endl;
        return false;
    }

    socket = amqp_tcp_socket_new(conn);
    if (!socket) {
        std::cerr << "Failed to create TCP socket" << std::endl;
        amqp_destroy_connection(conn);
        conn = nullptr;
        return false;
    }

    int status = amqp_socket_open(socket, hostname.c_str(), port);
    if (status) {
        std::cerr << "Failed to open TCP socket: " << status << std::endl;
        amqp_destroy_connection(conn);
        conn = nullptr;
        socket = nullptr;
        return false;
    }

    amqp_rpc_reply_t reply = amqp_login(conn, vhost.c_str(), 0, 131072, 0,
        AMQP_SASL_METHOD_PLAIN, username.c_str(), password.c_str());

    try {
        checkReply(reply, "Login");
        return true;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error during connection: " << e.what() << std::endl;
        amqp_destroy_connection(conn);
        conn = nullptr;
        socket = nullptr;
        return false;
    }
}

void Rabbit::disconnect() {
    if (conn) {
        try {
            amqp_rpc_reply_t reply = amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
            checkReply(reply, "Closing connection");
        } catch (const std::exception& e) {
            std::cerr << "Error during disconnect: " << e.what() << std::endl;
        }

        amqp_destroy_connection(conn);
        conn = nullptr;
        socket = nullptr;
    }
}

bool Rabbit::isConnected() const {
    return conn != nullptr;
}

bool Rabbit::openChannel(int channel) {
    if (!isConnected()) {
        std::cerr << "Not connected to RabbitMQ" << std::endl;
        return false;
    }

    amqp_channel_open(conn, channel);
    try {
        checkReply(amqp_get_rpc_reply(conn), "Opening channel");
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to open channel: " << e.what() << std::endl;
        return false;
    }
}

void Rabbit::closeChannel(int channel) {
    if (!isConnected()) {
        return;
    }

    try {
        amqp_channel_close(conn, channel, AMQP_REPLY_SUCCESS);
        checkReply(amqp_get_rpc_reply(conn), "Closing channel");
    } catch (const std::exception& e) {
        std::cerr << "Error closing channel: " << e.what() << std::endl;
    }
}

void Rabbit::declareQueue(int channel, const std::string& queueName, bool durable,
                           bool exclusive, bool autoDelete) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to RabbitMQ");
    }

    amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, channel,
        amqp_cstring_bytes(queueName.c_str()),
        0, // passive
        durable ? 1 : 0,
        exclusive ? 1 : 0,
        autoDelete ? 1 : 0,
        amqp_empty_table);

    checkReply(amqp_get_rpc_reply(conn), "Declaring queue");
}

void Rabbit::bindQueue(int channel, const std::string& queueName,
                        const std::string& exchangeName, const std::string& routingKey) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to RabbitMQ");
    }

    amqp_queue_bind(conn, channel,
        amqp_cstring_bytes(queueName.c_str()),
        amqp_cstring_bytes(exchangeName.c_str()),
        amqp_cstring_bytes(routingKey.c_str()),
        amqp_empty_table);

    checkReply(amqp_get_rpc_reply(conn), "Binding queue");
}

void Rabbit::declareExchange(int channel, const std::string& exchangeName,
                             const std::string& exchangeType, bool durable, bool autoDelete) {
    if (!isConnected()) {
        throw std::runtime_error("Not connected to RabbitMQ");
    }

    amqp_exchange_declare(conn, channel,
        amqp_cstring_bytes(exchangeName.c_str()),
        amqp_cstring_bytes(exchangeType.c_str()),
        0,
        durable ? 1 : 0,
        autoDelete ? 1 : 0,
        0,
        amqp_empty_table);

    checkReply(amqp_get_rpc_reply(conn), "Declaring exchange");
}

bool Rabbit::publish(int channel, const std::string& exchange, const std::string& routingKey,
                    const std::string& message, bool mandatory) {
    if (!isConnected()) {
        std::cerr << "Not connected to RabbitMQ" << std::endl;
        return false;
    }

    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("text/plain");
    props.delivery_mode = 2;

    int status = amqp_basic_publish(conn, channel,
        amqp_cstring_bytes(exchange.c_str()),
        amqp_cstring_bytes(routingKey.c_str()),
        mandatory ? 1 : 0,
        0,
        &props,
        amqp_cstring_bytes(message.c_str()));

    if (status != 0) {
        std::cerr << "Failed to publish message: " << status << std::endl;
        return false;
    }

    return true;
}

bool Rabbit::basicConsume(int channel, const std::string& queueName, const std::string& consumerTag) {
    if (!isConnected()) {
        std::cerr << "Not connected to RabbitMQ" << std::endl;
        return false;
    }

    amqp_basic_consume(conn, channel,
        amqp_cstring_bytes(queueName.c_str()),
        consumerTag.empty() ? amqp_empty_bytes : amqp_cstring_bytes(consumerTag.c_str()),
        0,
        1,
        0,
        amqp_empty_table);

    try {
        checkReply(amqp_get_rpc_reply(conn), "Starting consumer");
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to start consumer: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::string> Rabbit::getMessage(int channel, int timeoutMs) {
    if (!isConnected()) {
        std::cerr << "Not connected to RabbitMQ" << std::endl;
        return std::nullopt;
    }

    struct timeval timeout;
    timeout.tv_sec = timeoutMs / 1000;
    timeout.tv_usec = (timeoutMs % 1000) * 1000;

    amqp_envelope_t envelope;
    amqp_maybe_release_buffers(conn);

    amqp_rpc_reply_t res = amqp_consume_message(conn, &envelope, &timeout, 0);

    if (res.reply_type == AMQP_RESPONSE_NORMAL) {
        std::string message(static_cast<char*>(envelope.message.body.bytes),
                           envelope.message.body.len);
        amqp_destroy_envelope(&envelope);
        return message;
    } else if (res.reply_type == AMQP_RESPONSE_LIBRARY_EXCEPTION &&
               res.library_error == AMQP_STATUS_TIMEOUT) {
        return std::nullopt;
    } else {
        try {
            checkReply(res, "Consuming message");
        } catch (const std::exception& e) {
            std::cerr << "Error consuming message: " << e.what() << std::endl;
        }
        return std::nullopt;
    }
}

bool Rabbit::consumeMessages(int channel, const std::string& queueName,
                            std::function<void(const std::string&)> callback,
                            const std::string& consumerTag) {
    if (!basicConsume(channel, queueName, consumerTag)) {
        return false;
    }

    try {
        while (true) {
            auto messageOpt = getMessage(channel, 100);
            if (messageOpt) {
                callback(*messageOpt);
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in consume loop: " << e.what() << std::endl;
        return false;
    }

    return true;
}
