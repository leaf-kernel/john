#include <stdio.h>
#include "../john.h"

// Helper function to print JSON token details recursively
void print_json_token(json_token *token, int indent_level)
{
    if (token == __JOHN_NULL__)
        return;

    for (int i = 0; i < indent_level; i++)
        printf("  ");

    printf("Key: \"%s\", Type: %d", token->key, token->type);
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
        printf("\n");
        for (int i = 0; i < token->data.children.count; i++)
        {
            print_json_token(token->data.children.items[i], indent_level + 1);
        }
        break;
    case JSON_ARRAY:
        printf("\n");
        for (int i = 0; i < token->data.children.count; i++)
        {
            print_json_token(token->data.children.items[i], indent_level + 1);
        }
        break;
    default:
        printf("\n");
        break;
    }
}

int main()
{
    const char *json_string = "{\"name\": \"John Doe\", \"age\": 30, \"is_student\": false, \"grades\": [95, 85, 90], \"address\": {\"street\": \"123 Main St\", \"city\": \"Anytown\", \"zipcode\": \"12345\"}, \"contacts\": [{\"name\": \"Alice\", \"phone\": \"555-1234\"}, {\"name\": \"Bob\", \"phone\": \"555-5678\"}]}";

    john_json my_json;
    john_parse(&my_json, json_string); // Parse the JSON string into tokens
    printf("JSON Token Tree:\n");
    print_json_token(&my_json.root, 0); // Print the root token recursively

    return 0;
}
