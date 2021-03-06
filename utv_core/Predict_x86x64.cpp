/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */

#include <myintrin_x86x64.h>

#if !defined(GENERATE_SSE2) && !defined(GENERATE_SSSE3) && !defined(GENERATE_SSE41) && !defined(GENERATE_AVX1) && !defined(GENERATE_AVX2)
#error
#endif

template<class T>
static inline T median(T a, T b, T c)
{
	return max(min(max(a, b), c), min(a, b));
}

template<int F>
static inline void IncrementCounters8(__m128i xmm, uint32_t* pCountTable)
{
#ifdef __SSE4_1__
#if defined(__i386__)
	uint32_t x;

	x = _mm_cvtsi128_si32(xmm);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];

	x = _mm_extract_epi32(xmm, 1);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];

	x = _mm_extract_epi32(xmm, 2);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];

	x = _mm_extract_epi32(xmm, 3);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];
#elif defined(__x86_64__)
	uint64_t x;

	x = _mm_cvtsi128_si64(xmm);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];
	++pCountTable[(x >> 32) & 0xff];
	++pCountTable[(x >> 40) & 0xff];
	++pCountTable[(x >> 48) & 0xff];
	++pCountTable[(x >> 56) & 0xff];

	x = _mm_extract_epi64(xmm, 1);
	++pCountTable[x & 0xff];
	++pCountTable[(x >> 8) & 0xff];
	++pCountTable[(x >> 16) & 0xff];
	++pCountTable[(x >> 24) & 0xff];
	++pCountTable[(x >> 32) & 0xff];
	++pCountTable[(x >> 40) & 0xff];
	++pCountTable[(x >> 48) & 0xff];
	++pCountTable[(x >> 56) & 0xff];
#endif
#endif
}

template<int F>
static inline void IncrementCounters16(__m128i xmm, uint32_t* pCountTable)
{
#ifdef __SSE4_1__
#if defined(__i386__)
	uint32_t x;

	x = _mm_cvtsi128_si32(xmm);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];

	x = _mm_extract_epi32(xmm, 1);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];

	x = _mm_extract_epi32(xmm, 2);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];

	x = _mm_extract_epi32(xmm, 3);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];
#elif defined(__x86_64__)
	uint64_t x;

	x = _mm_cvtsi128_si64(xmm);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];
	++pCountTable[(x >> 32) & 0xffff];
	++pCountTable[(x >> 48) & 0xffff];

	x = _mm_extract_epi64(xmm, 1);
	++pCountTable[x & 0xffff];
	++pCountTable[(x >> 16) & 0xffff];
	++pCountTable[(x >> 32) & 0xffff];
	++pCountTable[(x >> 48) & 0xffff];
#endif
#endif
}


template<int F>
void tuned_PredictCylindricalLeftAndCount8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, uint32_t *pCountTable)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
	for (; p <= pSrcEnd - 16; p += 16, q += 16)
	{
		__m128i value = _mm_loadu_si128((const __m128i *)p);
		//__m128i left = _mm_or_si128(_mm_slli_si128(value, 1), _mm_srli_si128(prev, 15));
		__m128i left = _mm_alignr_epi8(value, prev, 15);

		__m128i error = _mm_sub_epi8(value, left);
		_mm_storeu_si128((__m128i *)q, error);
		prev = value;

		IncrementCounters8<F>(error, pCountTable);
	}
#endif
	for (; p < pSrcEnd; p++, q++)
	{
		*q = *p - *(p - 1);
		++pCountTable[*q];
	}
}

#ifdef GENERATE_SSE41
template void tuned_PredictCylindricalLeftAndCount8<CODEFEATURE_SSE41>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, uint32_t *pCountTable);
#endif

#ifdef GENERATE_AVX1
template void tuned_PredictCylindricalLeftAndCount8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, uint32_t *pCountTable);
#endif


template<int F>
void tuned_RestoreCylindricalLeft8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
	for (; p <= pSrcEnd - 32; p += 32, q += 32)
	{
		__m128i s0 = _mm_loadu_si128((const __m128i *)p);
		__m128i s1 = _mm_loadu_si128((const __m128i *)(p+16));

		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 1));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 1));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 2));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 2));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 4));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 4));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 8));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 8));
		s0 = _mm_add_epi8(s0, prev);
		s1 = _mm_add_epi8(s1, _mm_shuffle_epi8(s0, _mm_set1_epi8(15)));
		_mm_storeu_si128((__m128i *)q, s0);
		_mm_storeu_si128((__m128i *)(q+16), s1);
		prev = _mm_shuffle_epi8(s1, _mm_set1_epi8(15));
	}
#endif
	for (; p < pSrcEnd; p++, q++)
	{
		*q = *(q - 1) + *p;
	}
}

#ifdef GENERATE_SSSE3
template void tuned_RestoreCylindricalLeft8<CODEFEATURE_SSSE3>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd);
#endif

#ifdef GENERATE_AVX1
template void tuned_RestoreCylindricalLeft8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd);
#endif


template<int F>
void tuned_PredictCylindricalLeftAndCount10(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd, uint32_t *pCountTable)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi16(CSymbolBits<10>::midval);

#ifdef __SSSE3__
	for (; p <= pSrcEnd - 8; p += 8, q += 8)
	{
		__m128i value = _mm_loadu_si128((const __m128i *)p);
		__m128i left = _mm_alignr_epi8(value, prev, 14);

		__m128i error = _mm_and_si128(_mm_sub_epi16(value, left), _mm_set1_epi16(CSymbolBits<10>::maskval));
		_mm_storeu_si128((__m128i *)q, error);
		prev = value;

		IncrementCounters16<F>(error, pCountTable);
	}
#endif
	for (; p < pSrcEnd; p++, q++)
	{
		*q = (*p - *(p - 1)) & CSymbolBits<10>::maskval;
		++pCountTable[*q];
	}
}

#ifdef GENERATE_SSE41
template void tuned_PredictCylindricalLeftAndCount10<CODEFEATURE_SSE41>(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd, uint32_t *pCountTable);
#endif

#ifdef GENERATE_AVX1
template void tuned_PredictCylindricalLeftAndCount10<CODEFEATURE_AVX1>(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd, uint32_t *pCountTable);
#endif


template<int F>
void tuned_RestoreCylindricalLeft10(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi16(CSymbolBits<10>::midval);

#ifdef __SSSE3__
	for (; p <= pSrcEnd - 16; p += 16, q += 16)
	{
		__m128i s0 = _mm_loadu_si128((const __m128i *)p);
		__m128i s1 = _mm_loadu_si128((const __m128i *)(p + 8));

		s0 = _mm_add_epi16(s0, _mm_slli_si128(s0, 2));
		s1 = _mm_add_epi16(s1, _mm_slli_si128(s1, 2));
		s0 = _mm_add_epi16(s0, _mm_slli_si128(s0, 4));
		s1 = _mm_add_epi16(s1, _mm_slli_si128(s1, 4));
		s0 = _mm_add_epi16(s0, _mm_slli_si128(s0, 8));
		s1 = _mm_add_epi16(s1, _mm_slli_si128(s1, 8));
		s0 = _mm_add_epi16(s0, prev);
		s1 = _mm_add_epi16(s1, _mm_shuffle_epi8(s0, _mm_set2_epi8(15, 14)));
		s0 = _mm_and_si128(s0, _mm_set1_epi16(CSymbolBits<10>::maskval));
		s1 = _mm_and_si128(s1, _mm_set1_epi16(CSymbolBits<10>::maskval));
		_mm_storeu_si128((__m128i *)q, s0);
		_mm_storeu_si128((__m128i *)(q + 8), s1);
		prev = _mm_shuffle_epi8(s1, _mm_set2_epi8(15, 14));
	}
#endif
	for (; p < pSrcEnd; p++, q++)
	{
		*q = (*(q - 1) + *p) & CSymbolBits<10>::maskval;
	}
}

#ifdef GENERATE_SSSE3
template void tuned_RestoreCylindricalLeft10<CODEFEATURE_SSSE3>(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd);
#endif

#ifdef GENERATE_AVX1
template void tuned_RestoreCylindricalLeft10<CODEFEATURE_AVX1>(uint16_t *pDst, const uint16_t *pSrcBegin, const uint16_t *pSrcEnd);
#endif


template<int F>
void tuned_PredictCylindricalWrongMedianAndCount8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);
	__m128i topprev;

#ifdef __SSSE3__
	for (; p <= pSrcBegin + cbStride - 16; p += 16, q += 16)
	{
		__m128i value = _mm_loadu_si128((const __m128i *)p);
		__m128i left = _mm_alignr_epi8(value, prev, 15);

		__m128i error = _mm_sub_epi8(value, left);
		_mm_storeu_si128((__m128i *)q, error);
		prev = value;

		IncrementCounters8<F>(error, pCountTable);
	}
