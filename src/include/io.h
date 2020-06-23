#ifndef _IO_H
#define _IO_H 1

static __inline void outb(unsigned char value, unsigned short int port)
{
   __asm__ __volatile__ ("outb %w1,%b0": :"a" (value), "Nd" (port));
}

static __inline unsigned char inb(unsigned short int port)
{
   unsigned char ret;
   __asm__ __volatile__ ("inb %0,%w1":"=a" (ret):"Nd" (port));
   return ret;
}

#endif /* _IO_H */
