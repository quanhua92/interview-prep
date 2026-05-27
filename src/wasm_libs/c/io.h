#ifndef IO_H
#define IO_H

int *read_ints(int *count);
char *read_line(void);
void write_int(int val);
void write_ints(int *arr, int n);
void write_string(const char *s);
void write_bool(int b);

#endif
