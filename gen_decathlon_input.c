#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rxvm.h"

char *set_regex =
"(([A-Za-z\\-]{4,50}|erik)[ \t]+(100m|110m|400m|1500m|"
"discus|javelin|shot|long|high|pole)[ \t]+[1-3][0-9]{1,3}(\\.[0-9]+)"
"?[ \t]*\n+){25,1000}#[ \t]*\n+";

int parse_int (char *input)
{
    int ret;

    ret = 0;
    while (*input) {
        if (*input < '0' || *input > '9')
            return -1;
        ret = (ret * 10) + (*input - '0');
        ++input;
    }

    return ret;
}

void rxvm_print_err (int err)
{
    const char *msg;

    switch (err) {
        case RXVM_BADOP:
            msg = "Operator used incorrectly";
        break;
        case RXVM_BADCLASS:
            msg = "Unexpected character class closing character";
        break;
        case RXVM_BADREP:
            msg = "Unexpected closing repetition character";
        break;
        case RXVM_BADPAREN:
            msg = "Unexpected parenthesis group closing character";
        break;
        case RXVM_EPAREN:
            msg = "Unterminated parenthesis group";
        break;
        case RXVM_ECLASS:
            msg = "Unterminated character class";
        break;
        case RXVM_EREP:
            msg = "Missing repetition closing character";
        break;
        case RXVM_MREP:
            msg = "Empty repetition";
        break;
        case RXVM_ETRAIL:
            msg = "Trailing escape character";
        break;
        case RXVM_EMEM:
            msg = "Failed to allocate memory";
        break;
        case RXVM_EINVAL:
            msg = "Invalid symbol";
        break;
        default:
            msg = "Unrecognised error code";
    }

    printf("Error %d: %s\n", err, msg);
}

int main (int argc, char *argv[])
{
    char *gen;
    int ret;
    rxvm_t compiled;
    int num;
    int i;

    if (argc != 2) {
        printf("Usage: %s <no. of sets>\n", argv[0]);
        exit(1);
    }

    num = parse_int(argv[1]);
    srand(time(NULL));

    /* Compile the expression */
    if ((ret = rxvm_compile(&compiled, set_regex)) < 0) {
        rxvm_print_err(ret);
        exit(ret);
    }

    for (i = 0; i < num; ++i) {
        gen = rxvm_gen(&compiled, NULL);
        printf("%s\n", gen);
        free(gen);
    }

    printf("##\n");
    rxvm_free(&compiled);
    return ret;
}

