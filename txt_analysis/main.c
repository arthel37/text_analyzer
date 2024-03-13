#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
    FILE *txtfile;
    long numbytes;
    char *text;
    char *token;
    int wordc = 0;
    size_t charc;
    int scharc = 0;
    int letterc = 0;
    int uppc = 0;
    int lowc = 0;
    int spacec = 0;
    int digitc = 0;
    int i = 0;
    int j = 0;
    int ascii;
    int lettersarr[95][2];

    txtfile = fopen("textfile.txt", "r");
    if (txtfile == NULL){
        printf("Empty file");
        return 1;
    }

    fseek(txtfile, 0L, SEEK_END);
    numbytes = ftell(txtfile);
    fseek(txtfile, 0L, SEEK_SET);

    text = (char*)calloc(numbytes, sizeof(char));
    if (text == NULL){
        printf("Could not read text correctly");
        return 2;
    }

    fread(text, sizeof(char), numbytes, txtfile);
    fclose(txtfile);

    printf("%s\n", text);

    text[numbytes] = '\0';

    charc = strlen(text);

    for (j = 32; j <= 126; j++){
        lettersarr[j-32][0] = j;
        lettersarr[j-32][1] = 0;
    }

    for (i = 0; i < charc; i++){
        ascii = (int)(text[i]);
     //   printf("%c %d\n", text[i], ascii);
        for (j = 32; j <= 126; j++){
            if (ascii == j){
                lettersarr[j-32][1] += 1;
                if ((j>=97 && j<=122)){
                    letterc++;
                    lowc++;
                }
                else if (j>=48 && j<=57){
                    digitc++;
                }
                else if (j>=65 && j<=90){
                    letterc++;
                    uppc++;
                }
                else {

                    scharc++;
                }
            }
        }
    }

     for (j = 0; j < 95; j++){
            if (lettersarr[j][1] != 0){
                printf("%c %d\n", lettersarr[j][0], lettersarr[j][1]);
            }
    }


    token = strtok(text, " !#$%^'()*+,-./:;<=>?@[\]^_`{|}~\"\n");
    while (token != NULL){
        wordc += 1;
     //   printf("%s\n", token);
        token = strtok(NULL, " !#$%^'()*+,-./:;<=>?@[\]^_`{|}~\"\n");
    }

    spacec = lettersarr[0][1];

    scharc = scharc-spacec;

    printf("Text file contains %d words, %d spaces and %zu characters.\n", wordc, spacec, charc);
    printf("These characters include %d letters, of which %d are lowercase, while %d are uppercase letters, %d special characters (excluding spaces) and %d digits.\n", letterc, lowc, uppc, scharc, digitc);
    return 0;
}
