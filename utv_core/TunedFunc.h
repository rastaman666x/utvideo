/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */

#pragma once

#include "Coefficient.h"

#define FEATURESIZE 2
#define DECLARE_TUNEDFUNC_FRAGMENT_HEADER(T) \
	const T *pNext; \
	uint32_t dwRequiredFeatures[FEATURESIZE]


struct TUNEDFUNC_FRAGMENT
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_FRAGMENT);
};


template<int B> struct HUFFMAN_ENCODE_TABLE;
template<int B> struct HUFFMAN_DECODE_TABLE;

struct TUNEDFUNC_PREDICT
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_PREDICT);
	void (*pfnPredictCylindricalWrongMedianAndCount8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
	void (*pfnPredictCylindricalLeftAndCount8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, uint32_t *pCountTable);
	void (*pfnRestoreCylindricalWrongMedian8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
	void(*pfnRestoreCylindricalLeft8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd);
	void(*pfnPredictCylindricalLeftAndCount10)(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd, uint32_t *pCountTable);
	void(*pfnRestoreCylindricalLeft10)(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd);
	void(*pfnPredictPlanarGradientAndCount8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
	void(*pfnPredictPlanarGradient8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
	void(*pfnRestorePlanarGradient8)(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
};

struct TUNEDFUNC_HUFFMAN_ENCODE
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_HUFFMAN_ENCODE);
	size_t (*pfnHuffmanEncode8)(uint8_t *pDstBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, const HUFFMAN_ENCODE_TABLE<8> *pEncodeTable);
	size_t (*pfnHuffmanEncode10)(uint8_t *pDstBegin, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd, const HUFFMAN_ENCODE_TABLE<10> *pEncodeTable);
};

struct TUNEDFUNC_HUFFMAN_DECODE
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_HUFFMAN_DECODE);
	uint8_t* (*pfnHuffmanDecode8)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE<8> *pDecodeTable);
	uint16_t* (*pfnHuffmanDecode10)(uint16_t *pDstBegin, uint16_t *pDstEnd, const uint8_t *pSrcBegin, const HUFFMAN_DECODE_TABLE<10> *pDecodeTable);
};

struct TUNEDFUNC_CONVERT_YUVRGB_COLORSPACE
{
	void (*pfnConvertULY2ToBGR)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertULY2ToBGRX)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertULY2ToRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertULY2ToXRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertBGRToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertBGRXToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertRGBToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertXRGBToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void(*pfnConvertULY4ToBGR)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertULY4ToBGRX)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertULY4ToRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertULY4ToXRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertBGRToULY4)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertBGRXToULY4)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertRGBToULY4)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertXRGBToULY4)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void(*pfnConvertULY0ToBGR)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertULY0ToBGRX)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertULY0ToRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertULY0ToXRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertBGRToULY0)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertBGRXToULY0)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertRGBToULY0)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
	void(*pfnConvertXRGBToULY0)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t dwYPlaneGrossWidth, bool bInterlace);
};

struct TUNEDFUNC_CONVERT_YUVRGB
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_CONVERT_YUVRGB);
	TUNEDFUNC_CONVERT_YUVRGB_COLORSPACE bt601;
	TUNEDFUNC_CONVERT_YUVRGB_COLORSPACE bt709;
};

struct TUNEDFUNC_CONVERT_SHUFFLE
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_CONVERT_SHUFFLE);
	void (*pfnConvertBGRToULRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertBGRXToULRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertXRGBToULRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertBGRAToULRA)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, uint8_t *pABegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertARGBToULRA)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, uint8_t *pABegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertYUYVToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertUYVYToULY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertULRGToBGR)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertULRGToBGRX)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertULRGToXRGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertULRAToBGRA)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, const uint8_t *pABegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertULRAToARGB)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, const uint8_t *pABegin, size_t cbWidth, ssize_t scbStride, size_t cbPlaneWidth);
	void (*pfnConvertULY2ToYUYV)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertULY2ToUYVY)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, size_t cbWidth, ssize_t scbStride, size_t cbYWidth, size_t cbCWidth);
	void (*pfnConvertB48rToUQRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertB64aToUQRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertB64aToUQRA)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, uint8_t *pABegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertUQRGToB48r)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertUQRGToB64a)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertUQRAToB64a)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, const uint8_t *pABegin, size_t cbWidth, ssize_t scbStride);
	void (*pfnConvertV210ToUQY2)(uint8_t *pYBegin, uint8_t *pUBegin, uint8_t *pVBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, unsigned int nWidth, ssize_t scbStride);
	void (*pfnConvertUQY2ToV210)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pYBegin, const uint8_t *pUBegin, const uint8_t *pVBegin, unsigned int nWidth, ssize_t scbStride);
	void (*pfnConvertR210ToUQRG)(uint8_t *pGBegin, uint8_t *pBBegin, uint8_t *pRBegin, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, unsigned int nWidth, ssize_t scbStride);
	void (*pfnConvertUQRGToR210)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pGBegin, const uint8_t *pBBegin, const uint8_t *pRBegin, unsigned int nWidth, ssize_t scbStride);
};

