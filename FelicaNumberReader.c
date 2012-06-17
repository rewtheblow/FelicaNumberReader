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

static void hexdump(FILE *fp, uint8 *addr, int n);

int main()
{
	FILE *fp;
	pasori *p;
	felica *f;
	char s[256];

	if ((fp = fopen(OUTPUT_FILE, "a")) == NULL) {
		printf("file open error!!\n");
		exit(0);
	}
	printf("%s\n", "##############################################");
    printf("##   %s%s   ##\n", "Output file name is ", OUTPUT_FILE);
	printf("%s\n", "##############################################");
    
	fprintf(fp, "%s\n", "##############################################");
    fprintf(fp, "##   %s%s   ##\n", "Output file name is ", OUTPUT_FILE);
	fprintf(fp, "%s\n", "##############################################");

    fclose(fp);

    p = pasori_open(NULL);
    if (!p) {
        printf("PaSoRi open failed.");
        exit(1);
    }
    pasori_init(p);

	while(1){
		if ((fp = fopen(OUTPUT_FILE, "a")) == NULL) {
			printf("file open error!!\n");
			exit(0);
		}

	    f = felica_polling(p, POLLING_ANY, 0, 0);
        if (f) {
            hexdump(fp, f->IDm, 8);
            printf("    read succeeded.\n");
            fprintf(fp, "    read succeeded.\n");
            putchar('\a');
//      }
//      else
//      {
//          printf("Polling card failed.\n");
        }

        sleep(2);
        fclose(fp);
    }

    
//    felica_free(f);
	return 0;
}

static void hexdump(FILE *fp, uint8 *addr, int n)
{
time_t target_time;
	struct tm* target_time_tm;
	char* time_string;
	int string_length=20;
    int i;
    	
	time_string=(char *)malloc(string_length*sizeof(char));
	(void)time(&target_time);
	target_time_tm=localtime(&target_time);
	(void)strftime(time_string,string_length,"%Y/%m/%d %H:%M:%S",target_time_tm);

    printf("%s    ", time_string);
    fprintf(fp, "%s   ", time_string);
    for (i = 0; i < n; i++) {
        printf("%02X ", addr[i]);
        fprintf(fp, "%02X ", addr[i]);
    }
}
