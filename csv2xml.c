#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

char parsetoken(FILE *input, FILE *output, bool ishead)
{
    assert(input != NULL);
    assert(output != NULL);

    int c;

    fprintf(output, "\t\t<%s>", ishead ? "th" : "td");

    while ((c = fgetc(input)) != EOF) {
        switch (c) {
            case ',':
            case '\n':
                goto end;
            case '\r':
                break;
            default:
                fputc(c, output);
                break;
        }
    }

    end:

    fprintf(output, "</%s>\n", ishead ? "th" : "td");

    return c != EOF ? c : '\0';
}

char parseline(FILE *input, FILE *output, bool ishead)
{
    assert(input != NULL);
    assert(output != NULL);

    fputs("\t<tr>\n", output);

    char c;

    while ((c = parsetoken(input, output, ishead)) != '\0' && c != '\n');

    fputs("\t</tr>\n", output);

    return c;
}

void parsefile(FILE *input, FILE *output)
{
    assert(input != NULL);
    assert(output != NULL);

    fputs("<table>\n", output);

    fputs("<thead>\n", output);

    char c;

    c = parseline(input, output, true);

    fputs("</thead>\n", output);

    if (c == '\0')
        goto end;

    fputs("<tbody>\n", output);

    /* TODO: Take into account whitespacec at end! */

    while (parseline(input, output, false) != '\0');

    fputs("</tbody>\n", output);

    end:

    fputs("</table>\n", output);
}

int main(void)
{
    parsefile(stdin, stdout);

    // FILE *input = fopen("data\\GlobalTemperatures.csv", "rb");
    // assert(input != NULL);

    // FILE *output = fopen64("test.xml", "wb");
    // assert(output != NULL);

    // parsefile(input, output);

    // fclose(output);
    // fclose(input);
    
    return 0;
}
