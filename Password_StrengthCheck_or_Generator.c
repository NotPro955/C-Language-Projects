#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Strength_Check(char password[]){
    int i=0;
    int k=0;

    if (strlen(password)>=8)
        i++;
    else
        printf("Enter atleast 8 characters\n");
    
    for(int j =0 ; j < strlen(password); j++)
    {
        if(password[j] >= 'A' && password[j] <='Z'){
            i++;
            k+=1;
            break;}
    }
    
    for(int j =0 ; j < strlen(password); j++)
    {
        if(password[j] >= 'a' && password[j] <='z'){
            i++;
            k+=2;
            break;}
    }
    for(int j =0 ; j < strlen(password); j++)
    {
        if(password[j] >= '0'&& password[j] <='9'){
            i++;
            k+=4;
            break;}
    }
    for(int j =0; j < strlen(password); j++){
        if(!(password[j] >= 'A' && password[j] <='Z')){
            if(!(password[j] >= 'a' && password[j] <='z')){
                if(!(password[j] >= '0' && password[j] <='9')){
                    i++;
                    k+=8;
                    break;
                }
            }
        }
    }
    switch(k){
        case 0: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Special Character\n");break;
        case 1: printf("Password should have atleast 1 Lowercase\n");printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Special Character\n");break;
        case 2: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Special Character\n");break;
        case 3: printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Special Character\n");break;
        case 4: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Lowercase\n");printf("Password should have atleast 1 Special Character\n");break;
        case 5: printf("Password should have atleast 1 Lowercase\n");printf("Password should have atleast 1 Special Character\n");break;
        case 6: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Special Character\n");break;
        case 7: printf("Password should hve atleast 1 Specail Character\n");break;
        case 8: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Digit\n");printf("Password should have atleast 1 Digit\n");break;
        case 9: printf("Password should have atleast 1 Lowercase\n");printf("Password should have atleast 1 Digit\n");break;
        case 10: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Digit\n");break;
        case 11: printf("Password should have atleast 1 Digit\n");break;
        case 12: printf("Password should have atleast 1 Uppercase\n");printf("Password should have atleast 1 Lowercase\n");break;
        case 13: printf("Password should have atleast 1 Lowercase\n");break;
        case 14: printf("Password should have atleast 1 Uppercase\n");break;
        case 15: break;
        default: printf("INVALID INPUT\n");
    }
    switch(i){
        case 1 : printf("Password Strength: \x1b[31mVery Weak\n\x1b[0m");break;
        case 2 : printf("Password Strength: \x1b[38;2;255;165;0mWeak\n\x1b[0m");break;
        case 3 : printf("Password Strength: \x1b[33mModerate\n\x1b[0m");break;
        case 4 : printf("Password Strength: \x1b[32mStrong\n\x1b[0m");break;
        case 5 : printf("Password Strength: \x1b[35mVery Strong\n\x1b[0m");break;
        default : printf("INVALID PASSWORD\n");
    }
}

void Generator(){
    int length;
    printf("Length: ");
    scanf("%d", &length);
    char password[length];
    srand(time(NULL));


    char digits[] = "0123456789";
    int length_digits = strlen(digits);

    char uppercase[] = "ASDFGHJKLQWERTYUIOPZXCVBNM";
    int upper_length = strlen(uppercase);

    char lowercase[] = "asdfghjklqwertyuiopzxcvbnm";
    int lowercase_length = strlen(lowercase);

    char symboles[] = "!@#$^&%*?~()";
    int length_symboles = strlen(symboles);

    for (int i=0; i<length; i++){
        int char_random = rand()%4;
        if(char_random==0)
            password[i] = digits[rand() % length_digits];
        else if(char_random==1)
            password[i] = uppercase[rand() % upper_length];
        else if(char_random==2)
            password[i] = lowercase[rand() % lowercase_length];
        else
            password[i] = symboles[rand() % length_symboles];
    }
    printf("Password: %s\n", password);
    Strength_Check(password);
}

int main(){
    int i;
    char password[100];

    printf("Select from the following:\n");
    printf("    1.Generate a Random Password & Check it's Strength\n");
    printf("    2.Check the Strength of the Password\n");
    printf("\n");
    printf("Enter your option: ");
    scanf("%d", &i);

    if(i == 1)
        Generator();
    else if(i==2){
        printf("Enter your Password: ");
        scanf("%s", &password);
        printf("\n");

        Strength_Check(password);
    }
    else{
        printf("INVALID INPUT\n");
    }
    printf("-----------------------------END-----------------------------");
    return 0;
}