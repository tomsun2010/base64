
const char * g_base64_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/*
 * bindata：原始数据， base64：加密后的， binlength：原始数据的长度
*/
char *base64_encode(const unsigned char *bindata, char *base64, int binlength)
{
    int i, j;
    unsigned char current;

    for ( i=0,j=0; i<binlength; i+=3 )
    {
		//第一个编码字符
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;             //取第i个的前6位
        base64[j++] = g_base64_char[(int)current];  //编码

		//第二个编码字符
        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;  //取第i个的后2位
        if ( i+1 >= binlength )  //如果后面不够1个字符，编码就结束了，补等号
        {
            base64[j++] = g_base64_char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
		//后面够1个字符，继续编码
        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F ); //取第i+1个的前4位
        base64[j++] = g_base64_char[(int)current];

		//第三个编码字符
        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;  //取第i+1个的后4位
        if ( i+2 >= binlength )
        {
            base64[j++] = g_base64_char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 ); //取第i+2的前2位
        base64[j++] = g_base64_char[(int)current];

		//第四个编码字符
        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;  //取第i+2的后6位
        base64[j++] = g_base64_char[(int)current];
    }
    base64[j] = '\0';
    return base64;
}

int base64_decode(char *base64, unsigned char *bindata)
{
    int i = 0, j = 0;
    unsigned char k = 0;
    unsigned char temp[4] = {};
	

	//获取码值，4个
    for(i = 0, j = 0; base64[i] != '\0' ; i += 4)
    {
        memset(temp, 0xFF, sizeof(temp));
        for(k = 0; k < 64; k ++)
        {
            if(g_base64_char[k] == base64[i])
                temp[0]= k;
        }
        for(k = 0; k < 64; k ++)
        {
            if(g_base64_char[k] == base64[i+1])
                temp[1]= k;
        }
        for(k = 0; k < 64; k ++)
        {
            if ( g_base64_char[k] == base64[i+2])
                temp[2]= k;
        }
        for(k = 0; k < 64; k ++)
        {
            if(g_base64_char[k] == base64[i+3])
                temp[3]= k;
        }

		//根据码值，反推源码
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2))&0xFC)) | ((unsigned char)((unsigned char)(temp[1]>>4)&0x03));
        if(base64[i+2] == '=')
        {
            break;
        }
        
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4))&0xF0)) | ((unsigned char)((unsigned char)(temp[2]>>2)&0x0F));
        if (base64[i+3] == '=')
        {
            break;
        }
        
        bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6))&0xF0)) | ((unsigned char)(temp[3]&0x3F));

    }
    
    return j;
}
