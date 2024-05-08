#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Bmp2File.h"


// 输入默认是字节对齐
int Bmp1_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData)
{
	int vRet = 0;
	CBmp1 tBmp;
	int vBmpW, vDataW;
	unsigned char *ptr = NULL;
	unsigned char *szLine = NULL;
	int vDataSize, vAllSize;
	int i;
	FILE *fp = NULL;

	vDataW = (vWidth+7)/8;
	vBmpW = (vWidth+31)/32*4;
	vDataSize = vBmpW*vHeight;
	vAllSize = sizeof(CBmp1)+vDataSize;
	szLine = malloc(vBmpW);
	if(szLine == NULL){
		vRet = -1;
		goto LB_END;
	}
	// 文件头
	memset(&tBmp, 0, sizeof(CBmp1));

	memcpy(tBmp.tHead.szType, "BM", 2);
	tBmp.tHead.vFileSize = vAllSize;
	tBmp.tHead.vDataOffset = sizeof(CBmp1);
	tBmp.tHead.vInfoSize = 40;

	tBmp.tMsg.vWidth = vWidth;
	tBmp.tMsg.vHeight = vHeight;
	tBmp.tMsg.vPlanes = 1;
	tBmp.tMsg.vBitsPerPix = 1;
	tBmp.tMsg.vImageSize = vDataSize;

	tBmp.taPale[0].vRed = 255;
	tBmp.taPale[0].vGreen = 255;
	tBmp.taPale[0].vBlue = 255;
	tBmp.taPale[1].vRed = 0;
	tBmp.taPale[1].vGreen = 0;
	tBmp.taPale[1].vBlue = 0;
	// 写入文件
	fp = fopen(strName, "wb+");
	if(fp == NULL){
		vRet = -2;
		goto LB_END;
	}
	fwrite(&tBmp, 1, sizeof(CBmp1), fp);

	ptr = szData+(vHeight-1)*vDataW;
	memset(szLine, 0, vBmpW);
	for(i=0; i<vHeight; i++){
		memcpy(szLine, ptr, vDataW);
		fwrite(szLine, 1, vBmpW, fp);
		ptr -= vDataW;
	}
	fclose(fp);

LB_END:
	if(szLine != NULL){
		free(szLine);
	}
	return vRet;
}

int Bmp8_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData)
{
	int vRet = 0;
	CBmp8 tBmp;
	int vBmpW, vDataW;
	unsigned char *ptr = NULL;
	unsigned char *szLine = NULL;
	int vDataSize, vAllSize;
	int i;
	FILE *fp = NULL;

	vDataW = vWidth;
	vBmpW = (vWidth+3)/4*4;
	vDataSize = vBmpW*vHeight;
	vAllSize = sizeof(CBmp8)+vDataSize;
	szLine = malloc(vBmpW);
	if(szLine == NULL){
		vRet = -1;
		goto LB_END;
	}
	// 文件头
	memset(&tBmp, 0, sizeof(CBmp8));

	memcpy(tBmp.tHead.szType, "BM", 2);
	tBmp.tHead.vFileSize = vAllSize;
	tBmp.tHead.vDataOffset = sizeof(CBmp8);
	tBmp.tHead.vInfoSize = 40;

	tBmp.tMsg.vWidth = vWidth;
	tBmp.tMsg.vHeight = vHeight;
	tBmp.tMsg.vPlanes = 1;
	tBmp.tMsg.vBitsPerPix = 8;
	tBmp.tMsg.vImageSize = vDataSize;

	for(i=0; i<256; i++){
		tBmp.taPale[i].vRed = 255-i;
		tBmp.taPale[i].vGreen = 255-i;
		tBmp.taPale[i].vBlue = 255-i;
	}
	// 写入文件
	fp = fopen(strName, "wb+");
	if(fp == NULL){
		vRet = -2;
		goto LB_END;
	}
	fwrite(&tBmp, 1, sizeof(CBmp8), fp);

	ptr = szData+(vHeight-1)*vDataW;
	memset(szLine, 0, vBmpW);
	for(i=0; i<vHeight; i++){
		memcpy(szLine, ptr, vDataW);
		fwrite(szLine, 1, vBmpW, fp);
		ptr -= vDataW;
	}
	fclose(fp);

LB_END:
	if(szLine != NULL){
		free(szLine);
	}
	return vRet;
}

