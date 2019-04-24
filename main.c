#include <stdio.h>
#include <ctype.h>
#include <string.h>

char get_alpha(int n) {
    if (n < 0 || n >= 26) {
        return -1;
    }

    return 'a' + n;
}

int get_index(char n) {
    if (n < 'a' || n > 'z') {
        return -1;
    }

    return n - 'a';
}

int encrypt(char *message, const char *key) {
    int k, m;
    for (int i = 0; message[i] != '\0'; ++i) {
        m = get_index(tolower(message[i]));
        k = get_index(tolower(key[i]));

        message[i] = get_alpha((k + m) % 26);
    }
    
    return 0;
}

int decrypt(char *message, const char *key) {
    const int message_len = strlen(message);

    int d;
    for (int i = 0; message[i] != '\0'; ++i) {
        d = tolower(message[i]) - tolower(key[i % message_len]);
        message[i] = get_alpha((d < 0) ? (26 + d) : (d % 26));
    }

    return 0;
}

float matches(char *message1, char *message2) {
    int matches_count = 0;
    for (int i = 0; message1[i] != '\0'; ++i) {
        if (message1[i] == message2[i]) {
            ++matches_count;
        }
    }

    return matches_count * 100. / strlen(message1);
}

int main() {
    char g1[] = "ksvlszksxqylrcl";
    char g2[] = "zpyaitqhtelgtnl";

    char c1[] = "EsperanzaHarvey";
    char c2[] = "ChristynComeaux";
    char c3[] = "EsperanzaHarvey";

    encrypt(c1, g1);
    encrypt(c2, g2);
    encrypt(c3, g2);

    printf("c1\t= '%s'\n", c1);
    printf("c2\t= '%s'\n", c2);
    printf("c3\t= '%s'\n", c3);

    float p1 = matches(c1, c2);
    float p3 = matches(c1, c3);

    printf("p1\t= %f\n", p1);
    printf("p3\t= %f\n", p3);

    decrypt(c1, g1);
    decrypt(c2, g2);
    decrypt(c3, g2);

    printf("m1\t= '%s'\n", c1);
    printf("m2\t= '%s'\n", c2);

    return 0;
}
