#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s key\n", argv[0]);
    return 1;
  }
  for (int i = 0; i < strlen(argv[1]); i++)
  {
    if (!isdigit(argv[1][i]))
    {
      printf("Usage: %s key\n", argv[0]);
      return 1;
    }
  }
  int key = atoi(argv[1]) % 26;
  string plaintext = get_string("plaintext: ");
  int ptLength = strlen(plaintext);

  printf("ciphertext: ");
  for (int i = 0; i < ptLength; i++)
  {
    if (isalnum(plaintext[i]))
    {
      int ceaseredC = plaintext[i] + key;
      if (ceaseredC > 90 && plaintext[i] <= 90)
      {
        ceaseredC = (ceaseredC % 90) + 64;
      }
      else if (ceaseredC > 122)
      {
        ceaseredC = (ceaseredC % 122) + 96;
      }
      printf("%c", ceaseredC);
    }
    else
    {
      printf("%c", plaintext[i]);
    }
  }
  printf("\n");
}