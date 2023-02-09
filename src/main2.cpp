#include <stdio.h>
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

int main()
{
	char input[13] = "Hello, world";
	unsigned char md[SHA_DIGEST_LENGTH];
	if (!sha1(input, strlen(input), md)) {
		printf("[ERROR]: SHA256 did not work\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for (int i=0; i < SHA_DIGEST_LENGTH; i++)
		{
			printf("%02x", md[i]);
		}
		printf("\n");
	}
}