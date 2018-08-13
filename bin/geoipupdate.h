
#ifndef GEOIPUPDATE_H
#define GEOIPUPDATE_H (1)

#include <curl/curl.h>
#include <stdlib.h>

typedef struct edition_s {
    char *edition_id;
    struct edition_s *next;
} edition_s;

typedef struct {
    int account_id;
    // For a long time, license keys were restricted to 12 characters. However,
    // we want to change this for newer license keys. The array size is
    // arbitrarily 100 as that seems big enough to hold any future license
    // key.
    char license_key[100];
    edition_s *first;
} license_s;

typedef struct {
    license_s license;

    // user might change these before geoipupdate_s_init
    int preserve_file_times;
    int do_not_overwrite_database_directory;
    char *license_file;
    char *database_dir;
    char *host;
    char *proxy;               // 1.2.3.4, 1.2.3.4:1234
    char *proxy_user_password; // user:pwd
    char *lock_file;           // Path to a global runtime lock file.
    int verbose;
    CURL *curl;

} geoipupdate_s;

geoipupdate_s *geoipupdate_s_new(void);
void geoipupdate_s_delete(geoipupdate_s *gu);
void edition_delete_all(geoipupdate_s *gu);

int edition_count(geoipupdate_s *gu);
void edition_insert_once(geoipupdate_s *gu, const char *edition_id);
edition_s *edition_new(const char *edition_id);
void edition_delete(edition_s *p);

void exit_unless(int expr, const char *fmt, ...);
void say_if(int expr, const char *fmt, ...);
void *xcalloc(size_t, size_t);

#define NO_ACCOUNT_ID (0)
#define GEOIP_USERAGENT "geoipupdate/" VERSION

#define exit_if(expr, ...) exit_unless(!(expr), ##__VA_ARGS__)

#endif
