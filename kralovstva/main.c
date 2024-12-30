
#include "kralovstvo.h"


int main() {
    kralovstvo k;
    kralovstvoINIT(&k);
    vypisInfoKralovstvo(&k);
    kralovstvoDestroy(&k);
    return 0;
}