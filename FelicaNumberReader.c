////////////////////////////////////////////////////////
//                                                    //
//   FelicaNumberReader.c                             //
//                                                    //
//   This program can read felica's unuque number,    //
//   cooperates with ferica card reader device.       //
//                                                    //
//   Authour  : Ryusaburo Tanaka                      //
//   Date     : June. 18th. 2012                      //
//                                                    //
////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>
#include "felicalib.h"

#define OUTPUT_FILE    "felicaNumber.log"

static void hexdump(FILE *pfile, uint8 *addr, int n);

int main()
{
    FILE *pFile;        // pointer of output file
    pasori *pPasori;    // pointer of PaSoRi
    felica *pFelica;    // pointer of Felica data

    // display start message
    printf("%s\n", "************************************************");
    printf("%s\n", "***                                          ***");
    printf("%s\n", "***  Felica number reader for TECH-MEET      ***");
    printf("%s\n", "***                          Version 1.0     ***");
    printf("%s\n", "***                                          ***");
    printf("%s\n", "***  Plug your felica card reader to the PC  ***");
    printf("%s\n", "***  Touch the felica card to the reader     ***");    
    printf("%s\n", "***  Felica number will be read and logged   ***");
    printf("%s\n", "***                                          ***");
    printf("%s\n", "*** - Ctrl + C ------- exit this program     ***");
    printf("%s\n", "***                                          ***");
    printf("%s\n", "***      implemeneted by Ryusaburo Tanaka    ***");
    printf("%s\n", "************************************************");
    printf("\n");

    // open output file
    if ((pFile = fopen(OUTPUT_FILE, "a")) == NULL) {
        printf("file open error!!\n");
        exit(0);
    }

    // display start message on console
    printf("%s\n", "################################################");
    printf("%s\n", "##   This is the log file of                  ##");
    printf("%s\n", "##                      Felica number reader  ##");
    printf("%s\n", "################################################");
    
    // write start message in the log file
    fprintf(pFile, "%s\n", "################################################");
    fprintf(pFile, "##    %s%s    ##\n", "Output file name is ", OUTPUT_FILE);
    fprintf(pFile, "%s\n", "################################################");

    // close log file once
    fclose(pFile);

    // open and initialize PaSoRi card reader device
    pPasori = pasori_open(NULL);
    if (!pPasori) {
        printf("PaSoRi open failed.");
        exit(1);
    }
    pasori_init(pPasori);

    // main loop, wait and recieve touching of Felica
    while(1){    /* loop infinitely currently */
    
        // open output file
        if ((pFile = fopen(OUTPUT_FILE, "a")) == NULL) {
            printf("file open error!!\n");
            exit(0);
        }

        // read and output felica data, sound beep
        pFelica = felica_polling(pPasori, POLLING_ANY, 0, 0);
        if (pFelica) {
            hexdump(pFile, pFelica->IDm, 8);
            printf("    read succeeded.\n");
            fprintf(pFile, "    read succeeded.\n");
            putchar('\a');
//      }
//      else
//      {
//          printf("Polling card failed.\n");   /* comment out currently */
        }

        // wait 2 minutes
        sleep(2);
        
        // close ourput file
        fclose(pFile);
    }

    
    // release felica pointer
//    felica_free(f);    /* comment out currently */
    return 0;
}


static void hexdump(FILE *pFile, uint8 *addr, int n)
{
    // decralation of datetime variants
    time_t target_time;
    struct tm* target_time_tm;
    char* time_string;
    int string_length = 20;
    int i;

    // get and foramt system datetime
    time_string = (char *)malloc(string_length*sizeof(char));
    (void)time(&target_time);
    target_time_tm = localtime(&target_time);
    (void)strftime(time_string, string_length, "%Y/%m/%d %H:%M:%S", target_time_tm);

    // print and output recieved data as hexa dump with system datetime
    printf("%s    ", time_string);
    fprintf(pFile, "%s   ", time_string);
    for (i = 0; i < n; i++) {
        printf("%02X", addr[i]);
        fprintf(pFile, "%02X", addr[i]);
    }
}
