#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

extern void log(const std::string& identifier, const std::string& message);

extern void log(const std::string& identifier, const std::string& message, const std::string& message_two);

extern bool toss(bool trigger, const std::string& msg);