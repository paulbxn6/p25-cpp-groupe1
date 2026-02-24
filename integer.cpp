#include "integer.h" // " " car le fichier est à nous et non à C
#include "foo.h"

int main()
{
    Int i;
    foo(i);
    i.incr();
    return 0;
}