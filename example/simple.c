#include <stdio.h>
#include "../john.h"

int main()
{
    const char *json_data = "{ \"name\": \"John\", \"age\": 30, \"is_student\": true }";
    john_json john;

    // Parse the JSON data
    john_parse(&john, json_data);
    printf("Children: %d\n", john.root.data.children.count);
    return 0;
}