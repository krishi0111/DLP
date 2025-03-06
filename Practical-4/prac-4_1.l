%%
[0-9]+[\^][0-9]+ {
    int base, exp;
    sscanf(yytext, "%d^%d", &base, &exp);
    printf("power operation -> %d ** %d = %d\n", base, exp, (int)pow(base, exp));
}

[0-9]+[*][0-9]+ {
    int num1, num2;
    sscanf(yytext, "%d*%d", &num1, &num2);
    printf("You multiply %d with %d then will be : %d\n", num1, num2, num1 * num2);
}

. { /* Ignore other characters */ }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}