struct TUNEDFUNC_SYMPACK
{
	DECLARE_TUNEDFUNC_FRAGMENT_HEADER(TUNEDFUNC_SYMPACK);
	void (*pfnPack8SymAfterPredictPlanarGradient8)(uint8_t *pPacked, size_t *cbPacked, uint8_t *pControl, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
	void (*pfnUnpack8SymAndRestorePlanarGradient8)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pPacked, const uint8_t *pControl, size_t cbStride);
	void (*pfnPack8SymWithDiff8)(uint8_t *pPacked, size_t *cbPacked, uint8_t *pControl, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, const uint8_t *pPrevBegin, size_t cbStride);
	void (*pfnUnpack8SymWithDiff8)(uint8_t *pDstBegin, uint8_t *pDstEnd, const uint8_t *pPacked, const uint8_t *pControl, const uint8_t *pPrevBegin, size_t cbStride);
};

struct TUNEDFUNC
{
	const TUNEDFUNC_PREDICT *pPredict;
	const TUNEDFUNC_HUFFMAN_ENCODE *pHuffmanEncode;
	const TUNEDFUNC_HUFFMAN_DECODE *pHuffmanDecode;
	const TUNEDFUNC_CONVERT_YUVRGB *pConvertYUVRGB;
	const TUNEDFUNC_CONVERT_SHUFFLE *pConvertShuffle;
	const TUNEDFUNC_SYMPACK *pSymPack;
};

extern TUNEDFUNC tfn;
extern const TUNEDFUNC_PREDICT tfnPredictCPP;
extern const TUNEDFUNC_HUFFMAN_ENCODE tfnHuffmanEncodeCPP;
extern const TUNEDFUNC_HUFFMAN_DECODE tfnHuffmanDecodeCPP;
extern const TUNEDFUNC_CONVERT_YUVRGB tfnConvertYUVRGBCPP;
extern const TUNEDFUNC_CONVERT_SHUFFLE tfnConvertShuffleCPP;
extern const TUNEDFUNC_SYMPACK tfnSymPackCPP;

void ResolveTunedFunc(const TUNEDFUNC *ptfnRoot, const uint32_t *pdwSupportedFeatures);


template<class C> class CYUVTunedFunc;

template<> class CYUVTunedFunc<CBT601Coefficient>
{
public:
	static const TUNEDFUNC_CONVERT_YUVRGB_COLORSPACE &tf() { return tfn.pConvertYUVRGB->bt601; }
};

template<> class CYUVTunedFunc<CBT709Coefficient>
{
public:
	static const TUNEDFUNC_CONVERT_YUVRGB_COLORSPACE &tf() { return tfn.pConvertYUVRGB->bt709; }
};


#define PredictCylindricalWrongMedianAndCount8 tfn.pPredict->pfnPredictCylindricalWrongMedianAndCount8
#define PredictCylindricalLeftAndCount8 tfn.pPredict->pfnPredictCylindricalLeftAndCount8
#define RestoreCylindricalWrongMedian8 tfn.pPredict->pfnRestoreCylindricalWrongMedian8
#define RestoreCylindricalLeft8 tfn.pPredict->pfnRestoreCylindricalLeft8
#define PredictCylindricalLeftAndCount10 tfn.pPredict->pfnPredictCylindricalLeftAndCount10
#define RestoreCylindricalLeft10 tfn.pPredict->pfnRestoreCylindricalLeft10
#define PredictPlanarGradientAndCount8 tfn.pPredict->pfnPredictPlanarGradientAndCount8
#define PredictPlanarGradient8 tfn.pPredict->pfnPredictPlanarGradient8
#define RestorePlanarGradient8 tfn.pPredict->pfnRestorePlanarGradient8

#define HuffmanEncode8 tfn.pHuffmanEncode->pfnHuffmanEncode8
#define HuffmanEncode10 tfn.pHuffmanEncode->pfnHuffmanEncode10
#define HuffmanDecode8 tfn.pHuffmanDecode->pfnHuffmanDecode8
#define HuffmanDecode10 tfn.pHuffmanDecode->pfnHuffmanDecode10

#define ConvertULY2ToBGR(C) CYUVTunedFunc<C>::tf().pfnConvertULY2ToBGR
#define ConvertULY2ToBGRX(C) CYUVTunedFunc<C>::tf().pfnConvertULY2ToBGRX
#define ConvertULY2ToRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY2ToRGB
#define ConvertULY2ToXRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY2ToXRGB
#define ConvertBGRToULY2(C) CYUVTunedFunc<C>::tf().pfnConvertBGRToULY2
#define ConvertBGRXToULY2(C) CYUVTunedFunc<C>::tf().pfnConvertBGRXToULY2
#define ConvertRGBToULY2(C) CYUVTunedFunc<C>::tf().pfnConvertRGBToULY2
#define ConvertXRGBToULY2(C) CYUVTunedFunc<C>::tf().pfnConvertXRGBToULY2

