#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int height;

  do
  {
    height = get_int("Height:");
  } while (height < 1 || height > 8);

  // Print the pyramid out to the console
  int count = 0;

  while (count < height)
  {
    count++;
    // Spaces before the blocks
    for (int spaces = 0; spaces < height - count; spaces++)
    {
      printf(" ");
    }
    // Hashes for the blocks on the left
    for (int leftBlocks = 0; leftBlocks < count; leftBlocks++)
    {
      printf("#");
    }
    // The space between
    printf("  ");
    // Hashes for the blocks on the right
    for (int rightBlocks = 0; rightBlocks < count; rightBlocks++)
    {
      printf("#");
    }
    printf("\n");
  }
}
