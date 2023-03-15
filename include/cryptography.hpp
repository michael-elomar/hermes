#ifndef CRYPTOGRAPHY_HPP
#define CRYPTOGRAPHY_HPP

#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

bool sha256(void *input, unsigned long length, unsigned char *md)
{
	SHA256_CTX context;
	if (!SHA256_Init(&context))
		return false;

	if(!SHA256_Update(&context, (unsigned char *)input, length))
		return false;

	if(!SHA256_Final(md, &context))
		return false;

	return true;
}

bool sha1(void *input, unsigned long length, unsigned char *md)
{
	SHA_CTX context;
	if (!SHA1_Init(&context))
		return false;

	if(!SHA1_Update(&context, (unsigned char *)input, length))
		return false;

	if(!SHA1_Final(md, &context))
		return false;

	return true;
}

char* base64Encode(uint8_t *input, uint32_t length)
{
	const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	size_t output_len = 4 * ((length + 2) / 3);
	uint8_t remainder = length % 3; //remainder
	uint8_t a1,a2,a3,a4;
	char* output = (char *)malloc(output_len + 1);

	int j = 0;
	if (length >= 3)
	{
		for(int i=0;i < length - remainder; i = i+3)
		{
			a1 = input[i] >> 2;
			a2 = (input[i] % 4) * 16 + (input[i+1] >> 4);
			a3 = (input[i+1] % 16) * 4 + (input[i+2] >> 6);
			a4 = input[i+2] % 64;
			output[j] = base64_chars[a1];
			output[j+1] = base64_chars[a2];
			output[j+2] = base64_chars[a3];
			output[j+3] = base64_chars[a4];
			j += 4;
		}
	}
	switch (remainder)
	{
		case 1:
			a1 = input[length-1] >> 2;
			a2 = (input[length-1] % 4) * 16;
			output[j] = base64_chars[a1];
			output[j+1] = base64_chars[a2];
			output[j+2] = '=';
			output[j+3] = '=';
			// add == padding
			break;
		case 2:
			a1 = input[length -2] >> 2;
			a2 = (input[length - 2] % 4) * 16 + (input[length - 1] >> 4);
			a3 = (input[length - 1] % 16)*4; // add = padding
			output[j] = base64_chars[a1];
			output[j+1] = base64_chars[a2];
			output[j+2] = base64_chars[a3];
			output[j+3] = '=';
			break;
	}
	output[output_len] = '\0';
	return output;
}


#endif