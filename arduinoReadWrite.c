#include <termios.h>  // For serial port configuration
#include <fcntl.h>    // For file control (opening serial ports)
#include <unistd.h>   // For POSIX system calls like read/write
#include <stdio.h>    // For standard I/O (printf, perror)



int openSerial(int *fd) {
    *fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (*fd < 0) {
        perror("Error opening serial port");
        return 0;
    }

    struct termios tty;
    if (tcgetattr(*fd, &tty) < 0) {
        perror("Error getting serial port attributes");
        close(*fd);
        return 0;
    }

    // Configure serial port settings
    cfsetospeed(&tty, B9600);  // Baud rate 9600
    cfsetispeed(&tty, B9600);

    tty.c_cflag &= ~PARENB;    // No parity
    tty.c_cflag &= ~CSTOPB;    // 1 stop bit
    tty.c_cflag &= ~CSIZE;     // Clear data size
    tty.c_cflag |= CS8;        // 8 bits
    tty.c_cflag |= CREAD | CLOCAL;  // Enable receiver, ignore modem control lines

    // Apply settings
    if (tcsetattr(*fd, TCSANOW, &tty) < 0) {
        perror("Error setting serial port attributes");
        close(*fd);
        return 0;
    }

    return 1;
}

int arduinoWrite(int *fd) {
    char lpBuffer = 'A';
    ssize_t bytesWritten = write(*fd, &lpBuffer, sizeof(lpBuffer));
    if (bytesWritten < 0) {
        perror("Error writing to serial port");
        close(*fd);
        return 0;
    }
    return 1;  // Success
}
