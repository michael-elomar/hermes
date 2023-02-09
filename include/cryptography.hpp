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



#endif