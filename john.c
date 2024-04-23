#include "john.h"

void __json_val_init(struct json_token *value) {
    value->key[0] = '\0';
    value->type = JSON_NULL;
    value->data.children.count = 0;
}