#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include <stdio.h>



int main(int argc, char *argv[]){
    char device[15];
    int baudrate;
    uint8_t info[5]; // [:2] index, [2:] data 
    uint16_t index;
    uint16_t data;
    int port;

    strcpy(device, "/dev/ttyAMA0");
    baudrate = 115200;
    if (argc > 1)
    {
        // device = argv[1];
        strcpy(device, argv[1]);
        if (argc > 2)
        {
            baudrate = atoi(argv[2]);
        }
    }

    srand((unsigned) time(NULL)); // set seed
    index = 0;
    port = serialOpen(device, baudrate);
    info[4] = 0x00;
    printf("port: %s, baudrate: %d @ %d.\n", device, baudrate, port);
    while (1)
    {
        // Loop
        data = (uint16_t) (rand() & 0xFFFF);

        info[0] = (uint8_t) (index & 0xFF00);
        info[1] = (uint8_t) (index & 0x00FF);
        info[2] = (uint8_t) (data & 0xFF00);
        info[3] = (uint8_t) (data & 0x00FF);
        
        /**
         * 
         *  don't use serialPuts: info start with 0x00 -> strlen(s) = 0
         serialPuts(port, (char*) info);
         void serialPuts (const int fd, const char *s)
        {
        write (fd, s, strlen (s)) ; // unistd.h
        }
         
         */
        write(port, info, 4);

        printf("%d\n", info[1]);
        
        index++;

        delay(1000);

    }
}