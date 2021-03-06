/*******************************************************************************
	File:		UAudioFunc.cpp

	Contains:	The utility for audio operation implement file.

	Written by:	Fenger King

	Change History (most recent first):
	2014-05-01		Fenger			Create file

*******************************************************************************/
#ifndef __UAudioFunc_H__
#define __UAudioFunc_H__

#include "voAudio.h"
#include "voAAC.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define  MAXNUM_SAMPLE_RATES  12
static const int AACSampRateTab[MAXNUM_SAMPLE_RATES] = {
	96000, 88200, 64000, 48000, 44100, 32000, 
	24000, 22050, 16000, 12000, 11025,  8000
};


typedef struct{
	VO_S32               nSampleRate;             /* Sample rate */
	VO_S32               nChannels;               /* Channels count */
	VO_S32               nSampleBits;             /* Bits per sample */
	VO_S32               nProfiles;               /* Codec profile */
	VO_S32               nFrameType;              /* Frame type, such as: AAC ADTS or ADIF */
} YY_AUDIO_HEADDATAINFO;

typedef struct
{
	VO_U8  element_instance_tag;
	VO_U8  object_type;
	VO_U8  sampling_frequency_index;
	VO_U8  num_front_channel_elements;
	VO_U8  num_side_channel_elements;
	VO_U8  num_back_channel_elements;
	VO_U8  num_lfe_channel_elements;
	VO_U8  num_assoc_data_elements;
	VO_U8  num_valid_cc_elements;
	VO_U8  mono_mixdown_present;
	VO_U8  mono_mixdown_element_number;
	VO_U8  stereo_mixdown_present;
	VO_U8  stereo_mixdown_element_number;
	VO_U8  matrix_mixdown_idx_present;
	VO_U8  matrix_mixdown_idx;
	VO_U8  pseudo_surround_enable;
	VO_U8  front_element_is_cpe[16];
	VO_U8  front_element_tag_select[16];
	VO_U8  side_element_is_cpe[16];
	VO_U8  side_element_tag_select[16];
	VO_U8  back_element_is_cpe[16];
	VO_U8  back_element_tag_select[16];
	VO_U8  lfe_element_tag_select[16];
	VO_U8  assoc_data_element_tag_select[16];
	VO_U8  cc_element_is_ind_sw[16];
	VO_U8  valid_cc_element_tag_select[16];
	VO_U8  comment_field_bytes;
	//output value
	VO_U8  num_front_channels;
	VO_U8  num_side_channels;
	VO_U8  num_back_channels;
	VO_U8  num_lfe_channels;
	VO_U8  channels;
}YYADIF_CONFIG;

typedef struct
{
	VO_U32 adif_id;
	VO_U8  copyright_id_present;
	VO_S8  copyright_id[9];//72 bits
	VO_U8  original_copy;
	VO_U8  home;
	VO_U8  bitstream_type;
	VO_U32 bitrate;
	VO_U8  num_program_config_elements;
	VO_U32 adif_buffer_fullness;
	YYADIF_CONFIG pce[16];
} YYADIF_INFO;


typedef struct
{
	VO_U16 syncword;
	VO_U8  ID;
	VO_U8  layer;
	VO_U8  protection_absent;
	VO_U8  profile;
	VO_U8  sampling_frequency_index;
	VO_U8  private_bit;
	VO_U8  channel_configuration;
	VO_U8  original;
	VO_U8  home;
	VO_U8  copyright_identification_bit;
	VO_U8  copyright_identification_start;
	VO_U16 frame_length;
	VO_U16 adts_buffer_fullness;
	VO_U8  number_of_raw_data_blocks_in_frame;
	VO_U16 crc_check;	
} YYATDS_INFO;

typedef enum {
	VOMPEG1  = 0,
	VOMPEG2  = 1,
	VOMPEG25 = 2,
	YYMP3VERSMAX = VO_MAX_ENUM_VALUE
} YYMP3VERS;

typedef enum {
	VOLAYER1 = 1,
	VOLAYER2 = 2,
	VOLAYER3 = 3,
	YYMP3LAYERSMAX = VO_MAX_ENUM_VALUE
} YYMP3LAYERS;

typedef enum {
	YYMP3MONO   = 0,
	YYMP3DUAL   = 1,
	YYMP3JOINT  = 2,
	YYMP3STEREO = 3,
	YYMP3CHMODES = VO_MAX_ENUM_VALUE
} YYCHMODES;

typedef struct {
	YYMP3VERS     version;
	YYMP3LAYERS   layer;				
	VO_S32	      crc;					/* CRC flag: 0 = disabled, 1 = enabled */	 
	VO_S32	      bitrate;		
	VO_S32	      samplerate;		
	YYCHMODES     mode;			
	VO_S32	      modeext;	
	VO_S32	      paddingBit;
	VO_S32	      channels;
	VO_S32	      subIndex;
	VO_S32	      crc_check;	
	VO_S32	      crc_target; 
	VO_S32	      headlen;
	VO_S32	      framelen;
} YYMP3HEADINFO;

const int YYMP3SampRateTab[3][3] = {
	{44100, 48000, 32000},		/* MPEG-1 */
	{22050, 24000, 16000},		/* MPEG-2 */
	{11025, 12000,  8000},		/* MPEG-2.5 */
};

const short YYMP3BitrateTab[3][3][15] = {
	{
		/* MPEG-1 */
		{  0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448}, /* Layer 1 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384}, /* Layer 2 */
		{  0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320}, /* Layer 3 */
	},
	{
		/* MPEG-2 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256}, /* Layer 1 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 2 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 3 */
	},
	{
		/* MPEG-2.5 */
		{  0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256}, /* Layer 1 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 2 */
		{  0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160}, /* Layer 3 */
	},
};


/* Get AAC basic head information from bitstream */
VO_U32 yyAudioGetAACHeadInfo (unsigned char * pBuff, int nSize, YY_AUDIO_HEADDATAINFO *pAudioHeadDataInfo);

/* Add ADTS Header to RAW Data frame
 * Use voGetAACHeadInfo function fill the pAudioHeadDataInfo structure, such as 2bytes head data
 * Input: pCodecBuf->Buffer --- one rawData frame
 *        pCodecBuf->Length --- frame length
 * Ouput: pOut->Buffer --- adts heaer + rawdata frame
 *        pOut->Length --- adts header length(7Bytes) + rawData frame length */

VO_U32 yyAudioAddAACADTSHeadPack(unsigned char * pInBuff, int nInSize, 
								 unsigned char * pOutBuff, int & nOutSize, YY_AUDIO_HEADDATAINFO *pAudioHeadDataInfo);

/* Pack Two byte aac header data */
VO_U32 yyAudioAACRAWHeadPack(unsigned char * pInBuff, int nInSize, YY_AUDIO_HEADDATAINFO *pAudioHeadDataInfo);

/* Get Raw Data Offset */
VO_U32 yyAudioAACRAWDataOffset(unsigned char * pInBuff, int nInSize);

/* Re-pack AAC header data 7bytes to 2 bytes */
VO_U32 yyAudioAACHeadData7to2Bytes(unsigned char * pInBuff, int nInSize, unsigned char * pOutBuff, int & nOutSize);

/* Get MP3 basic head information from bitstream */
VO_U32 yyAudioGetMP3HeadInfo(unsigned char * pBuff, int nSize, YY_AUDIO_HEADDATAINFO *pAudioHeadDataInfo);

#ifdef __cplusplus
}
#endif // __cplusplus 

#endif  // __UAudioFunc_H__








