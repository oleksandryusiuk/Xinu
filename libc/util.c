/** @file util.h
 * 
 * @brief helpful standart C utilities 
 *
 */
#include "util.h"
#include "../cpu/type.h"

void memory_copy(char *source, char *dest, int nbytes) 
{
    int i;
    for (i = 0; i < nbytes; i++) 
    {
        *(dest + i) = *(source + i);
    }
}

void memory_set(uint8_t *dest, uint8_t val, uint32_t len) 
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) 
{
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do 
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
int strlen(char s[]) 
{
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}
/* K&R */
void reverse(char s[]) 
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) 
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


void backspace(char s[]) 
{
    int len = strlen(s);
    s[len-1] = '\0';
}



void append(char s[], char n) 
{
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void hex_to_ascii(int n, char str[]) 
{
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int tmp;
    int i;
    for (i = 28; i > 0; i -= 4) 
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}


void strcpy(char *dest, char *src)
{
	int idx = 0;
	
	while ( *src != '\0' )
	{
		dest[ idx ] = *src;
		
		src++;
		idx++;
	}
}

int strcmp(char *str1, char *str2)
{
        while ( *str1 != '\0' )
        {
                if ( *str1 != *str2 )
                        return 0;

                str1++;
                str2++;
        }

        if ( *str2 != '\0' )
                return 0;

        return 1;
}





