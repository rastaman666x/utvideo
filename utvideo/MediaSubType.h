/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */

#pragma once

#define DEFINE_FOURCC_MEDIASUBTYPE(fcc, fccname) \
	DEFINE_GUID(MEDIASUBTYPE_##fccname, fcc, 0x0000, 0x0010, 0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71)

DEFINE_FOURCC_MEDIASUBTYPE(FCC('ULRA'), ULRA);
DEFINE_FOURCC_MEDIASUBTYPE(FCC('ULRG'), ULRG);
DEFINE_FOURCC_MEDIASUBTYPE(FCC('ULY0'), ULY0);
DEFINE_FOURCC_MEDIASUBTYPE(FCC('ULY2'), ULY2);

DEFINE_FOURCC_MEDIASUBTYPE(FCC('YUNV'), YUNV);
DEFINE_FOURCC_MEDIASUBTYPE(FCC('UYNV'), UYNV);
DEFINE_FOURCC_MEDIASUBTYPE(FCC('VYUY'), VYUY);