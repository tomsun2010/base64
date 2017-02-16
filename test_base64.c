#ifdef __cplusplus
    extern "C" {
#endif  /* __cplusplus */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "base64.h"

int main(int argc, char **argv)
{
	char pwd[64] = {0}; 
	char pwd_encode[64] = {0};
	char pwd_decode[64] = {0};
	
	while(1)
	{
		memset(pwd, 0, sizeof(pwd));
		memset(pwd_encode, 0, sizeof(pwd_encode));
		memset(pwd_decode, 0, sizeof(pwd_decode));
		printf("please input:\n");
		scanf("%s", pwd);
		
		base64_encode((const unsigned char *)pwd, pwd_encode, strlen(pwd));
		printf("pwd = %s\n", pwd);
		printf("pwd_encode = %s\n", pwd_encode);
		
		base64_decode(pwd_encode, pwd_decode);
		printf("pwd_decode = %s\n", pwd_decode);
	}
	
	
	
	return 0;
}




#ifdef __cplusplus
}
#endif  /* __cplusplus */