#include "mini_uart.h"
#include "tool.h"
#include "string.h"
#include "devicetree.h"
typedef struct {//cpio_newc_header
	char	c_magic[6];
	char	c_ino[8];
	char	c_mode[8];
	char	c_uid[8];
	char	c_gid[8];
	char	c_nlink[8];
	char	c_mtime[8];
	char	c_filesize[8];
	char	c_devmajor[8];
	char	c_devminor[8];
	char	c_rdevmajor[8];
	char	c_rdevminor[8];
	char	c_namesize[8];
	char	c_check[8];
} cpio_header_type;

char * base_address;
void init_cpio(){
	base_address = (char *)initramfs_callback();
}


void ls(){
    char * address = (char *)base_address;
    while(!memcmp(address,"070701",6) && memcmp(address+sizeof(cpio_header_type),"TRAILER!!",9)){
        cpio_header_type * cpio_header = (cpio_header_type *)address;
        int namesize = hex2dec(cpio_header->c_namesize,8);
        int filesize = hex2dec(cpio_header->c_filesize,8);
        uart_puts_width(address + sizeof(cpio_header_type),namesize);
        uart_send_string("\r\n");

        if ((sizeof(cpio_header_type) + namesize) % 4){
            address += (((sizeof(cpio_header_type)+namesize) / 4) +1 ) * 4;
        }
        else{
            address += sizeof(cpio_header_type) + namesize;
        }
        
        if ((filesize)%4){
            address += ((filesize / 4 ) +1) * 4;
        }
        else{
            address += filesize;
        }
    }
}


void cat(char * str){
	char * address = (char *)base_address;
    char * filename;
    int found = 0;
    while(!memcmp(address,"070701",6) && memcmp(address+sizeof(cpio_header_type),"TRAILER!!",9)){
        cpio_header_type * cpio_header = (cpio_header_type *)address;
        int namesize = hex2dec(cpio_header->c_namesize,8);
        int filesize = hex2dec(cpio_header->c_filesize,8);
        filename = address + sizeof(cpio_header_type);
        if(!memcmp(str+4,filename,strlen(str+4)+1)){
            uart_puts_width(address + sizeof(cpio_header_type)+namesize,filesize);
           // uart_send_string("\r\n");
            found = 1;
            break;
        }
        if ((sizeof(cpio_header_type) + namesize) % 4){
            address += (((sizeof(cpio_header_type)+namesize) / 4) +1 ) * 4;
        }
        else{
            address += sizeof(cpio_header_type) + namesize;
        }
        
        if ((filesize)%4){
            address += ((filesize / 4 ) +1) * 4;
        }
        else{
            address += filesize;
        }
    }
    if(!found){
        uart_send_string("file not found!\r\n");
    }
    filename = NULL;
}
