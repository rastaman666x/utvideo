/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */

#include "stdafx.h"
#include "utvideo.h"
#include "ULYUV422Codec.h"
#include "Predict.h"
#include "Convert.h"
#include "TunedFunc.h"

template<>
const utvf_t CULYUV422Codec<CBT601Coefficient>::m_utvfEncoderInput[] = {
	UTVF_YUY2, UTVF_YUYV, UTVF_YUNV, UTVF_yuvs,
	UTVF_UYVY, UTVF_UYNV, UTVF_2vuy,
	UTVF_YV16,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CULYUV422Codec<CBT601Coefficient>::m_utvfDecoderOutput[] = {
	UTVF_YUY2, UTVF_YUYV, UTVF_YUNV, UTVF_yuvs,
	UTVF_UYVY, UTVF_UYNV, UTVF_2vuy,
	UTVF_YV16,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CULYUV422Codec<CBT709Coefficient>::m_utvfEncoderInput[] = {
	UTVF_HDYC,
	UTVF_YUY2, UTVF_YUYV, UTVF_YUNV, UTVF_yuvs,
	UTVF_UYVY, UTVF_UYNV, UTVF_2vuy,
	UTVF_YV16,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<>
const utvf_t CULYUV422Codec<CBT709Coefficient>::m_utvfDecoderOutput[] = {
	UTVF_HDYC,
	UTVF_YUY2, UTVF_YUYV, UTVF_YUNV, UTVF_yuvs,
	UTVF_UYVY, UTVF_UYNV, UTVF_2vuy,
	UTVF_YV16,
	UTVF_NFCC_BGR_BU,
	UTVF_NFCC_BGRX_BU,
	UTVF_NFCC_BGR_TD,
	UTVF_NFCC_BGRX_TD,
	UTVF_NFCC_RGB_TD,
	UTVF_NFCC_ARGB_TD,
	UTVF_INVALID,
};

template<class C>
const utvf_t CULYUV422Codec<C>::m_utvfCompressed[] = {
	m_utvfCodec,
	UTVF_INVALID,
};

template<>
CULYUV422Codec<CBT601Coefficient>::CULYUV422Codec(const char *pszInterfaceName) : CUL00Codec("ULY2", pszInterfaceName)
{
}

template<>
CULYUV422Codec<CBT709Coefficient>::CULYUV422Codec(const char *pszInterfaceName) : CUL00Codec("ULH2", pszInterfaceName)
{
}

template<>
const char *CULYUV422Codec<CBT601Coefficient>::GetColorFormatName(void)
{
	return "YUV422 BT.601";
}

template<>
const char *CULYUV422Codec<CBT709Coefficient>::GetColorFormatName(void)
{
	return "YUV422 BT.709";
}

template<class C>
void CULYUV422Codec<C>::CalcPlaneSizes(unsigned int width, unsigned int height)
{
	m_cbPlaneSize[0]          = width * height;
	m_cbPlaneSize[1]          = width * height / 2;
	m_cbPlaneSize[2]          = width * height / 2;

	m_cbPlaneWidth[0]         = width;
	m_cbPlaneWidth[1]         = width / 2;
	m_cbPlaneWidth[2]         = width / 2;

	m_cbPlaneStripeSize[0]    = width;
	m_cbPlaneStripeSize[1]    = width / 2;
	m_cbPlaneStripeSize[2]    = width / 2;

	m_cbPlanePredictStride[0] = width;
	m_cbPlanePredictStride[1] = width / 2;
	m_cbPlanePredictStride[2] = width / 2;
}

template<class C>
void CULYUV422Codec<C>::ConvertToPlanar(uint32_t nBandIndex)
{
	uint8_t *pDstYBegin = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[0];
	uint8_t *pDstUBegin = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[1];
	uint8_t *pDstVBegin = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[2];

	const uint8_t *pSrcBegin = ((uint8_t *)m_pInput) + m_dwRawStripeBegin[nBandIndex] * m_cbRawStripeSize;
	const uint8_t *pSrcEnd   = ((uint8_t *)m_pInput) + m_dwRawStripeEnd[nBandIndex]   * m_cbRawStripeSize;

	switch (m_utvfRaw)
	{
	case UTVF_YUY2:
	case UTVF_YUYV:
	case UTVF_YUNV:
	case UTVF_yuvs:
		ConvertYUYVToULY2(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_UYVY:
	case UTVF_UYNV:
	case UTVF_2vuy:
	case UTVF_HDYC:
		ConvertUYVYToULY2(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGR_BU:
		ConvertBGRToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcEnd - m_cbRawGrossWidth, pSrcBegin - m_cbRawGrossWidth, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGRX_BU:
		ConvertBGRXToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcEnd - m_cbRawGrossWidth, pSrcBegin - m_cbRawGrossWidth, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGR_TD:
		ConvertBGRToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGRX_TD:
		ConvertBGRXToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_RGB_TD:
		ConvertRGBToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_ARGB_TD:
		ConvertXRGBToULY2(C)(pDstYBegin, pDstUBegin, pDstVBegin, pSrcBegin, pSrcEnd, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	}
}

template<class C>
void CULYUV422Codec<C>::ConvertFromPlanar(uint32_t nBandIndex)
{
	const uint8_t *pSrcYBegin = m_pCurFrame->GetPlane(0) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[0];
	const uint8_t *pSrcUBegin = m_pCurFrame->GetPlane(1) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[1];
	const uint8_t *pSrcVBegin = m_pCurFrame->GetPlane(2) + m_dwPlaneStripeBegin[nBandIndex] * m_cbPlaneStripeSize[2];

	uint8_t *pDstBegin = ((uint8_t *)m_pOutput) + m_dwRawStripeBegin[nBandIndex] * m_cbRawStripeSize;
	uint8_t *pDstEnd   = ((uint8_t *)m_pOutput) + m_dwRawStripeEnd[nBandIndex]   * m_cbRawStripeSize;

	switch (m_utvfRaw)
	{
	case UTVF_YUY2:
	case UTVF_YUYV:
	case UTVF_YUNV:
	case UTVF_yuvs:
		ConvertULY2ToYUYV(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_UYVY:
	case UTVF_UYNV:
	case UTVF_2vuy:
	case UTVF_HDYC:
		ConvertULY2ToUYVY(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGR_BU:
		ConvertULY2ToBGR(C)(pDstEnd - m_cbRawGrossWidth, pDstBegin - m_cbRawGrossWidth, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGRX_BU:
		ConvertULY2ToBGRX(C)(pDstEnd - m_cbRawGrossWidth, pDstBegin - m_cbRawGrossWidth, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, -(ssize_t)m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGR_TD:
		ConvertULY2ToBGR(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_BGRX_TD:
		ConvertULY2ToBGRX(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_RGB_TD:
		ConvertULY2ToRGB(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	case UTVF_NFCC_ARGB_TD:
		ConvertULY2ToXRGB(C)(pDstBegin, pDstEnd, pSrcYBegin, pSrcUBegin, pSrcVBegin, m_cbRawNetWidth, m_cbRawGrossWidth, m_cbPlaneWidth[0], m_cbPlaneWidth[1]);
		break;
	}
}

template<class C>
bool CULYUV422Codec<C>::PredictDirect(uint32_t nBandIndex)
{
	if (m_utvfRaw == UTVF_YV16)
	{
		const uint8_t *pSrcBegin[3];

		pSrcBegin[0] = ((const uint8_t *)m_pInput);
		pSrcBegin[2] = pSrcBegin[0] + m_nWidth * m_nHeight;
		pSrcBegin[1] = pSrcBegin[2] + m_nWidth * m_nHeight / 2;

		PredictFromPlanar(nBandIndex, pSrcBegin);

		return true;
	}

	return false;
}

template<class C>
bool CULYUV422Codec<C>::DecodeDirect(uint32_t nBandIndex)
{
	if (m_utvfRaw == UTVF_YV16)
	{
		uint8_t *pDstBegin[3];

		pDstBegin[0] = ((uint8_t *)m_pOutput);
		pDstBegin[2] = pDstBegin[0] + m_nWidth * m_nHeight;
		pDstBegin[1] = pDstBegin[2] + m_nWidth * m_nHeight / 2;

		DecodeToPlanar(nBandIndex, pDstBegin);

		return true;
	}

	return false;
}
