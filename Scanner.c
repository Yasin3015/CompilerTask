#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length_of_str(char *str);
int compare_str(char *str1,char *str2);
char *substring(char *src_str,int left,int right);
int is_operator(char ch);
int is_delimiter(char ch);
int is_valid_identifier(char *str);
int is_keyword(char *str);
int is_integer(char *str);
int is_real_number(char *str);
int tokenizer(char *str);

int main (void)
{   
   char code[100];
printf("Enter code: ");
fgets(code, sizeof(code), stdin);
tokenizer(code);
}

int length_of_str(char *str)
{
    int i = 0 ;
    while (str[i]!='\0')
        i++;
    return i ;
}

int compare_str(char *str1,char *str2)
{
    if(length_of_str(str1)==length_of_str(str2))
    {
        for(int i = 0 ; i<length_of_str(str1);i++)
        {
            if(str1[i]!=str2[i])
            return 0 ;
        }
        return 1 ;
    }
    return 0 ;
}


char *substring(char *src_str, int left, int right) {
    // calc substring length
    int len = right - left + 1;

    // create memory for substring copy
    char *dest_str = (char *)malloc(sizeof(char) * (len + 1));

    // loop to copy substring into dest_str
    for (int i = left; i <= right && src_str[i] != '\0'; i++) {
        dest_str[i - left] = src_str[i];
    }

    // append null char at end
    dest_str[len] = '\0';

    // return pointer to substring
    return dest_str;
}


int is_operator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || 
       ch == '/' || ch == '>' || ch == '<' || 
       ch == '=' )
       return 1;
    return 0;
}


int is_delimiter(char ch)
{
    if(ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
       ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
       ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
       ch == '[' || ch == ']' || ch == '{' || ch == '}' )
       return 1;
    return 0;
}


int is_valid_identifier(char *str)
{
    if(str[0]=='0' || str[0]=='1' || str[0]=='2' || 
       str[0]=='3' || str[0]=='4'  || str[0]=='5' ||  
       str[0]=='6' || str[0]=='7' || str[0]=='8' || 
       str[0]=='9' || is_delimiter(str[0])==1)
       return 0;
    return 1;   
}

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

// Function to check if a word is a C keyword
int is_keyword(char *str) {
    // Number of keywords in the list
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    // Loop through the list of keywords
    for (int i = 0; i < numKeywords; ++i) {
        // Compare the given word with each keyword
        if (strcmp(str, keywords[i]) == 0) {
            // Return 1 if it's a keyword
            return 1;
        }
    }

    // Return 0 if it's not a keyword
    return 0;
}


int is_integer(char *str)
{
    int len = length_of_str(str);
    if(len==0)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i]!='0' && str[i]!='1' && str[i]!='2' && 
            str[i]!='3' && str[i]!='4' && str[i]!='5' && 
            str[i]!='6' && str[i]!='7' && str[i]!='8' && 
            str[i]!='9' || (str[i]=='-'  && i > 0) )
            return 0;
    }
    return 1 ;
}


int is_real_number(char *str)
{
    int len = length_of_str(str);
    if (len==0)
        return 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i]!='0' && str[i]!='1' && str[i]!='2' && 
            str[i]!='3' && str[i]!='4' && str[i]!='5' && 
            str[i]!='6' && str[i]!='7' && str[i]!='8' && 
            str[i]!='9' && str[i]!='.' || (str[i]=='-'  && i > 0) )
            return 0;
    }
    return 1 ;
}


int tokenizer(char *str)
{
    int left = 0 , right = 0;
    int len = length_of_str(str);

    while(right <= len && left <= len)
    {
        if (is_delimiter(str[right])==0)
            right ++ ;
        if (is_delimiter(str[right])==1 && right == left)
        {
            if(is_operator(str[right]) == 1)
                printf("'%c' is an operator \n",str[right]);
            right++;
            left=right;
        }
        else if(is_delimiter(str[right]) == 1 && left!=right || (right == len && left != right))
        {
            char *substr = substring(str,left,right-1);
            if(is_keyword(substr) == 1)
                printf("'%s' is a keyword \n",substr);
            else if(is_integer(substr)==1)
                printf("'%s' is an integer \n",substr);
            else if(is_real_number(substr)==1)
                printf("'%s' is a real number \n",substr);
            else if(is_valid_identifier(substr)==1 && is_delimiter(str[right-1])==0)
                printf("'%s' is a valid identifier \n",substr);
            left = right;
        }
    }
    return 0;
}
