# ifndef _at24c02_H
# define _at24c02_H

# include "public.h"
# include "iic.h"

//写字节
void at24c02_write_byte(uchar addr, ulong dat);

//读字节
ulong at24c02_read_byte(uchar addr);

# endif