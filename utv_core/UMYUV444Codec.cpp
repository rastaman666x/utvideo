/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */

#include "stdafx.h"
#include "utvideo.h"
#include "UMYUV444Codec.h"
#include "Predict.h"
#include "TunedFunc.h"
#include "ColorOrder.h"

template<>
const utvf_t CUMYUV444Codec<CBT601Coefficient>::m_utvfEncoderInput[] = {
	UTVF_YV24,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CUMYUV444Codec<CBT601Coefficient>::m_utvfDecoderOutput[] = {
	UTVF_YV24,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CUMYUV444Codec<CBT709Coefficient>::m_utvfEncoderInput[] = {
	UTVF_YV24,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CUMYUV444Codec<CBT709Coefficient>::m_utvfDecoderOutput[] = {
	UTVF_YV24,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<class C>
const utvf_t CUMYUV444Codec<C>::m_utvfCompressed[] = {
	m_utvfCodec,
	UTVF_INVALID,
};

template<>
CUMYUV444Codec<CBT601Coefficient>::CUMYUV444Codec(const char *pszInterfaceName) : CUM00Codec("UMY4", pszInterfaceName)
{
}

template<>
CUMYUV444Codec<CBT709Coefficient>::CUMYUV444Codec(const char *pszInterfaceName) : CUM00Codec("UMH4", pszInterfaceName)
{
}

template<>
const char *CUMYUV444Codec<CBT601Coefficient>::GetColorFormatName(void)
{
	return "YUV444 BT.601";
}

template<>
const char *CUMYUV444Codec<CBT709Coefficient>::GetColorFormatName(void)
{
	return "YUV444 BT.709";
}

template<class C>
void CUMYUV444Codec<C>::CalcPlaneSizes(unsigned int width, unsigned int height)
{
	width = ROUNDUP(width, 64);

	m_cbPlaneSize[0]          = width * height;
	m_cbPlaneSize[1]          = width * height;
	m_cbPlaneSize[2]          = width * height;

	m_cbPlaneWidth[0]         = width;
	m_cbPlaneWidth[1]         = width;
	m_cbPlaneWidth[2]         = width;

	m_cbPlaneStripeSize[0]    = width;
	m_cbPlaneStripeSize[1]    = width;
	m_cbPlaneStripeSize[2]    = width;

	m_cbPlanePredictStride[0] = width;
	m_cbPlanePredictStride[1] = width;
	m_cbPlanePredictStride[2] = width;
}

template<class C>
void CUMYUV444Codec<C>::ConvertToPlanar(uint32_t nBandIndex)
{
	uint8_t *pDstYBegin = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[0];
	uint8_t *pDstUBegin = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[1];
	uint8_t *pDstVBegin = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[2];

	switch (m_utvfRaw)
	{
	case UTVF_YV24:
		{
			const uint8_t *pSrcYBegin, *pSrcVBegin, *pSrcUBegin;
			const uint8_t *pSrcYEnd, *pSrcVEnd, *pSrcUEnd;

			pSrcYBegin = ((uint8_t *)m_pInput);
			pSrcVBegin = pSrcYBegin + m_nWidth * m_nHeight;
			pSrcUBegin = pSrcVBegin + m_nWidth * m_nHeight;

			pSrcYEnd = pSrcYBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;
			pSrcVEnd = pSrcVBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;
			pSrcUEnd = pSrcUBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;

			pSrcYBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;
			pSrcVBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;
			pSrcUBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;

			for (auto p = pSrcYBegin; p != pSrcYEnd; p += m_nWidth, pDstYBegin += m_cbPlaneWidth[0])
			{
				memcpy(pDstYBegin, p, m_nWidth);
				std::fill(pDstYBegin + m_nWidth, pDstYBegin + m_cbPlaneWidth[0], pDstYBegin[m_nWidth - 1]);
			}
			for (auto p = pSrcUBegin; p != pSrcUEnd; p += m_nWidth, pDstUBegin += m_cbPlaneWidth[1])
			{
				memcpy(pDstUBegin, p, m_nWidth);
				std::fill(pDstUBegin + m_nWidth, pDstUBegin + m_cbPlaneWidth[1], pDstUBegin[m_nWidth - 1]);
			}
			for (auto p = pSrcVBegin; p != pSrcVEnd; p += m_nWidth, pDstVBegin += m_cbPlaneWidth[2])
			{
				memcpy(pDstVBegin, p, m_nWidth);
				std::fill(pDstVBegin + m_nWidth, pDstVBegin + m_cbPlaneWidth[2], pDstVBegin[m_nWidth - 1]);
			}
		}
		return;
	}

	const uint8_t *pSrcBegin = ((uint8_t *)m_pInput) + m_dwRawStripeBegin[nBandIndex] * m_cbRawStripeSize;
	const uint8_t *pSrcEnd   = ((uint8_t *)m_pInput) + m_dwRawStripeEnd[nBandIndex]   * m_cbRawStripeSize;

	switch (m_utvfRaw)
	{
	case UTVF_NFCC_BGR_BU:
		ConvertBGRToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcEnd - m_cbRawGrossWidth, pSrcBegin - m_cbRawGrossWidth, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGRX_BU:
		ConvertBGRXToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcEnd - m_cbRawGrossWidth, pSrcBegin - m_cbRawGrossWidth, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGR_TD:
		ConvertBGRToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGRX_TD:
		ConvertBGRXToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_RGB_TD:
		ConvertRGBToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_ARGB_TD:
		ConvertXRGBToULY4(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	}
}

template<class C>
void CUMYUV444Codec<C>::ConvertFromPlanar(uint32_t nBandIndex)
{
	const uint8_t *pSrcYBegin = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[0];
	const uint8_t *pSrcUBegin = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[1];
	const uint8_t *pSrcVBegin = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[2];

	switch (m_utvfRaw)
	{
	case UTVF_YV24:
		{
			uint8_t *pDstYBegin, *pDstVBegin, *pDstUBegin;
			uint8_t *pDstYEnd, *pDstVEnd, *pDstUEnd;

			pDstYBegin = ((uint8_t *)m_pOutput);
			pDstVBegin = pDstYBegin + m_nWidth * m_nHeight;
			pDstUBegin = pDstVBegin + m_nWidth * m_nHeight;

			pDstYEnd = pDstYBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;
			pDstVEnd = pDstVBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;
			pDstUEnd = pDstUBegin + m_dwRawStripeEnd[nBandIndex] * m_nWidth;

			pDstYBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;
			pDstVBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;
			pDstUBegin += m_dwRawStripeBegin[nBandIndex] * m_nWidth;

			for (auto p = pDstYBegin; p != pDstYEnd; p += m_nWidth, pSrcYBegin += m_cbPlaneWidth[0])
				memcpy(p, pSrcYBegin, m_nWidth);
			for (auto p = pDstUBegin; p != pDstUEnd; p += m_nWidth, pSrcUBegin += m_cbPlaneWidth[1])
				memcpy(p, pSrcUBegin, m_nWidth);
			for (auto p = pDstVBegin; p != pDstVEnd; p += m_nWidth, pSrcVBegin += m_cbPlaneWidth[2])
				memcpy(p, pSrcVBegin, m_nWidth);
		}
		return;
	}

	uint8_t *pDstBegin = ((uint8_t *)m_pOutput) + m_dwRawStripeBegin[nBandIndex] * m_cbRawStripeSize;
	uint8_t *pDstEnd   = ((uint8_t *)m_pOutput) + m_dwRawStripeEnd[nBandIndex]   * m_cbRawStripeSize;

	switch (m_utvfRaw)
	{
	case UTVF_NFCC_BGR_BU:
		ConvertULY4ToBGR(C)(pDstEnd - m_cbRawGrossWidth, pDstBegin - m_cbRawGrossWidth, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGRX_BU:
		ConvertULY4ToBGRX(C)(pDstEnd - m_cbRawGrossWidth, pDstBegin - m_cbRawGrossWidth, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGR_TD:
		ConvertULY4ToBGR(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_BGRX_TD:
		ConvertULY4ToBGRX(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_RGB_TD:
		ConvertULY4ToRGB(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	case UTVF_NFCC_ARGB_TD:
		ConvertULY4ToXRGB(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0]);
		break;
	}
}

template<class C>
bool CUMYUV444Codec<C>::PredictDirect(uint32_t nBandIndex)
{
	if (m_utvfRaw == UTVF_YV24 && (m_nWidth % 64) == 0)
	{
		const uint8_t *pSrcBegin[3];

		pSrcBegin[0] = ((const uint8_t *)m_pInput);
		pSrcBegin[2] = pSrcBegin[0] + m_nWidth * m_nHeight;
		pSrcBegin[1] = pSrcBegin[2] + m_nWidth * m_nHeight;

		PredictFromPlanar(nBandIndex, pSrcBegin);

		return true;
	}

	return false;
}

template<class C>
bool CUMYUV444Codec<C>::DecodeDirect(uint32_t nBandIndex)
{
	if (m_utvfRaw == UTVF_YV24 && (m_nWidth % 64) == 0)
	{
		uint8_t *pDstBegin[3];

		pDstBegin[0] = ((uint8_t *)m_pOutput);
		pDstBegin[2] = pDstBegin[0] + m_nWidth * m_nHeight;
		pDstBegin[1] = pDstBegin[2] + m_nWidth * m_nHeight;

		DecodeToPlanar(nBandIndex, pDstBegin);

		return true;
	}

	return false;
}
