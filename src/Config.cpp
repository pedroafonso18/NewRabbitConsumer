#include "../include/Config.h"
#include <filesystem>

Config::Config() : env(std::make_unique<Env>()) {
    std::string root_path = "../.env";
    if (std::filesystem::exists(".env")) {
        root_path = ".env";
    }

    std::cout << "Tentando carregar .env de: " << root_path << std::endl;
    dotenv::init(root_path.c_str());
    loadEnv();
}

std::unique_ptr<Config::Env> Config::loadEnv() {
    env->DbUrl = dotenv::getenv("DB_URL", "");
    env->DbUrlDisp = dotenv::getenv("DB_URL_DISP", "");
    env->DbUrlLogs = dotenv::getenv("DB_URL_LOGS", "");
    env->RabbitUrl = dotenv::getenv("RABBIT_URL", "");
    return std::move(env);
}