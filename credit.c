#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool checkLuhn(long cc, int length)
{
  //Transform the long into an array of digits
  int digits[length];

  for (int i = 0; i < length; i++)
  {
    long divisor = (i == 0) ? 1 : pow(10, i);
    digits[i] = (cc / divisor) % 10;
    int temp = (cc / divisor) % 10;
  }

  //starting with second digit (index 1 since our order is reversed)
  //multiple every other digit by 2
  int multipliedDigits[length / 2];
  int count = 0;
  for (int i = 1; i < length; i += 2)
  {
    multipliedDigits[count] = digits[i] * 2;
    count++;
  }

  //Now add the products' digits together
  int digitsSum = 0;
  for (int i = 0; i < length / 2; i++)
  {
    //values can range between 0 and 18
    digitsSum += ((multipliedDigits[i] / 10) + (multipliedDigits[i] % 10));
  }

  //Also add the unused digits
  for (int i = 0; i < length; i += 2)
  {
    digitsSum += digits[i];
  }

  return (digitsSum % 10 == 0) ? true : false;
}

int main(void)
{
  bool cardValid = false;
  long cardNum = get_long("Number: ");

  //Valid number is 13, 15, and 16 digits long
  //Master card and Visa (16) start with 51, 52, 53, 54, 55, and 4, AMEX starts with 34 or 37
  if (cardNum >= 5100000000000000 && cardNum < 5600000000000000)
  {
    cardValid = checkLuhn(cardNum, 16);
    if (cardValid)
    {
      printf("%s\n", "MASTERCARD");
      return 0;
    }
  }
  else if (cardNum >= 4000000000000000 && cardNum < 5000000000000000)
  {
    cardValid = checkLuhn(cardNum, 16);
    if (cardValid)
    {
      printf("%s\n", "VISA");
      return 0;
    }
  }
  else if (cardNum >= 4000000000000 && cardNum < 5000000000000)
  {
    cardValid = checkLuhn(cardNum, 13);
    if (cardValid)
    {
      printf("%s\n", "VISA");
      return 0;
    }
  }
  else if ((cardNum >= 340000000000000 && cardNum < 350000000000000) || (cardNum >= 370000000000000 && cardNum < 380000000000000))
  {
    cardValid = checkLuhn(cardNum, 15);
    if (cardValid)
    {
      printf("%s\n", "AMEX");
      return 0;
    }
  }

  if (!cardValid)
  {
    printf("%s\n", "INVALID");
    return 0;
  }
}