int Bmp16_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData)
{
	int vRet = 0;
	CBmp16 tBmp;
	int vBmpW, vDataW;
	unsigned char *ptr = NULL;
	unsigned char *szLine = NULL;
	int vDataSize, vAllSize;
	int i;
	FILE *fp = NULL;

	vDataW = vWidth<<1;
	vBmpW = (vDataW+3)/4*4;
	vDataSize = vBmpW*vHeight;
	vAllSize = sizeof(CBmp16)+vDataSize;
	szLine = malloc(vBmpW);
	if(szLine == NULL){
		vRet = -1;
		goto LB_END;
	}
	// 文件头
	memset(&tBmp, 0, sizeof(CBmp16));

	memcpy(tBmp.tHead.szType, "BM", 2);
	tBmp.tHead.vFileSize = vAllSize;
	tBmp.tHead.vDataOffset = sizeof(CBmp16);
	tBmp.tHead.vInfoSize = 40;

	tBmp.tMsg.vWidth = vWidth;
	tBmp.tMsg.vHeight = vHeight;
	tBmp.tMsg.vPlanes = 1;
	tBmp.tMsg.vBitsPerPix = 16;
	tBmp.tMsg.vCompression = 3;
	tBmp.tMsg.vImageSize = vDataSize;

	tBmp.taPale[0].vRed = 0xF800;
	tBmp.taPale[0].vGreen = 0x07E0;
	tBmp.taPale[0].vBlue = 0x001F;
	tBmp.taPale[0].vAlpha = 0x0000;

	// 写入文件
	fp = fopen(strName, "wb+");
	if(fp == NULL){
		vRet = -2;
		goto LB_END;
	}
	fwrite(&tBmp, 1, sizeof(CBmp16), fp);

	ptr = szData+(vHeight-1)*vDataW;
	memset(szLine, 0, vBmpW);
	for(i=0; i<vHeight; i++){
		memcpy(szLine, ptr, vDataW);
		fwrite(szLine, 1, vBmpW, fp);
		ptr -= vDataW;
	}
	fclose(fp);

LB_END:
	if(szLine != NULL){
		free(szLine);
	}
	return vRet;
}

int Bmp24_ToFile(const char *strName, int vWidth, int vHeight, unsigned char *szData)
{
	int vRet = 0;
	CBmp24 tBmp;
	int vBmpW, vDataW;
	unsigned char *ptr = NULL;
	unsigned char *szLine = NULL;
	int vDataSize, vAllSize;
	int i;
	FILE *fp = NULL;

	vDataW = vWidth*3;
	vBmpW = (vDataW+3)/4*4;
	vDataSize = vBmpW*vHeight;
	vAllSize = sizeof(CBmp24)+vDataSize;
	szLine = malloc(vBmpW);
	if(szLine == NULL){
		vRet = -1;
		goto LB_END;
	}
	// 文件头
	memset(&tBmp, 0, sizeof(CBmp24));

	memcpy(tBmp.tHead.szType, "BM", 2);
	tBmp.tHead.vFileSize = vAllSize;
	tBmp.tHead.vDataOffset = sizeof(CBmp24);
	tBmp.tHead.vInfoSize = 40;

	tBmp.tMsg.vWidth = vWidth;
	tBmp.tMsg.vHeight = vHeight;
	tBmp.tMsg.vPlanes = 1;
	tBmp.tMsg.vBitsPerPix = 8;
	tBmp.tMsg.vCompression = 0;
	tBmp.tMsg.vImageSize = vDataSize;

	// 写入文件
	fp = fopen(strName, "wb+");
	if(fp == NULL){
		vRet = -2;
		goto LB_END;
	}
	fwrite(&tBmp, 1, sizeof(CBmp24), fp);

	ptr = szData+(vHeight-1)*vDataW;
	memset(szLine, 0, vBmpW);
	for(i=0; i<vHeight; i++){
		memcpy(szLine, ptr, vDataW);
		fwrite(szLine, 1, vBmpW, fp);
		ptr -= vDataW;
	}
	fclose(fp);

LB_END:
	if(szLine != NULL){
		free(szLine);
	}
	return vRet;
}

int Bmp_ToFile(const char *strName, int vClrBits, int vWidth, int vHeight, unsigned char *szData)
{
	int vRet = 0;

	if(vClrBits == 1){
		vRet = Bmp1_ToFile(strName, vWidth, vHeight, szData);
	}
	else if(vClrBits == 8){
		vRet = Bmp8_ToFile(strName, vWidth, vHeight, szData);
	}
	else if(vClrBits == 16){
		vRet = Bmp16_ToFile(strName, vWidth, vHeight, szData);
	}
	else if(vClrBits == 24){
		vRet = Bmp24_ToFile(strName, vWidth, vHeight, szData);
	}
	else{
		vRet = 1;
	}

	return vRet;
}

