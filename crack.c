#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s hash\n", argv[0]);
    return 1;
  }

  // get hash to compare
  string hashToCompare = argv[1];
  // Get the Salt from the hash
  char salt[5];
  salt[0] = hashToCompare[0];
  salt[1] = hashToCompare[1];

  // Declare a string of char that can store our test values
  char testPass[8];

  // generate string A -> zzzzz and hash them with the salt and compare to input hash
  // A = 65 & Z = 90, a = 97 & z = 122
  for (int fifth = -1; fifth < 52; fifth++)
  {
    for (int fourth = -1; fourth < 52; fourth++)
    {
      for (int third = -1; third < 52; third++)
      {
        for (int second = -1; second < 52; second++)
        {
          for (int first = 0; first < 52; first++)
          {
            //get first character (there is always a first one!)
            if (first < 26)
            {
              testPass[0] = first + 65;
            }
            else
            {
              testPass[0] = first + 71;
            }

            if (second == -1)
            {
            } //do nothing!
            else if (second < 26)
            {
              testPass[1] = second + 65;
            }
            else
            {
              testPass[1] = second + 71;
            }

            if (third == -1)
            {
            } //do nothing!
            else if (third < 26)
            {
              testPass[2] = third + 65;
            }
            else
            {
              testPass[2] = third + 71;
            }

            if (fourth == -1)
            {
            } //do nothing!
            else if (fourth < 26)
            {
              testPass[3] = fourth + 65;
            }
            else
            {
              testPass[3] = fourth + 71;
            }

            if (fifth == -1)
            {
            } //do nothing!
            else if (fifth < 26)
            {
              testPass[4] = fifth + 65;
            }
            else
            {
              testPass[4] = fifth + 71;
            }

            // hash the string
            string hashToTest = crypt(testPass, salt);

            if (0 == strncmp(hashToTest, hashToCompare, 5))
            {
              printf("%s\n", testPass);
              return 0;
            }
          }
        }
      }
    }
  }

  printf("FAILED\n");
  return 1;
}