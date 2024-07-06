#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LOG_MESSAGE 256

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

typedef struct {
    FILE* file;
    LogLevel min_level;
} Logger;

const char* log_level_strings[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR"
};

Logger* create_logger(const char* filename, LogLevel min_level) {
    Logger* logger = (Logger*)malloc(sizeof(Logger));
    if (logger == NULL) {
        fprintf(stderr, "Failed to allocate memory for logger\n");
        return NULL;
    }

    logger->file = fopen(filename, "a");
    if (logger->file == NULL) {
        fprintf(stderr, "Failed to open log file: %s\n", filename);
        free(logger);
        return NULL;
    }

    logger->min_level = min_level;
    return logger;
}

void close_logger(Logger* logger) {
    if (logger) {
        if (logger->file) {
            fclose(logger->file);
        }
        free(logger);
    }
}

void log_message(Logger* logger, LogLevel level, const char* module, const char* message) {
    if (level < logger->min_level) {
        return;
    }

    time_t now;
    time(&now);
    struct tm* local_time = localtime(&now);

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);

    fprintf(logger->file, "[%s] [%s] [%s]: %s\n", 
            timestamp, log_level_strings[level], module, message);
    fflush(logger->file);
}

int main() {
    Logger* logger = create_logger("industrial_log.txt", LOG_DEBUG);
    if (logger == NULL) {
        return 1;
    }

    log_message(logger, LOG_DEBUG, "MAIN", "This is a debug message");
    log_message(logger, LOG_INFO, "SYSTEM", "System initialized successfully");
    log_message(logger, LOG_WARNING, "SENSOR", "Temperature approaching critical level");
    log_message(logger, LOG_ERROR, "NETWORK", "Connection to remote server lost");

    close_logger(logger);
    return 0;
}