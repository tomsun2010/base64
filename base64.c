
const char * g_base64_char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/*
 * bindata��ԭʼ���ݣ� base64�����ܺ�ģ� binlength��ԭʼ���ݵĳ���
*/
char *base64_encode(const unsigned char *bindata, char *base64, int binlength)
{
    int i, j;
    unsigned char current;

    for ( i=0,j=0; i<binlength; i+=3 )
    {
		//��һ�������ַ�
        current = (bindata[i] >> 2) ;
        current &= (unsigned char)0x3F;             //ȡ��i����ǰ6λ
        base64[j++] = g_base64_char[(int)current];  //����

		//�ڶ��������ַ�
        current = ( (unsigned char)(bindata[i] << 4 ) ) & ( (unsigned char)0x30 ) ;  //ȡ��i���ĺ�2λ
        if ( i+1 >= binlength )  //������治��1���ַ�������ͽ����ˣ����Ⱥ�
        {
            base64[j++] = g_base64_char[(int)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
		//���湻1���ַ�����������
        current |= ( (unsigned char)(bindata[i+1] >> 4) ) & ( (unsigned char) 0x0F ); //ȡ��i+1����ǰ4λ
        base64[j++] = g_base64_char[(int)current];

		//�����������ַ�
        current = ( (unsigned char)(bindata[i+1] << 2) ) & ( (unsigned char)0x3C ) ;  //ȡ��i+1���ĺ�4λ
        if ( i+2 >= binlength )
        {
            base64[j++] = g_base64_char[(int)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (unsigned char)(bindata[i+2] >> 6) ) & ( (unsigned char) 0x03 ); //ȡ��i+2��ǰ2λ
        base64[j++] = g_base64_char[(int)current];

		//���ĸ������ַ�
        current = ( (unsigned char)bindata[i+2] ) & ( (unsigned char)0x3F ) ;  //ȡ��i+2�ĺ�6λ
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
	

	//��ȡ��ֵ��4��
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

		//������ֵ������Դ��
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
