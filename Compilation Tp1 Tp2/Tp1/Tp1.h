#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

FILE *Ptr_File_Syn = NULL;
FILE *Ptr_File_Lyx = NULL;


bool Its_Reel = false;

int Numbre_Of_Lignes = 1;

typedef enum Token_Type
{
        SCANEOF, 
        INTLITERAL,
        LPAREN,
        RPAREN,
        SEMICOLON,
        COMMA,
        PLUSOP,
        ASSIGNOP,
        MINUSOP,
        BEGIN,
        END,
        ID,
        WRITE,
        READ,
        REALLITERAL,
        LEXICAL_ERROR
} Token;

char *Token_Type_String[50] = 
{   "SCANEOF", 
    "INTLITERAL", 
    "LPAREN", 
    "RPAREN",
    "SEMICOLON",
    "COMMA",
    "PLUSOP",
    "ASSIGNOP",
    "MINUSOP",
    "BEGIN",
    "END",
    "ID",
    "WRITE",
    "READ",
    "REALLITERAL",
    "LEXICAL_ERROR"
};

char Token_Buffer[100];

int Buffer_Size()
{
    int CntrI = 0, CntrLenght = 0;
    while (Token_Buffer[CntrI++] != '\0')
        CntrLenght++;
    return CntrLenght;
}


void Clear_Buffer(void)
{
        for(int i = 0; i < 100; i++)
                Token_Buffer[i] = '\0';
}

int eof(FILE *Ptr_File)
{
        char c;
        if( (c = fgetc(Ptr_File)) == EOF) return 1;
        ungetc(c,Ptr_File);
        return 0;
}

Token Check_Reserved_Token()
{
        if(!strcmp(Token_Buffer,"BEGIN")) return BEGIN;
        if(!strcmp(Token_Buffer,"READ")) return READ;
        if(!strcmp(Token_Buffer,"WRITE")) return WRITE;
        if(!strcmp(Token_Buffer,"END")) return END;
        return ID;
}

/**
 *                      Store Car After Car In A Table
 */
void Stock_Car_In_Buffer(char car)
{
        int i;
        for(i = 0; i<100 ; i++)
                if(Token_Buffer[i] == '\0') break;
        Token_Buffer[i] = car;
}

/**
 *                      Display Lexical Error
 */
void Lexical_Error_Message(char Car_Of_Error)
{
        printf("\nError Dans La Ligne %d Sur Lettre %c !!", Numbre_Of_Lignes, Car_Of_Error);
}

void Passed_The_Current_Instruct(FILE *Ptr_File)
{
        char Car_Error ;
        Car_Error = fgetc(Ptr_File);
        while( Car_Error != '\n' && Car_Error != ';') Car_Error = fgetc(Ptr_File);
        if(Car_Error != ';')
                ungetc(Car_Error,Ptr_File);
}

/**
 *                      Returned Next Token
 */

