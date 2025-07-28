#ifndef CONFIG_H
#define CONFIG_H

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

    Env* env;
public:
    Config();
    ~Config();
    Env* loadEnv();
};

#endif