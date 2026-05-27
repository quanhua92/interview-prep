#include "io.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

static char buf[65536];

static char *trim_newline(char *s)
{
    int len = (int)std::strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
        s[--len] = '\0';
    return s;
}

std::string read_line()
{
    if (!std::fgets(buf, sizeof(buf), stdin))
        return "";
    return trim_newline(buf);
}

std::vector<int> read_ints()
{
    if (!std::fgets(buf, sizeof(buf), stdin))
        return {};
    std::vector<int> result;
    char *p = std::strtok(buf, " \t\n\r");
    while (p) {
        result.push_back(std::atoi(p));
        p = std::strtok(nullptr, " \t\n\r");
    }
    return result;
}

void write_int(int val)
{
    std::printf("%d\n", val);
}

void write_ints(const std::vector<int> &arr)
{
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i > 0) std::putchar(' ');
        std::printf("%d", arr[i]);
    }
    std::putchar('\n');
}

void write_string(const std::string &s)
{
    std::printf("%s\n", s.c_str());
}

void write_bool(bool b)
{
    std::printf("%s\n", b ? "true" : "false");
}
