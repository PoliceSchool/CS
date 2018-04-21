#include <stdio.h>
//简易版的scanf
int my_scanf(char str[]) {
	int i = 0;
	while ((str[i] = getchar()) == '\n' ? (str[i] = '\0') : 1) {
		++i;
	}
	return i;
}

//简易版的printf
int my_printf(char str[]) {
	int i = 0;
	while (str[i] != '\0') {
		putchar(str[i++]);
	}
	return i + 1;
}

//简易版的strlen
int my_strlen(char str[]) {
	if (str == NULL)
		return 0;
	int len = 0;
	while (str[len++] != '\0');
	return len - 1; //不包含最后的'\0'
}

//简易版的strcpy
char* my_strcpy(char to[], char from[]) {
	int i = 0;
	if (to == NULL || from == NULL)
		return 0;
	while ((to[i] = from[i]) != '\0')
		++i;
	return to;
}

//简易版strcmp
int my_strcmp(const char *str1, const char *str2) {
	int ret = 0;
	while (!(ret = *str1 - *str2) && *str2)
		++str1, ++str2;
	return ret;
}

//简易版strcat，不过在vs2015上运行好像有点问题
char* my_strcat(char *str1, char *str2) {
	if (str1 == NULL || str2 == NULL)
		return 0;

	char *address = str1;

	while (*str1 != '\0')
		++str1;
	while (*str2 != '\0')
		*str1++ = *str2++;
	*str1 = '\0';
	return address;
}

char* str_reverse(char str[]) {
	char *p1, *p2, temp;
	p1 = str;
	p2 = str + my_strlen(str) - 1;
	while (p1 < p2) {
		temp = *p2;
		*p2 = *p1;
		*p1 = temp;
		p1++;
		p2--;
	}
	return str;
}

int main(void) {
	char str[15] = { 0 };
	my_scanf(str);
	my_printf(str_reverse(str));
	return 0;
}
