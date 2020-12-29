#include <stdio.h>
#define efficient_isupper(c) (c >= 'A' && c <= 'Z')

/* two implementations:
Macro: saves time but takes more space because the preprocessor has
to carry out the expansions
Function: saves space but takes longer because of the overhead
of calling a function
*/

char efficientisupper(char c){
    return (c >= 'A' && c <= 'Z');
}
