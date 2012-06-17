////////////////////////////////////////////////////////
//                                                    //
//   WorkerNumberReader.c                             //
//                                                    //
//   This program can read felica's unuque number,    //
//   cooperates with ferica card reader device.       //
//                                                    //
//   Authour  : Ryusaburo Tanaka                      //
//   Date     : June. 18th. 2012                      //
//                                                    //
////////////////////////////////////////////////////////

#include <stdio.h>
#include "felicalib.h"

static void hexdump(uint8 *addr, int n);

int main()
{
	pasori *p;
	felica *f;

    p = pasori_open(NULL);
    if (!p) {
        printf("PaSoRi open failed.");
        exit(1);
    }
    pasori_init(p);

	while(1){
	    f = felica_polling(p, POLLING_ANY, 0, 0);
        if (f) {
            hexdump(f->IDm, 8);
            printf("\n");
            hexdump(f->PMm, 8);
            printf("\n");
            printf("read succeeded.\n");
            putchar('\a');
//      }
//      else
//      {
//          printf("Polling card failed.\n");
        }
        sleep(2);
    }

    
//    felica_free(f);
	return 0;
}

static void hexdump(uint8 *addr, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%02X ", addr[i]);
    }
}
