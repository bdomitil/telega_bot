#include <stdio.h>
#include <stdlib.h>

int main()
{
 int res = system("bash add_user.sh");
 printf ("result = %d\n", res);
}