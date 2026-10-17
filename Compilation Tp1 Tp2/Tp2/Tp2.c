#include "Tp2.h"

int main()
{
    Ptr_File_Syn = fopen("Tp2_Input.txt","r");
    System_Goal();
    fclose(Ptr_File_Syn);
    return 0;
}