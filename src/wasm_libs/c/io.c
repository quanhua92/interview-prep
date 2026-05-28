#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char buf[65536];

int *read_ints(int *count)
{
    if (!fgets(buf, sizeof(buf), stdin)) {
        *count = 0;
        return malloc(sizeof(int));
    }
    int cap = 256;
    int *arr = malloc(cap * sizeof(int));
    int n = 0;
    char *p = buf;
    while (*p) {
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        if (!*p) break;
        if (n >= cap) {
            cap *= 2;
            arr = realloc(arr, cap * sizeof(int));
        }
        arr[n++] = atoi(p);
        while (*p && *p != ' ' && *p != '\t' && *p != '\r' && *p != '\n') p++;
    }
    *count = n;
    return arr;
}

int read_int(void)
{
    int *a = read_ints(&(int){0});
    int v = a[0];
    free(a);
    return v;
}

char *read_line(void)
{
    if (!fgets(buf, sizeof(buf), stdin)) {
        char *s = malloc(1);
        s[0] = '\0';
        return s;
    }
    int len = (int)strlen(buf);
    while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r'))
        buf[--len] = '\0';
    char *s = malloc(len + 1);
    memcpy(s, buf, len + 1);
    return s;
}

void write_int(int val)
{
    printf("%d\n", val);
}

void write_ints(int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}

void write_string(const char *s)
{
    printf("%s\n", s);
}

void write_bool(int b)
{
    printf("%s\n", b ? "true" : "false");
}
