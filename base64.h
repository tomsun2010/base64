#ifndef __BASE_API_H
#define __BASE_API_H

#ifdef __cplusplus
         extern "C" {
#endif  /* __cplusplus */


#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>

char *base64_encode(const unsigned char *bindata, char *base64, int binlength);
int base64_decode(char *base64, unsigned char *bindata);




#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif