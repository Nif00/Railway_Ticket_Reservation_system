#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <thread>

extern bool logging_disabled;

void add_log(const std::string& message);
