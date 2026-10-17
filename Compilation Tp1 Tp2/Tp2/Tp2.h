#include "../Tp1/Tp1.h"

void Expression(void);
void Match_Next_Token(Token);
Token Next_Token(FILE *);
void Instructs_List(void);
void Instuct();
void Program(void);
void prim(void);
void Unget_Token(Token);
void Add_Opp(void);
int Depasse_Space_EndOfLine(FILE *);
void Expr_List();

void Syntax_Error(Token errorToken)
{
    printf("Syntax Error Token Not Founded : %s \n", Token_Type_String[(int) errorToken]);
}

void System_Goal(void)
{ 
    Program();
    Match_Next_Token(SCANEOF);
}

void Program(void)
{
    Match_Next_Token(BEGIN);
    Instructs_List();
    Match_Next_Token(END);
}

void Instructs_List()
{
    Instuct();
    while(true)
    {
        Token CurretToken = Next_Token(Ptr_File_Syn);
        Unget_Token(CurretToken);
        switch(CurretToken)
        {
            /***
            
            */
            case ID:
            case READ:
            case WRITE:
                Instuct();
                break;
            default:
                return;
        }
    }
}

void Instuct()
{

    Token tok = Next_Token(Ptr_File_Syn);
    Unget_Token(tok);
    switch(tok)
    {
        case ID:
            Match_Next_Token(ID);
            Match_Next_Token(ASSIGNOP);
            Expression();
            Match_Next_Token(SEMICOLON);
            break;

        case WRITE:
            Match_Next_Token(WRITE);
            Match_Next_Token(LPAREN);
            Expr_List();
            Match_Next_Token(RPAREN);
            Match_Next_Token(SEMICOLON);
            break;

        default:
            Syntax_Error(tok);
            break;
    }
}

void Ids_List()
{
    
    Match_Next_Token(ID);
    Token monToken ;
    while( ( monToken = Next_Token(Ptr_File_Syn) ) == COMMA)
    {
        Unget_Token(COMMA);
        Match_Next_Token(COMMA);
        Match_Next_Token(ID);
    }
    Unget_Token(monToken);
}

void Expression(void)
{
    
    prim();
    Token monToken;
    for(monToken = Next_Token(Ptr_File_Syn) ; monToken == PLUSOP 
                    || monToken == MINUSOP ; monToken = Next_Token(Ptr_File_Syn))
    {
        Unget_Token(monToken);
        Add_Opp();
        prim();
    }
    Unget_Token(monToken);
    
}

void Expr_List(void)
{
    
    Expression();
    Token CurrentToken;
    while( ( CurrentToken = Next_Token(Ptr_File_Syn) ) == COMMA)
    {
        Unget_Token(CurrentToken);
        Match_Next_Token(COMMA);
        Expression();
    }
    Unget_Token(CurrentToken);
}

void Add_Opp( )
{
    
    Token monToken = Next_Token(Ptr_File_Syn);
    Unget_Token(monToken);
    if(monToken == PLUSOP || monToken == MINUSOP)
        Match_Next_Token(monToken);
    else 
        Syntax_Error(monToken);
}

void prim()
{
    
    Token tok = Next_Token(Ptr_File_Syn);
    Unget_Token(tok);
    switch(tok)
    {
        case LPAREN:
            Match_Next_Token(LPAREN);
            Expression();
            Match_Next_Token(RPAREN);
            break;
        case ID:
            Match_Next_Token(ID);
            break;
        case INTLITERAL:
            Match_Next_Token(INTLITERAL);
            break;
        case REALLITERAL:
            Match_Next_Token(REALLITERAL);
            break;
        default:
            Syntax_Error(tok);
            break;
    }
}

void Match_Next_Token(Token monToken)
{
    
    Token currentToken = Next_Token(Ptr_File_Syn);
    if(monToken != currentToken)
        Syntax_Error(monToken);
}


int Depasse_Space_EndOfLine(FILE *Ptr_File_Syn)
{
    if( !Ptr_File_Syn )  exit(0);
    int CurrentChar ;
    while(( CurrentChar = fgetc(Ptr_File_Syn) ) == ' ' || (CurrentChar == '\n'));
    return CurrentChar;
}

Token Next_Token(FILE *Ptr_File_Syntaxique)
{
    
    if(!Ptr_File_Syntaxique) exit(0);

    int monChar;

    Clear_Buffer();

    while((monChar = fgetc(Ptr_File_Syntaxique)) != ' ' && monChar != EOF)
    {
        if(monChar == '\n')
            continue;
        Stock_Car_In_Buffer((char)monChar);
    }
    
    int monCntr = 0;
    for(; monCntr <= 15 ; monCntr++)
        if(!strcmp(Token_Buffer,Token_Type_String[monCntr]))
            break;
    return (Token) monCntr;
}


void Unget_Token(Token MonToken)
{
    switch (MonToken)
    {
            case BEGIN :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('G', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('B', Ptr_File_Syn);
                    break;

            case END :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('D', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    break;

            case ID :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('D', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    break;

            case WRITE :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('T', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    ungetc('W', Ptr_File_Syn);
                    break;

            case READ :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('D', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    break;

            case MINUSOP :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    ungetc('U', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('M', Ptr_File_Syn);
                    break;

            case ASSIGNOP :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('G', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    break;

            case PLUSOP :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    ungetc('U', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    break;

            case COMMA :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('M', Ptr_File_Syn);
                    ungetc('M', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('C', Ptr_File_Syn);
                    break;

            case SEMICOLON :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('C', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('M', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    break;

            case RPAREN :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    break;

            case LPAREN :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('P', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    break;
            case INTLITERAL :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('T', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('T', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    break;
            case REALLITERAL :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('T', Ptr_File_Syn);
                    ungetc('I', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('L', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('R', Ptr_File_Syn);
                    break;
            
            default :
                    ungetc(' ', Ptr_File_Syn);
                    ungetc('F', Ptr_File_Syn);
                    ungetc('O', Ptr_File_Syn);
                    ungetc('E', Ptr_File_Syn);
                    ungetc('N', Ptr_File_Syn);
                    ungetc('A', Ptr_File_Syn);
                    ungetc('C', Ptr_File_Syn);
                    ungetc('S', Ptr_File_Syn);
                    break;
        }
}
