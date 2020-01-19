#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char reflector[]="YRUHQSLDPXNGOKMIEBFZCWVJAT"; 
char rotor_table[5][27] = 
{
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK"
};
char step_char[6]="RFWKA"; // Royal Flags Wave Kings Above

char* encrypte(char* plaintext, int Rotornumber,char* RingSetting,\
               char* MessageKey, char* plugboard);
int find(int whichrotor, char letter);
char* cracking(char* word,char* cypher,int Rotornumber,\
               char* RingSetting, char* plugboard);
void RotateMessageKey(char* MessageKey,int Rotornumber);
void ReverseRotateMessageKey(char* MessageKey,int Rotornumber,int times);
char AfterPlugboard(char* plugboard,char c);

int main(){
    
    char* plaintext;
    char cypher[1005];
    int Rotornumber = 125;
    char RingSetting[5] = "TIP";
    char* MessageKey;
    char plugboard[25] = "POLMIUJKNHYTGBVFREDC";
    char word[25];
    char key[5] = "XYZ";
    /*
	srand((unsigned) time(NULL)); 
    for(int i=0;i < 1000;i++){
        cypher[i] = 'A'+rand()%26;
    }
    cypher[1001] = '\0';
    printf("\n");
    plaintext = encrypte(cypher,Rotornumber,RingSetting,key,plugboard);
    strncpy(word,plaintext+23,20);word[20] = '\0';
    printf("%s\n",cypher);
    printf("%s\n",plaintext);
    printf("%s",word);
    */
    scanf("%s",cypher);
    scanf("%s",word);
    MessageKey = cracking(word,cypher,Rotornumber,RingSetting,plugboard);
    printf("MessageKey=%s\n",MessageKey);
    plaintext = encrypte(cypher,Rotornumber,RingSetting,MessageKey,plugboard);
    printf("PlainText=%s",plaintext);
}

char* encrypte(char* plaintext, int Rotornumber,char* RingSetting,\
               char* MessageKey, char* plugboard)
{   
    char* cyphertext = (char*)malloc(sizeof(char) * 1005);
    int i = 0;
    while(plaintext[i] != '\0'){
        RotateMessageKey(MessageKey,Rotornumber);
        cyphertext[i] = plaintext[i];//copy the plaintext
        
        cyphertext[i] = AfterPlugboard(plugboard,cyphertext[i]);
        
        int delt2 = MessageKey[2] - RingSetting[2];
        cyphertext[i] = (rotor_table[Rotornumber%10-1][(cyphertext[i]-'A'+delt2+26)%26] -'A'- delt2+26)%26+'A';
        int delt1 = MessageKey[1] - RingSetting[1];
        cyphertext[i] = (rotor_table[Rotornumber/10%10-1][(cyphertext[i]-'A'+delt1+26)%26] -'A'- delt1+26)%26+'A';   
        int delt0 = MessageKey[0] - RingSetting[0];
        cyphertext[i] = (rotor_table[Rotornumber/100-1][(cyphertext[i]-'A'+delt0+26)%26] -'A'- delt0+26)%26+'A';   
        
        cyphertext[i] = reflector[cyphertext[i]-'A'];

        cyphertext[i] = ( find(Rotornumber/100-1,(cyphertext[i]-'A'+delt0+26)%26+'A') -delt0+26)%26 +'A';
        cyphertext[i] = ( find(Rotornumber/10%10-1,(cyphertext[i]-'A'+delt1+26)%26+'A')-delt1+26)%26+'A';
        cyphertext[i] = ( find(Rotornumber%10-1,(cyphertext[i]-'A'+delt2+26)%26+'A')-delt2+26)%26+'A';
        
        cyphertext[i] = AfterPlugboard(plugboard,cyphertext[i]);
        
        i++;
    }
    cyphertext[i] = '\0';
    return cyphertext;
}

int find(int whichrotor, char letter){
    int i;
    for(i=0;i<26;i++){
        if(letter == rotor_table[whichrotor][i]){
            return i;
        }
    }
}

char* cracking(char* word,char* cypher,int Rotornumber,\
               char* RingSetting, char* plugboard)
{
    char* testkey = (char*)malloc(sizeof(char) * 5);
    char* testword;
    testkey[3] = '\0';
    for(int i=0;i<26;i++){
        testkey[0] = i+'A';
        for(int j=0;j<26;j++){
            testkey[1] = j + 'A';
            for(int m=0;m<26;m++){
                testkey[2] = m + 'A';
                testword = encrypte(word,Rotornumber,RingSetting,testkey,plugboard);
                if(strstr(cypher,testword)){
                    goto h;
                }
                free(testword);
            }
        }
    }
    
    h:   
    ReverseRotateMessageKey(testkey,Rotornumber,strlen(word)) ;
    ReverseRotateMessageKey(testkey,Rotornumber,strstr(cypher,testword)-cypher) ;
    return testkey;
}

void RotateMessageKey(char* MessageKey,int Rotornumber){
    if(MessageKey[1] == step_char[Rotornumber/10%10-1] -1){//double stepping
            MessageKey[0]++;
            MessageKey[1]++;
            MessageKey[2]++;
            if(MessageKey[0]=='Z'+1) MessageKey[0] = 'A';
            if(MessageKey[1]=='Z'+1) MessageKey[1] = 'A';
            if(MessageKey[2]=='Z'+1) MessageKey[2] = 'A';
        }else{//stepping
            MessageKey[2]++;
            if(MessageKey[2]=='Z'+1) MessageKey[2] = 'A';
            if(MessageKey[2] == step_char[Rotornumber%10-1]) MessageKey[1]++;
            if(MessageKey[1]=='Z'+1) MessageKey[1] = 'A';
        }
}

void ReverseRotateMessageKey(char* MessageKey,int Rotornumber,int times){
    while(times--){
        if(MessageKey[1] == step_char[Rotornumber/10%10-1] && MessageKey[2]==step_char[Rotornumber%10-1]+1){//double stepping
            MessageKey[0]--;
            MessageKey[1]--;
            MessageKey[2]--;
            if(MessageKey[0]=='A'-1) MessageKey[0] = 'Z';
            if(MessageKey[1]=='A'-1) MessageKey[1] = 'Z';
            if(MessageKey[2]=='A'-1) MessageKey[2] = 'Z';
        }else{//stepping
            if(MessageKey[2] == step_char[Rotornumber%10-1]) MessageKey[1]--;
            MessageKey[2]--;
            if(MessageKey[2]=='A'-1) MessageKey[2] = 'Z';
            if(MessageKey[1]=='A'-1) MessageKey[1] = 'Z';
        }
    }
}


char AfterPlugboard(char* plugboard,char c){
    int j = 0;
    while(plugboard[j] != '\0' ){
        if(c == plugboard[j]){
            c = plugboard[j+1];
            break;
        }else if(c == plugboard[j+1]){
            c = plugboard[j];
            break;
        }
        j+=2;
    }
    return c;
}