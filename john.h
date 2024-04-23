#ifndef LEAF_JOHN_H
#define LEAF_JOHN_H

#define __JOHN_MAX_KEY_LENGTH__      64
#define __JOHN_MAX_VALUE_LENGTH__    256
#define __JOHN_MAX_CHILDREN__        16

typedef enum {
    __JOHN_FALSE__ = 0,
    __JOHN_TRUE__ = 1
} __JOHN_BOOL__;

typedef double __JOHN_DOUBLE__;

typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_OBJECT,
    JSON_ARRAY
} json_value_type;

struct json_token;

typedef struct {
    struct json_token *items[__JOHN_MAX_CHILDREN__];
    int count;
} json_token_children_t;

struct json_token {
    char key[__JOHN_MAX_KEY_LENGTH__];
    json_value_type type;
    union {
        __JOHN_BOOL__ boolean_value;
        __JOHN_DOUBLE__ number_value;
        char string_value[__JOHN_MAX_VALUE_LENGTH__];
        json_token_children_t children;
    } data;
};

typedef struct {
    struct json_token root;
} john_json_t;

void __json_val_init(struct json_token *value);

#endif // LEAF_JOHN_H
