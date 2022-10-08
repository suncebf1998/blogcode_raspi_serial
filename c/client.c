#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include <stdio.h>





int main(int argc, char *argv[]){
    char device[15];
    int baudrate;
    uint16_t index;
    uint16_t data;
    int port;

    // strcpy(device, "/dev/ttyAMA1");
    // baudrate = 115200;
    // if (argc > 1)
    // {
    //     // device = argv[1];
    //     strcpy(device, argv[1]);
    //     if (argc > 2)
    //     {
    //         baudrate = atoi(argv[2]);
    //     }
    // }

    strcpy(device, (argc > 1)? argv[1]: "/dev/ttyAMA1");
    baudrate = (argc > 2)? atoi(argv[2]):115200;

    port = serialOpen(device, baudrate);
    printf("port: %s, baudrate: %d.\n", device, baudrate);
    while (1)
    {
        // Loop
        index = 0x0000;
        data = 0x0000;
        while (serialDataAvail(port) < 4)
        {
            delay(100);
        }
        index |= ((uint16_t) serialGetchar(port) << 8);
        index |= (uint16_t) serialGetchar(port);
        data |= ((uint16_t) serialGetchar(port) << 8);
        data |= (uint16_t) serialGetchar(port);
        printf("%d:%d\n", index, data);

        delay(900);

    }
}