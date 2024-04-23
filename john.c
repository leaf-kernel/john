#include "john.h"

static void __json_val_init(json_token *value)
{
    if (value != __JOHN_NULL__)
    {
        value->key[0] = '\0';
        value->type = JSON_NULL;
        value->data.boolean_value = __JOHN_FALSE__;
        value->data.number_value = 0;
        value->data.string_value[0] = '\0';
        value->data.children.count = 0;
    }
}

int __john_strcmp(const char *str1, const char *str2)
{
    if (str1 == __JOHN_NULL__ || str2 == __JOHN_NULL__)
        return -1;

    while (*str1 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

__JOHN_INT__ __john_atoi(const char *str)
{
    if (str == __JOHN_NULL__)
        return 0;

    __JOHN_INT__ num_value = 0;
    while (*str != '\0')
    {
        num_value = num_value * 10 + (*str - '0');
        str++;
    }
    return num_value;
}

void __json_add_child(json_token *parent, json_token *child)
{
    if (parent == __JOHN_NULL__ || child == __JOHN_NULL__ || parent->data.children.count >= __JOHN_MAX_CHILDREN__)
    {
        return;
    }

    // Check if there's space in the children array
    if (parent->data.children.count < __JOHN_MAX_CHILDREN__)
    {
        // Assign the new child directly to the next available slot in the array
        parent->data.children.items[parent->data.children.count] = child;
        parent->data.children.count++;
    }
}

void john_parse(john_json *john, const char *data)
{
    if (john == __JOHN_NULL__ || data == __JOHN_NULL__)
        return;

    typedef enum
    {
        PARSE_START,
        IN_OBJECT,
        IN_NAME,
        AFTER_NAME,
        IN_VALUE,
        AFTER_VALUE,
        IN_NUMBER_OR_BOOLEAN
    } __parse_state_t;

    __parse_state_t state = PARSE_START;
    __JOHN_BOOL__ in_quotes = __JOHN_FALSE__;
    int name_index = 0;
    json_token *current_token = &john->root;

    while (*data != '\0')
    {
        switch (state)
        {
        case PARSE_START:
            if (*data == '{')
            {
                state = IN_OBJECT;
            }
            break;

        case IN_OBJECT:
            if (*data == '"')
            {
                current_token->type = JSON_OBJECT;
                state = IN_NAME;
                in_quotes = __JOHN_TRUE__;
                name_index = 0;
            }
            else if (*data == '}')
            {
                return;
            }
            break;

        case IN_NAME:
            if (*data == '"' && in_quotes)
            {
                current_token->key[name_index] = '\0';
                state = AFTER_NAME;
                in_quotes = __JOHN_FALSE__;
            }
            else if (in_quotes)
            {
                current_token->key[name_index++] = *data;
            }
            break;

        case AFTER_NAME:
            if (*data == ':')
            {
                state = IN_VALUE;
            }
            break;

        case IN_VALUE:
            if (*data == '"')
            {
                if (!in_quotes)
                {
                    in_quotes = __JOHN_TRUE__;
                }
                else
                {
                    current_token->data.string_value[name_index] = '\0';
                    current_token->type = JSON_STRING;
                    state = AFTER_VALUE;
                }
            }
            else if (*data == 't' || *data == 'f' || (*data >= '0' && *data <= '9'))
            {
                name_index = 0;
                current_token->data.string_value[name_index++] = *data;
                state = IN_NUMBER_OR_BOOLEAN;
            }
            break;

        case AFTER_VALUE:
            if (*data == ',' || *data == '}')
            {
                if (current_token->type != JSON_OBJECT)
                {
                    json_token new_token;
                    __json_val_init(&new_token);

                    if (current_token->type == JSON_NULL)
                    {
                        current_token->type = JSON_OBJECT;
                    }
                    else
                    {
                        __json_add_child(current_token, &new_token);
                        current_token = &new_token;
                    }
                }

                state = (*data == '}') ? PARSE_START : IN_OBJECT;
            }
            break;

        case IN_NUMBER_OR_BOOLEAN:
            if (*data == ',' || *data == '}')
            {
                current_token->data.string_value[name_index] = '\0';
                if (__john_strcmp(current_token->data.string_value, "true") == 0)
                {
                    current_token->data.boolean_value = __JOHN_TRUE__;
                    current_token->type = JSON_BOOLEAN;
                }
                else if (__john_strcmp(current_token->data.string_value, "false") == 0)
                {
                    current_token->data.boolean_value = __JOHN_FALSE__;
                    current_token->type = JSON_BOOLEAN;
                }
                else
                {
                    current_token->data.number_value = __john_atoi(current_token->data.string_value);
                    current_token->type = JSON_NUMBER;
                }
                state = (*data == '}') ? PARSE_START : IN_OBJECT;
            }
            else
            {
                current_token->data.string_value[name_index++] = *data;
            }
            break;
        }
        data++;
    }
}
