#include <stdio.h>
#include "../john.h"

// Helper function to print JSON token details recursively
void print_json_token(json_token *token, int indent_level)
{
    if (token == __JOHN_NULL__)
        return;

    for (int i = 0; i < indent_level; i++)
        printf("  ");

    printf("Key: \"%s\", Type: %d, Children: %d", token->key, token->type, token->data.children.count);
    switch (token->type)
    {
    case JSON_BOOLEAN:
        printf(", Value: %s\n", token->data.boolean_value ? "true" : "false");
        break;
    case JSON_NUMBER:
        printf(", Value: %d\n", token->data.number_value);
        break;
    case JSON_STRING:
        printf(", Value: \"%s\"\n", token->data.string_value);
        break;
    case JSON_OBJECT:
        printf(" {\n");
        for (int i = 0; i < token->data.children.count; i++)
        {
            print_json_token(token->data.children.items[i], indent_level + 1);
        }
        for (int i = 0; i < indent_level; i++)
            printf("  ");
        printf("}\n");
        break;
    default:
        printf("\n");
        break;
    }
}

int main()
{
    const char *json_string = "{\"name\": \"John\", \"age\": 30, \"is_student\": false}";
    john_json my_json;
    john_parse(&my_json, json_string);
    print_json_token(&my_json.root, 0);

    return 0;
}
