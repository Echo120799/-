#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

int main() 
{
	//读取文件
	string file = "plaintext.txt";
	ifstream in;
	in.open(file.data());
	if (!in.is_open())
	{
		cout << "can't open the txt" << endl;
	}
	
	string line;
	getline(in, line);
	in.close();

	char* text =&line[0];
	size_t len = strlen(text) + 1;
	//分组
	if (len % AES_BLOCK_SIZE != 0)
	{
		len = (len / AES_BLOCK_SIZE + 1)*AES_BLOCK_SIZE;  
	}

	//存放明文的字节数组
	unsigned char* plainText = new unsigned char[len];
	strcpy_s((char*)plainText,len,text);

	//生成aes密钥
	unsigned char my_16bytes_key[16] = { 0 };
	for (int i = 0; i < 16; ++i) 
	{
		my_16bytes_key[i] = 0x30;
	}
	AES_KEY aes_key;
	AES_set_encrypt_key(my_16bytes_key, 128, &aes_key);

	//初始向量，此处设为0
	unsigned char iv[AES_BLOCK_SIZE];        // init vector
	for (int i = 0; i < AES_BLOCK_SIZE; ++i)
	{
		iv[i] = 0;
	}

	//加密
	unsigned char* cipherText = new unsigned char[len];
	AES_cbc_encrypt(plainText, cipherText, len, &aes_key, iv, AES_ENCRYPT);

	//解密
	//解密文字存放的数组
	unsigned char* decryptText = new unsigned char[len];

	//初始向量，与加密时一致。
	for (int i = 0; i < AES_BLOCK_SIZE; ++i)
	{
		iv[i] = 0;
	}

	//初始化秘钥结构体
	AES_set_decrypt_key(my_16bytes_key, 128, &aes_key);
	//解密。
	AES_cbc_encrypt(cipherText, decryptText, len, &aes_key, iv, AES_DECRYPT);

	// print
	printf("原文 : %s\n", plainText);
	printf("密文 : %s\n", cipherText);
	printf("解密后文字 : %s\n", decryptText);
	system("pause");
	return 0;
}