/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id$ */


#define DEFINE_DMOCODEC_CLSID(fcc, fccname) \
	DEFINE_GUID(CLSID_##fccname##DMOEncoder, fcc, 0xE991, 0x460D, 0x84, 0x0B, 0xC1, 0xC6, 0x49, 0x74, 0x57, 0xEF); \
	DEFINE_GUID(CLSID_##fccname##DMODecoder, fcc, 0xD991, 0x460D, 0x84, 0x0B, 0xC1, 0xC6, 0x49, 0x74, 0x57, 0xEF)

DEFINE_DMOCODEC_CLSID(FCC('ULRA'), ULRA);
DEFINE_DMOCODEC_CLSID(FCC('ULRG'), ULRG);
DEFINE_DMOCODEC_CLSID(FCC('ULY0'), ULY0);
DEFINE_DMOCODEC_CLSID(FCC('ULY2'), ULY2);
