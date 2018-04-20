//简易版的scanf
int my_scanf(char str[]) {
    int i = 0;
    while ((str[i] = getchar()) == '\n' ? (str[i] = '\0'):1) {
        ++i;
    }
    return i;
}

//简易版的printf
int my_printf(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        putchar(str[i++]);
    }
    return i+1;
}

int main(void) {
    char str[10] = {0};
    my_scanf(str);
    my_printf(str);
    return 0;
}