#endif
	for (; p < pSrcBegin + cbStride; p++, q++)
	{
		*q = *p - *(p - 1);
		++pCountTable[*q];
	}

	prev = _mm_set1_epi8((char)0x80);
	topprev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
	for (; p <= pSrcEnd - 16; p += 16, q += 16)
	{
		__m128i value = _mm_loadu_si128((const __m128i *)p);
		__m128i top = _mm_loadu_si128((const __m128i *)(p - cbStride));
		__m128i left = _mm_alignr_epi8(value, prev, 15);
		__m128i topleft = _mm_alignr_epi8(top, topprev, 15);
		__m128i grad = _mm_sub_epi8(_mm_add_epi8(left, top), topleft);
		__m128i pred = _mm_max_epu8(_mm_min_epu8(_mm_max_epu8(left, top), grad), _mm_min_epu8(left, top));

		__m128i error = _mm_sub_epi8(value, pred);
		_mm_storeu_si128((__m128i *)q, error);
		prev = value;
		topprev = top;

		IncrementCounters8<F>(error, pCountTable);
	}
#endif
	for (; p < pSrcEnd; p++, q++)
	{
		*q = *p - median<uint8_t>(*(p - 1), *(p - cbStride), *(p - 1) + *(p - cbStride) - *(p - cbStride - 1));
		++pCountTable[*q];
	}
}

#ifdef GENERATE_SSE41
template void tuned_PredictCylindricalWrongMedianAndCount8<CODEFEATURE_SSE41>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
#endif

#ifdef GENERATE_AVX1
template void tuned_PredictCylindricalWrongMedianAndCount8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
#endif


template<int F>
void tuned_RestoreCylindricalWrongMedian8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
	for (; p <= pSrcBegin + cbStride - 32; p += 32, q += 32)
	{
		__m128i s0 = _mm_loadu_si128((const __m128i *)p);
		__m128i s1 = _mm_loadu_si128((const __m128i *)(p + 16));

		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 1));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 1));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 2));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 2));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 4));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 4));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 8));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 8));
		s0 = _mm_add_epi8(s0, prev);
		s1 = _mm_add_epi8(s1, _mm_shuffle_epi8(s0, _mm_set1_epi8(15)));
		_mm_storeu_si128((__m128i *)q, s0);
		_mm_storeu_si128((__m128i *)(q + 16), s1);
		prev = _mm_shuffle_epi8(s1, _mm_set1_epi8(15));
	}
#endif
	for (; p < pSrcBegin + cbStride; p++, q++)
	{
		*q = *(q - 1) + *p;
	}

	__m128i left = _mm_setzero_si128();
	__m128i topleft = _mm_setzero_si128();

	for (; p < pSrcEnd; p++, q++)
	{
		__m128i top = _mm_cvtsi32_si128(*(const uint32_t *)(q - cbStride));
		__m128i grad = _mm_add_epi8(left, _mm_sub_epi8(top, topleft));
		__m128i pred = _mm_max_epu8(_mm_min_epu8(_mm_max_epu8(left, top), grad), _mm_min_epu8(left, top));
		__m128i value = _mm_add_epi8(pred, _mm_cvtsi32_si128(*(const uint32_t *)p));
		*q = _mm_cvtsi128_si32(value);
		left = value;
		topleft = top;
	}
}

#ifdef GENERATE_SSSE3
template void tuned_RestoreCylindricalWrongMedian8<CODEFEATURE_SSSE3>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif

#ifdef GENERATE_AVX1
template void tuned_RestoreCylindricalWrongMedian8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif


template<int F, bool DoCount>
static inline void tuned_PredictPlanarGradientAndMayCount8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);
	__m128i topprev;

#ifdef __SSSE3__
	for (; p <= pSrcBegin + cbStride - 16; p += 16, q += 16)
	{
		__m128i value = _mm_loadu_si128((const __m128i *)p);
		__m128i left = _mm_alignr_epi8(value, prev, 15);

		__m128i error = _mm_sub_epi8(value, left);
		_mm_storeu_si128((__m128i *)q, error);
		prev = value;

		if (DoCount)
			IncrementCounters8<F>(error, pCountTable);
	}
