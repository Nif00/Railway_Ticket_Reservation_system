#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;

extern bool logging_disabled;

void add_log(const string& message);
