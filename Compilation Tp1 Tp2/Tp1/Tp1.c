#include "Tp1.h"



int main()
{

        Ptr_File_Lyx = fopen("Tp1_Input.txt","r");
        Ptr_File_Syn = fopen("../Tp2/Tp2_Input.txt","w");

        Token mot ;

        while((mot = Scanner_Of_File(Ptr_File_Lyx)) != SCANEOF)
                switch (mot)
                {
                        case BEGIN :
                                fprintf(Ptr_File_Syn,"BEGIN ");
                                break;
                        case END :
                                fprintf(Ptr_File_Syn, "END ");
                                break;
                        case ID :
                                fprintf(Ptr_File_Syn, "ID ");
                                break;
                        case WRITE :
                                fprintf(Ptr_File_Syn, "WRITE ");
                                break;
                        case READ :
                                fprintf(Ptr_File_Syn, "READ ");
                                break;
                        case MINUSOP :
                                fprintf(Ptr_File_Syn, "MINUSOP ");
                                break;

                        case ASSIGNOP :
                                fprintf(Ptr_File_Syn, "ASSIGNOP ");
                                break;
                        
                        case PLUSOP :
                                fprintf(Ptr_File_Syn, "PLUSOP ");
                                break;

                        case COMMA :
                                fprintf(Ptr_File_Syn, "COMMA ");
                                break;

                        case SEMICOLON :
                                fprintf(Ptr_File_Syn, "SEMICOLON ");
                                break;

                        case RPAREN :
                                fprintf(Ptr_File_Syn, "RPAREN ");
                                break;

                        case LPAREN :
                                fprintf(Ptr_File_Syn, "LPAREN ");
                                break;

                        case INTLITERAL :
                                fprintf(Ptr_File_Syn, "INTLITERAL ");
                                break;

                        case SCANEOF :
                                fprintf(Ptr_File_Syn, "SCANEOF ");
                                break;

                        case REALLITERAL :
                                fprintf(Ptr_File_Syn, "REALLITERAL ");
                                break;

                        case LEXICAL_ERROR :
                                fprintf(Ptr_File_Syn, "LEXICAL_ERROR");
                                break;
                }

        fprintf(Ptr_File_Syn,"SCANEOF");
        fclose(Ptr_File_Lyx);
        fclose(Ptr_File_Syn);

        return 0;
}