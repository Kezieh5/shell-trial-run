#include "shell.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @l: size of line
 * @m: size of buffer
 */
void bring_line(char **lineptr, size_t *l, char *buffer, size_t m)
{
    if (*lineptr == NULL) {
        if (m > BUFSIZE) {
            *l = m;
        } else {
            *l = BUFSIZE;
        }
        *lineptr = buffer;
    } else if (*l < m) {
        if (m > BUFSIZE) {
            *l = m;
        } else {
            *l = BUFSIZE;
        }
        *lineptr = realloc(*lineptr, *l);
        if (*lineptr == NULL) {
            free(buffer);
            return;
        }
        strcpy(*lineptr, buffer);
        free(buffer);
    } else {
        strcpy(*lineptr, buffer);
        free(buffer);
    }
}
/**
 * get_line - Read input from stream
 * @lineptr: buffer that stores the input
 * @l: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t _getline(char **lineptr, size_t *l, FILE *stream)
{
    static ssize_t input;
    ssize_t ret;
    char c = 'x', *buffer;
    int o;

    if (input == 0)
        fflush(stream);
    else
        return (-1);
    input = 0;

    buffer = malloc(sizeof(char) * 1024);
    if (!buffer)
        return (-1);

    while (c != '\n')
    {
        o = read(STDIN_FILENO, &c, 1);
        if (o == -1 || (o == 0 && input == 0))
        {
            free(buffer);
            return (-1);
        }
        if (o == 0 && input != 0)
        {
            input++;
            break;
        }

        if (input >= 1024)
            buffer = _realloc(buffer, input, input + 1);

        buffer[input] = c;
        input++;
    }
    buffer[input] = '\0';

    if (*lineptr == NULL || *l < input)
    {
        *l = input;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }

    ret = input;
    if (o != 0)
        input = 0;
    return (ret);
}