#define ConvertULY4ToBGR(C) CYUVTunedFunc<C>::tf().pfnConvertULY4ToBGR
#define ConvertULY4ToBGRX(C) CYUVTunedFunc<C>::tf().pfnConvertULY4ToBGRX
#define ConvertULY4ToRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY4ToRGB
#define ConvertULY4ToXRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY4ToXRGB
#define ConvertBGRToULY4(C) CYUVTunedFunc<C>::tf().pfnConvertBGRToULY4
#define ConvertBGRXToULY4(C) CYUVTunedFunc<C>::tf().pfnConvertBGRXToULY4
#define ConvertRGBToULY4(C) CYUVTunedFunc<C>::tf().pfnConvertRGBToULY4
#define ConvertXRGBToULY4(C) CYUVTunedFunc<C>::tf().pfnConvertXRGBToULY4

#define ConvertULY0ToBGR(C) CYUVTunedFunc<C>::tf().pfnConvertULY0ToBGR
#define ConvertULY0ToBGRX(C) CYUVTunedFunc<C>::tf().pfnConvertULY0ToBGRX
#define ConvertULY0ToRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY0ToRGB
#define ConvertULY0ToXRGB(C) CYUVTunedFunc<C>::tf().pfnConvertULY0ToXRGB
#define ConvertBGRToULY0(C) CYUVTunedFunc<C>::tf().pfnConvertBGRToULY0
#define ConvertBGRXToULY0(C) CYUVTunedFunc<C>::tf().pfnConvertBGRXToULY0
#define ConvertRGBToULY0(C) CYUVTunedFunc<C>::tf().pfnConvertRGBToULY0
#define ConvertXRGBToULY0(C) CYUVTunedFunc<C>::tf().pfnConvertXRGBToULY0

#define ConvertBGRToULRG tfn.pConvertShuffle->pfnConvertBGRToULRG
#define ConvertRGBToULRG(g, b, r, p, q, w, s, pw) ConvertBGRToULRG(g, r, b, p, q, w, s, pw)
#define ConvertBGRXToULRG tfn.pConvertShuffle->pfnConvertBGRXToULRG
#define ConvertXRGBToULRG tfn.pConvertShuffle->pfnConvertXRGBToULRG
#define ConvertBGRAToULRA tfn.pConvertShuffle->pfnConvertBGRAToULRA
#define ConvertARGBToULRA tfn.pConvertShuffle->pfnConvertARGBToULRA
#define ConvertYUYVToULY2 tfn.pConvertShuffle->pfnConvertYUYVToULY2
#define ConvertUYVYToULY2 tfn.pConvertShuffle->pfnConvertUYVYToULY2
#define ConvertULRGToBGR tfn.pConvertShuffle->pfnConvertULRGToBGR
#define ConvertULRGToRGB(p, q, g, b, r, w, s, pw) ConvertULRGToBGR(p, q, g, r, b, w, s, pw)
#define ConvertULRGToBGRX tfn.pConvertShuffle->pfnConvertULRGToBGRX
#define ConvertULRGToXRGB tfn.pConvertShuffle->pfnConvertULRGToXRGB
#define ConvertULRAToBGRA tfn.pConvertShuffle->pfnConvertULRAToBGRA
#define ConvertULRAToARGB tfn.pConvertShuffle->pfnConvertULRAToARGB
#define ConvertULY2ToYUYV tfn.pConvertShuffle->pfnConvertULY2ToYUYV
#define ConvertULY2ToUYVY tfn.pConvertShuffle->pfnConvertULY2ToUYVY
#define ConvertB48rToUQRG tfn.pConvertShuffle->pfnConvertB48rToUQRG
#define ConvertB64aToUQRG tfn.pConvertShuffle->pfnConvertB64aToUQRG
#define ConvertB64aToUQRA tfn.pConvertShuffle->pfnConvertB64aToUQRA
#define ConvertUQRGToB48r tfn.pConvertShuffle->pfnConvertUQRGToB48r
#define ConvertUQRGToB64a tfn.pConvertShuffle->pfnConvertUQRGToB64a
#define ConvertUQRAToB64a tfn.pConvertShuffle->pfnConvertUQRAToB64a
#define ConvertV210ToUQY2 tfn.pConvertShuffle->pfnConvertV210ToUQY2
#define ConvertUQY2ToV210 tfn.pConvertShuffle->pfnConvertUQY2ToV210
#define ConvertR210ToUQRG tfn.pConvertShuffle->pfnConvertR210ToUQRG
#define ConvertUQRGToR210 tfn.pConvertShuffle->pfnConvertUQRGToR210

#define Pack8SymAfterPredictPlanarGradient8 tfn.pSymPack->pfnPack8SymAfterPredictPlanarGradient8
#define Unpack8SymAndRestorePlanarGradient8 tfn.pSymPack->pfnUnpack8SymAndRestorePlanarGradient8
#define Pack8SymWithDiff8 tfn.pSymPack->pfnPack8SymWithDiff8
#define Unpack8SymWithDiff8 tfn.pSymPack->pfnUnpack8SymWithDiff8
