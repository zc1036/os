#include <string.h>
#include <io.h>
#include <serial.h>
 
#define PORT_COM1 0x3F8
#define PORT_COM2 0x2F8
#define PORT_COM3 0x3E8
#define PORT_COM4 0x2E8

// IO Port Offsets
//    DLAB not set
#define COM_DATA_REG 0
#define COM_INT_REG  1
//    DLAB set
#define COM_BAUD_LO  0
#define COM_BAUD_HI  1
//    DLAB set or not set
#define COM_INT_ID   2
#define COM_FIFO     2
#define COM_LINE_CTL 3
#define COM_DLAB     3 // MSB determines DLAB
#define COM_MODEM_CTL   4
#define COM_LINE_STATUS 5
#define COM_MODEM_STATUS   6
#define COM_SCRATCH  7

#define BIT(n) (1 << (n))
#define INT_DATA       BIT(0)
#define INT_TRANSMIT   BIT(1)
#define INT_BREAK      BIT(2)
#define INT_STATUS     BIT(3)
#define INT_DISABLE_ALL 0

#define DLAB_SET     0x80
#define DLAB_UNSET   0x00

#define BAUD_DIVISOR_HI(x) ((115200 / x) & 0xFF00) >> 8
#define BAUD_DIVISOR_LO(x) ((115200 / x) & 0x00FF)

#define DATA_BITS_5  0
#define DATA_BITS_6  BIT(0)
#define DATA_BITS_7  BIT(1)
#define DATA_BITS_8  BIT(0) | BIT(1)

#define STOP_BIT_1 0
#define STOP_BIT_2 BIT(2)

#define PARITY_NONE  0
#define PARITY_ODD   BIT(3)
#define PARITY_EVEN  BIT(3) | BIT(4)
#define PARITY_MARK  BIT(3) | BIT(5)
#define PARITY_SPACE BIT(3) | BIT(4) | BIT(5)

#define LINE_STATUS_DR  BIT(0) // Data Ready (DR)
#define LINE_STATUS_OE  BIT(1) // Overrun Error (OE)
#define LINE_STATUS_PE  BIT(2) // Parity Error (PE)
#define LINE_STATUS_FE  BIT(3) // Framing Error (FE)
#define LINE_STATUS_BI  BIT(4) // Break Indicator (BI)
#define LINE_STATUS_THRE   BIT(5) // Transmitter Holding Register Emptry (THRE)
#define LINE_STATUS_TEMT   BIT(6) // Transmitter Empty (TEMT)
#define LINE_STATUS_ERR BIT(7) // Impending Error

unsigned int serial_enabled = 0;
unsigned int serial_initialized = 0;

void serial_initialize()
{
   unsigned short port = PORT_COM1;
   outb(INT_DISABLE_ALL, port + COM_INT_REG);  // Disable all interrupts
   outb(DLAB_SET, port + COM_DLAB);     // Enable DLAB (set baud rate divisor)
   outb(BAUD_DIVISOR_LO(9600), port + COM_BAUD_LO);  // Set divisor for 9600 baud (lo byte)
   outb(BAUD_DIVISOR_HI(9600), port + COM_BAUD_HI);  //                           (hi byte)
   outb(DATA_BITS_8 | STOP_BIT_1 | PARITY_NONE, port + COM_LINE_CTL); // 8 bits, no parity, one stop bit
   outb(0xC7, port + COM_FIFO);     // Enable FIFO, clear them, with 14-byte threshold
   outb(0x0B, port + COM_MODEM_CTL);// IRQs enabled, RTS/DSR set

   serial_initialized = 1;
}

int serial_received()
{
   return inb(PORT_COM1 + COM_LINE_STATUS) & LINE_STATUS_DR;
}

char serial_read()
{
   while (serial_received() == 0) ;
   return inb(PORT_COM1 + COM_DATA_REG);
}

int serial_is_transmit_empty()
{
   return inb(PORT_COM1 + COM_LINE_STATUS) & LINE_STATUS_THRE;
}

void serial_putchar(char c)
{
   while (serial_is_transmit_empty() == 0) ;

   outb(c, PORT_COM1);
}

void serial_write(const char* data, size_t size)
{
   for (size_t i = 0; i < size; i++)
      serial_putchar(data[i]);
}

void serial_writestring(const char* data)
{
   serial_write(data, strlen(data));
}