Token Scanner_Of_File(FILE *Ptr_File)
{
        int in_char, c;

        Clear_Buffer();

        if(eof(Ptr_File)) return SCANEOF;

        while (((in_char = fgetc(Ptr_File)) != EOF))
        {
                if(isspace(in_char))
                {
                        if(in_char == '\n')
                        {
                                fprintf(Ptr_File_Syn,"\n");
                                Numbre_Of_Lignes++;
                        }
                        continue;
                }
                else if(isalpha(in_char))
                {
                        Stock_Car_In_Buffer(in_char);

                        for( c = fgetc(Ptr_File) ; isalnum(c) || c == '_'; c = fgetc(Ptr_File) )
                                Stock_Car_In_Buffer(c);

                        ungetc(c,Ptr_File);
                        return Check_Reserved_Token();
                }
                else if(isdigit(in_char) || in_char == '.')
                {
                        Stock_Car_In_Buffer(in_char);
                        
                        if(in_char == '.') Its_Reel = true;

                        for( c = fgetc(Ptr_File) ; isdigit(c) || c == '.' || c == 'e' || c == 'E'; c = fgetc(Ptr_File))
                        {
                                if(c == '.' || Its_Reel == true)
                                {
                                        if(Its_Reel == true) Its_Reel = false;

                                        Stock_Car_In_Buffer(c);

                                        for(c = fgetc(Ptr_File); isdigit(c) || c == 'e' || c == 'E'; c = fgetc(Ptr_File))
                                        {
                                                if( c == 'e' || c == 'E')
                                                {
                                                        Stock_Car_In_Buffer(c);
                                                        c = fgetc(Ptr_File); // + Or -
                                                        if(isdigit(c) || c == '+' || c == '-')
                                                        {
                                                                Stock_Car_In_Buffer(c);

                                                                if(c == '+' || c == '-')
                                                                {
                                                                        c = fgetc(Ptr_File);
                                                                        if( ! isdigit(c))
                                                                        {
                                                                                Lexical_Error_Message(c);
                                                                                Passed_The_Current_Instruct(Ptr_File);
                                                                                return LEXICAL_ERROR;
                                                                        }
                                                                        else Stock_Car_In_Buffer(c);
                                                                }
                                                                


                                                                for(c = fgetc(Ptr_File); isdigit(c); c = fgetc(Ptr_File))
                                                                        Stock_Car_In_Buffer(c);

                                                                ungetc(c,Ptr_File);
                                                                return REALLITERAL;
                                                        }
                                                        else /// Error rien apres e Or E
                                                        {
                                                                Lexical_Error_Message(c);
                                                                Passed_The_Current_Instruct(Ptr_File);
                                                                return LEXICAL_ERROR;
                                                        }
                                                }
                                                else 
                                                        Stock_Car_In_Buffer(c);
                                        }
                                        ungetc(c,Ptr_File);
                                        return REALLITERAL;

                                        
                                }
                                else if(c == 'e' || c == 'E')
                                {
                                        Stock_Car_In_Buffer(c);
                                        c = fgetc(Ptr_File); // + Or -
                                        if(isdigit(c) || c == '+' || c == '-')
                                        {
                                                Stock_Car_In_Buffer(c);

                                                if(c == '+' || c == '-')
                                                {
                                                        c = fgetc(Ptr_File);
                                                        if( ! isdigit(c))
                                                        {
                                                                Lexical_Error_Message(c);
                                                                Passed_The_Current_Instruct(Ptr_File);
                                                                return LEXICAL_ERROR;
                                                        }
                                                        else Stock_Car_In_Buffer(c);
                                                }                                                                

                                                for(c = fgetc(Ptr_File); isdigit(c); c = fgetc(Ptr_File))
                                                        Stock_Car_In_Buffer(c);
                                                ungetc(c,Ptr_File);
                                                return REALLITERAL;
                                        }
                                        else /// Error rien apres e Or E
                                        {
                                                Lexical_Error_Message(c);
                                                Passed_The_Current_Instruct(Ptr_File);
                                                return LEXICAL_ERROR;
                                        }
                                }
                                else 
                                        Stock_Car_In_Buffer(c);
                        }
                        
                        ungetc(c,Ptr_File);
                        return INTLITERAL;
                }
                else if(in_char == '(')
                        return LPAREN;
                else if(in_char == ')')
                        return RPAREN;
                else if(in_char == ';')
                        return SEMICOLON;
                else if(in_char == ',')
                        return COMMA;
                else if(in_char == '+')
                        return PLUSOP;
                else if(in_char == ':')
                {
                        c=fgetc(Ptr_File);
                        if(c == '=') return ASSIGNOP;
                        else
                        {
                                Lexical_Error_Message(in_char);
                                Passed_The_Current_Instruct(Ptr_File);
                                return LEXICAL_ERROR;
                        }
                }
                else if(in_char == '-')
                {
                        c=fgetc(Ptr_File);
                        if(c == '-')
                        {
                                do in_char = fgetc(Ptr_File);
                                while(in_char != '\n');
                                Numbre_Of_Lignes
                        ++;
                        }
                        else
                        {
                                ungetc(c,Ptr_File);
                                return MINUSOP;
                        }
                }
                else
                {
                        Lexical_Error_Message(in_char);
                        Passed_The_Current_Instruct(Ptr_File);
                        return LEXICAL_ERROR;
                }
        }
}