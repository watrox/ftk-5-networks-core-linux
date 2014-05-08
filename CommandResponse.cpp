#include "CommandResponse.h"
#include "lgs_constants.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>

CommandResponse::CommandResponse(const int code, const std::string line) {
    this->code = code;
    this->line = line;
    this->is_multi_line = false;
    this->lines = NULL;
    this->lines_count = 0;
}

CommandResponse::CommandResponse(const int code, const std::string * lines, const unsigned int lines_count) {
    this->code = code;
    this->lines = lines;
    this->lines_count = lines_count;
}

CommandResponse::~CommandResponse() {
    if (this->raw_response != NULL) {
        delete this->raw_response;
    }
}

char * CommandResponse::raw() {
    std::stringstream response;
    if (this->is_multi_line) {
        // первая строка начинается с кода и пробела:
        response << this->code << ' ' << lines[0] << CRLF;
        // все строки идут без изменений: 
        for (int i = 0; i < lines_count - 1; i++) {
            response << lines[i] << CRLF;
        }
        // последняя строка начинается с кода и минуса
        response << this->code << '-' << lines[lines_count - 2] << CRLF;
    } else {
        response << this->code << ' ' << this->line << CRLF;
    }
    unsigned int response_length = response.str().length() + 1;
    this->raw_response = new char[response_length];
    memcpy((void*)this->raw_response, (void*) response.str().data(), response_length);
    return this->raw_response;
}
