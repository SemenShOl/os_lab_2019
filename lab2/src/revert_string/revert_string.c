#include <stdlib.h>
#include <string.h>
void RevertString(char *str)
{
	int n = strlen(str);

	// начинаем менять местами символы с обоих концов строки
	for (int i = 0, j = n - 1; i < j; i++, j--)
	{
		char ch = str[i];
		str[i] = str[j];
		str[j] = ch;
	}
}