#endif
	for (; p < pSrcBegin + cbStride; p++, q++)
	{
		*q = *p - *(p - 1);
		if (DoCount)
			++pCountTable[*q];
	}

	for (auto pp = pSrcBegin + cbStride; pp != pSrcEnd; pp += cbStride)
	{
		prev = _mm_set1_epi8((char)0x80);
		topprev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
		for (; p <= pp + cbStride - 16; p += 16, q += 16)
		{
			__m128i value = _mm_loadu_si128((const __m128i *)p);
			__m128i top = _mm_loadu_si128((const __m128i *)(p - cbStride));
			__m128i left = _mm_alignr_epi8(value, prev, 15);
			__m128i topleft = _mm_alignr_epi8(top, topprev, 15);
			__m128i pred = _mm_sub_epi8(_mm_add_epi8(left, top), topleft);

			__m128i error = _mm_sub_epi8(value, pred);
			_mm_storeu_si128((__m128i *)q, error);
			prev = value;
			topprev = top;

			if (DoCount)
				IncrementCounters8<F>(error, pCountTable);
		}
#endif
		for (; p < pp + cbStride; p++, q++)
		{
			*q = *p - (*(p - 1) + *(p - cbStride) - *(p - cbStride - 1));
			if (DoCount)
				++pCountTable[*q];
		}
	}
}

template<int F>
void tuned_PredictPlanarGradientAndCount8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable)
{
	tuned_PredictPlanarGradientAndMayCount8<F, true>(pDst, pSrcBegin, pSrcEnd, cbStride, pCountTable);
}

template<int F>
void tuned_PredictPlanarGradient8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride)
{
	tuned_PredictPlanarGradientAndMayCount8<F, false>(pDst, pSrcBegin, pSrcEnd, cbStride, NULL);
}

#ifdef GENERATE_SSE41
template void tuned_PredictPlanarGradientAndCount8<CODEFEATURE_SSE41>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
template void tuned_PredictPlanarGradient8<CODEFEATURE_SSE41>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif

#ifdef GENERATE_AVX1
template void tuned_PredictPlanarGradientAndCount8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride, uint32_t *pCountTable);
template void tuned_PredictPlanarGradient8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif


template<int F>
void tuned_RestorePlanarGradient8(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride)
{
	auto p = pSrcBegin;
	auto q = pDst;

	__m128i prev = _mm_set1_epi8((char)0x80);

#ifdef __SSSE3__
	for (; p <= pSrcBegin + cbStride - 32; p += 32, q += 32)
	{
		__m128i s0 = _mm_loadu_si128((const __m128i *)p);
		__m128i s1 = _mm_loadu_si128((const __m128i *)(p + 16));

		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 1));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 1));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 2));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 2));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 4));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 4));
		s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 8));
		s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 8));
		s0 = _mm_add_epi8(s0, prev);
		s1 = _mm_add_epi8(s1, _mm_shuffle_epi8(s0, _mm_set1_epi8(15)));
		_mm_storeu_si128((__m128i *)q, s0);
		_mm_storeu_si128((__m128i *)(q + 16), s1);
		prev = _mm_shuffle_epi8(s1, _mm_set1_epi8(15));
	}
#endif
	for (; p < pSrcBegin + cbStride; p++, q++)
	{
		*q = *(q - 1) + *p;
	}

	for (auto pp = pSrcBegin + cbStride; pp != pSrcEnd; pp += cbStride)
	{
		prev = _mm_set1_epi8((char)0);

#ifdef __SSSE3__
		for (; p <= pp + cbStride - 32; p += 32, q += 32)
		{
			__m128i s0 = _mm_loadu_si128((const __m128i *)p);
			__m128i s1 = _mm_loadu_si128((const __m128i *)(p + 16));

			s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 1));
			s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 1));
			s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 2));
			s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 2));
			s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 4));
			s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 4));
			s0 = _mm_add_epi8(s0, _mm_slli_si128(s0, 8));
			s1 = _mm_add_epi8(s1, _mm_slli_si128(s1, 8));
			s0 = _mm_add_epi8(s0, prev);
			s1 = _mm_add_epi8(s1, _mm_shuffle_epi8(s0, _mm_set1_epi8(15)));
			_mm_storeu_si128((__m128i *)q, _mm_add_epi8(s0, _mm_loadu_si128((const __m128i *)(q - cbStride))));
			_mm_storeu_si128((__m128i *)(q + 16), _mm_add_epi8(s1, _mm_loadu_si128((const __m128i *)(q - cbStride + 16))));
			prev = _mm_shuffle_epi8(s1, _mm_set1_epi8(15));
		}
#endif
		for (; p < pp + cbStride; p++, q++)
		{
			*q = *p + (*(q - 1) + *(q - cbStride) - *(q - cbStride - 1));
		}
	}
}

#ifdef GENERATE_SSSE3
template void tuned_RestorePlanarGradient8<CODEFEATURE_SSSE3>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif

#ifdef GENERATE_AVX1
template void tuned_RestorePlanarGradient8<CODEFEATURE_AVX1>(uint8_t *pDst, const uint8_t *pSrcBegin, const uint8_t *pSrcEnd, size_t cbStride);
#endif
