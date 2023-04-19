#include "shell.h"

/**
 * check_interactive - checks if shell is in interactive mode
 * @input_fd: file descriptor of input
 *
 * Return: true if shell is in interactive mode, false otherwise
 */
bool check_interactive(int input_fd)
{
    return isatty(input_fd) && input_fd <= 2;
}

/**
 * is_delimiter - checks if character is a delimiter
 * @c: the character to check
 * @delimiters: string of delimiters
 *
 * Return: true if the character is a delimiter, false otherwise
 */
bool is_delimiter(char c, const char *delimiters)
{
    while (*delimiters != '\0') {
        if (*delimiters == c) {
            return true;
        }
        delimiters++;
    }
    return false;
}

/**
 * is_alpha - checks if character is an alphabet
 * @c: the character to check
 *
 * Return: true if the character is an alphabet, false otherwise
 */
bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/**
 * string_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the converted integer or 0 if the string contains no numbers
 */
int string_to_int(const char *s)
{
    int sign = 1;
    unsigned int result = 0;
    bool digit_found = false;

    while (*s != '\0') {
        if (*s == '-') {
            sign = -1;
        } else if (isdigit(*s)) {
            digit_found = true;
            result *= 10;
            result += (*s - '0');
        } else if (digit_found) {
            break;
        }
        s++;
    }

    return sign * result;
}
