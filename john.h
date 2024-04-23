#ifndef JOHN_H
#define JOHN_H

#include <stdio.h>

#define __JOHN_MAX_KEY_LENGTH__ 64
#define __JOHN_MAX_VALUE_LENGTH__ 256
#define __JOHN_MAX_CHILDREN__ 16

typedef enum
{
    __JOHN_FALSE__ = 0,
    __JOHN_TRUE__ = 1
} __JOHN_BOOL__;

typedef int __JOHN_INT__;
#define __JOHN_NULL__ ((void *)0)

typedef enum
{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_OBJECT,
    JSON_ARRAY
} json_value_type;

typedef struct json_token json_token;

typedef struct
{
    json_token *items[__JOHN_MAX_CHILDREN__];
    int count;
} json_token_children_t;

struct json_token
{
    char key[__JOHN_MAX_KEY_LENGTH__];
    json_value_type type;
    union
    {
        __JOHN_BOOL__ boolean_value;
        __JOHN_INT__ number_value;
        char string_value[__JOHN_MAX_VALUE_LENGTH__];
        json_token_children_t children;
    } data;
};

typedef struct
{
    json_token root;
} john_json;

void john_parse(john_json *john, const char *data);

#endif // JOHN_H
