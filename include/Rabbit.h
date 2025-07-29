#ifndef RABBIT_H
#define RABBIT_H

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
#include <string>
#include <memory>
#include <functional>
#include <optional>

class Rabbit {
private:
    amqp_connection_state_t conn;
    amqp_socket_t* socket;
    std::string hostname;
    int port;
    std::string username;
    std::string password;
    std::string vhost;

    void checkReply(amqp_rpc_reply_t reply, const std::string& context);

public:
    Rabbit(const std::string& host = "localhost",
           int port = 5672,
           const std::string& user = "guest",
           const std::string& pass = "guest",
           const std::string& vhost = "/");
    ~Rabbit();

    bool connect();
    void disconnect();
    bool isConnected() const;

    bool openChannel(int channel);
    void closeChannel(int channel);

    void declareQueue(int channel, const std::string& queueName, bool durable = true,
                      bool exclusive = false, bool autoDelete = false);
    void bindQueue(int channel, const std::string& queueName,
                   const std::string& exchangeName, const std::string& routingKey);

    void declareExchange(int channel, const std::string& exchangeName,
                         const std::string& exchangeType, bool durable = true,
                         bool autoDelete = false);

    bool publish(int channel, const std::string& exchange, const std::string& routingKey,
                const std::string& message, bool mandatory = false);

    bool basicConsume(int channel, const std::string& queueName,
                     const std::string& consumerTag = "");
    std::optional<std::string> getMessage(int channel, int timeoutMs = 1000);

    bool consumeMessages(int channel, const std::string& queueName,
                        std::function<void(const std::string&)> callback,
                        const std::string& consumerTag = "");
};

#endif