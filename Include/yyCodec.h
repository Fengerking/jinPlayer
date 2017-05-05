/*******************************************************************************
	File:		yyCodec.h

	Contains:	yy player type define header file.

	Written by:	Fenger King

	Change History (most recent first):
	2013-03-23		Fenger			Create file

*******************************************************************************/
#ifndef __yyCodec_H__
#define __yyCodec_H__

#include "yyType.h"

enum YYCodecID {
    YY_CODEC_ID_NONE,

    // video codecs 
    YY_CODEC_ID_MPEG1VIDEO,
    YY_CODEC_ID_MPEG2VIDEO, 
    YY_CODEC_ID_MPEG4,

    YY_CODEC_ID_H261,
    YY_CODEC_ID_H263,
    YY_CODEC_ID_H264,
    YY_CODEC_ID_H265,

    YY_CODEC_ID_RV10,
    YY_CODEC_ID_RV20,
    YY_CODEC_ID_RV30,
    YY_CODEC_ID_RV40,

    YY_CODEC_ID_MSMPEG4V1,
    YY_CODEC_ID_MSMPEG4V2,
    YY_CODEC_ID_MSMPEG4V3,
    YY_CODEC_ID_WMV1,
    YY_CODEC_ID_WMV2,
    YY_CODEC_ID_WMV3,
    YY_CODEC_ID_VC1,

    YY_CODEC_ID_VP3,
    YY_CODEC_ID_VP5,
    YY_CODEC_ID_VP6,
    YY_CODEC_ID_VP8,
    YY_CODEC_ID_VP9,

    YY_CODEC_ID_FLV1,
    YY_CODEC_ID_DVVIDEO,

    YY_CODEC_ID_MJPEG,
    YY_CODEC_ID_MJPEGB,
    YY_CODEC_ID_LJPEG,
    YY_CODEC_ID_JPEGLS,
    YY_CODEC_ID_JPEG2000,
    YY_CODEC_ID_TIFF,
    YY_CODEC_ID_GIF,

    YY_CODEC_ID_RAWVIDEO,

    // audio codecs 
    YY_CODEC_ID_AMR_NB = 0x12000,
    YY_CODEC_ID_AMR_WB,
    YY_CODEC_ID_MP2,
    YY_CODEC_ID_MP3, 
    YY_CODEC_ID_AAC,
    YY_CODEC_ID_AC3,
    YY_CODEC_ID_DTS,
    YY_CODEC_ID_VORBIS,
    YY_CODEC_ID_DVAUDIO,
    YY_CODEC_ID_WMAV1,
    YY_CODEC_ID_WMAV2,
    YY_CODEC_ID_FLAC,
    YY_CODEC_ID_ALAC,
    YY_CODEC_ID_GSM, 
    YY_CODEC_ID_QCELP,
    YY_CODEC_ID_APE,
    YY_CODEC_ID_WMAVOICE,
    YY_CODEC_ID_WMAPRO,
    YY_CODEC_ID_WMALOSSLESS,
    YY_CODEC_ID_ATRAC3P,
    YY_CODEC_ID_EAC3,
    YY_CODEC_ID_MP1,
    YY_CODEC_ID_G723_1,
    YY_CODEC_ID_G729,

    // various ADPCM codecs 
    YY_CODEC_ID_ADPCM_IMA_QT = 0x14000,
    YY_CODEC_ID_ADPCM_IMA_WAV,
    YY_CODEC_ID_ADPCM_IMA_DK3,
    YY_CODEC_ID_ADPCM_IMA_DK4,
    YY_CODEC_ID_ADPCM_IMA_WS,
    YY_CODEC_ID_ADPCM_IMA_SMJPEG,
    YY_CODEC_ID_ADPCM_MS,
    YY_CODEC_ID_ADPCM_4XM,
    YY_CODEC_ID_ADPCM_XA,
    YY_CODEC_ID_ADPCM_ADX,
    YY_CODEC_ID_ADPCM_EA,
    YY_CODEC_ID_ADPCM_G726,
    YY_CODEC_ID_ADPCM_CT,
    YY_CODEC_ID_ADPCM_SWF,
    YY_CODEC_ID_ADPCM_YAMAHA,
    YY_CODEC_ID_ADPCM_SBPRO_4,
    YY_CODEC_ID_ADPCM_SBPRO_3,
    YY_CODEC_ID_ADPCM_SBPRO_2,
    YY_CODEC_ID_ADPCM_THP,
    YY_CODEC_ID_ADPCM_IMA_AMV,
    YY_CODEC_ID_ADPCM_EA_R1,
    YY_CODEC_ID_ADPCM_EA_R3,
    YY_CODEC_ID_ADPCM_EA_R2,
    YY_CODEC_ID_ADPCM_IMA_EA_SEAD,
    YY_CODEC_ID_ADPCM_IMA_EA_EACS,
    YY_CODEC_ID_ADPCM_EA_XAS,
    YY_CODEC_ID_ADPCM_EA_MAXIS_XA,
    YY_CODEC_ID_ADPCM_IMA_ISS,
    YY_CODEC_ID_ADPCM_G722,
    YY_CODEC_ID_ADPCM_IMA_APC,
    // various PCM
    YY_CODEC_ID_FIRST_AUDIO = 0x15000,     
    YY_CODEC_ID_PCM_S16LE,
    YY_CODEC_ID_PCM_S16BE,
    YY_CODEC_ID_PCM_U16LE,
    YY_CODEC_ID_PCM_U16BE,
    YY_CODEC_ID_PCM_S8,
    YY_CODEC_ID_PCM_U8,
};

#endif // __yyCodec_H__