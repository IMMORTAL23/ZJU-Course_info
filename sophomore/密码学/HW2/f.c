static long32 f(ulong32 r, unsigned char subkey[8])
{
	unsigned char s[4], plaintext[8], m[4], t[4];
    unsigned long int rval;
/*-------------(1) ------------------*/
	s[0] = r & 0xFF;
	s[1] = (r & 0xFF00)>>8;
	s[2] = (r & 0xFF0000) >> 16;
	s[3] = (r & 0xFF000000) >> 24;
	#ifdef LITTLE_ENDIAN
    s[0] = byteswap(s[0]);
    s[1] = byteswap(s[1]);
	s[2] = byteswap(s[2]);
    s[3] = byteswap(s[3]);
	#endif
/*------------(2)---------------------*/
	int i = 0;j = 0,temp = 0,ans=0;
	for(i=0;i<8;i++){
		ans = 0;temp = 0;
		for(j=0;j<6;j++){
			temp = plaintext_32bit_expanded_to_48bit_table[6*i+j] - 1;
			ans |= ( s[temp/8] & bytebit[7-temp%8] ) >> 2;
		}
		plaintext[i] = ans;
	}
}