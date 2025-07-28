#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <string>
#include "../lib/dotenv.h"

using std::string;

class Config {
private:
    typedef struct {
        string DbUrl;
        string RabbitUrl;
        string DbUrlLogs;
        string DbUrlDisp;
    } Env;

    std::unique_ptr<Env> env;
public:
    Config();
    std::unique_ptr<Env> loadEnv();
};

#endif