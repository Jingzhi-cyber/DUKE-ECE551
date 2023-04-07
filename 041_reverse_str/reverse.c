#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getStringSize(char str[]) {
  char * p = str;
  size_t size = 0;
  if (str == NULL) {
    exit(EXIT_FAILURE);
  }
  while (*p != '\0') {
    size++;
    p++;
  }

  return size;
}

void reverse(char * str) {
  size_t size = getStringSize(str);
  if (size != 0) {
    char reverseStr[size + 1];
    for (size_t i = 0; i < size; i++) {
      reverseStr[i] = str[size - i - 1];
    }

    reverseStr[size] = '\0';

    for (size_t i = 0; i < size; i++) {
      str[i] = reverseStr[i];
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}

/*
void reverse(char * str) {
  size_t size = getStringSize(str);
  if (size != 0) {
    if (size % 2 == 0) {
      for (size_t i = 0; i < (size / 2 - 1); i++) {
        char temp = str[size - 1 - i];
        str[size - 1 - i] = str[i];
        str[i] = temp;
      }
    }
    else {
      for (size_t i = 0; i < (size - 1) / 2; i++) {
        char temp = str[size - 1 - i];
        str[size - 1 - i] = str[i];
        str[i] = temp;
      }
    }
  }
}
*/
