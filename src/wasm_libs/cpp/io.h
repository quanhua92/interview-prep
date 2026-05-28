#pragma once

#include <string>
#include <vector>

std::vector<int> read_ints();
int read_int();
std::string read_line();
void write_int(int val);
void write_ints(const std::vector<int> &arr);
void write_string(const std::string &s);
void write_bool(bool b);
