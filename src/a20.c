#include <a20.h>
#include <serial.h>
#include <printf.h>

int is_a20_enabled()
{
   int ret = 0;
   void *low_ptr = (void *)0x012345;
   void *hi_ptr = (void *)0x112345;

   *(int *)(low_ptr) = 0x012345;
   *(int *)(hi_ptr) = 0x112345;
   if(*(int *)(low_ptr) == *(int *)(hi_ptr))
   {
      serial_writestring("a20 is disabled!\n");
      ret = 0;
   }else
   {
      serial_writestring("a20 is enabled!\n");
      ret = 1;
   }
   return ret;
}
