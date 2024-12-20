#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);

    for (int j = 0; j < n; j++) {
        char str[100];
        printf("Enter a string: ");
        scanf("%s", str);

        int len = strlen(str);

        if (len < 2) {
            printf("Invalid string\n");
            continue;
        }

        int valid = 0;
        for (int i = 0; i < len - 2; i++) {
            if (str[i] == 'a') {
                valid = 1;
                break;
            }
        }

        if (valid && str[len - 1] == 'b' && str[len - 2] == 'b') {
            printf("Valid string\n");
        } else {
            printf("Invalid string\n");
        }
    }

    return 0;
}
