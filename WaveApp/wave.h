#ifndef WAVE_H
#define WAVE_H

#define SPEAKER_FRONT_LEFT 0x1
#define SPEAKER_FRONT_RIGHT 0x2
#define SPEAKER_FRONT_CENTER 0x4
#define SPEAKER_LOW_FREQUENCY 0x8
#define SPEAKER_BACK_LEFT 0x10
#define SPEAKER_BACK_RIGHT 0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER 0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER 0x80
#define SPEAKER_BACK_CENTER 0x100
#define SPEAKER_SIDE_LEFT 0x200
#define SPEAKER_SIDE_RIGHT 0x400
#define SPEAKER_TOP_CENTER 0x800
#define SPEAKER_TOP_FRONT_LEFT 0x1000
#define SPEAKER_TOP_FRONT_CENTER 0x2000
#define SPEAKER_TOP_FRONT_RIGHT 0x4000
#define SPEAKER_TOP_BACK_LEFT 0x8000
#define SPEAKER_TOP_BACK_CENTER 0x10000
#define SPEAKER_TOP_BACK_RIGHT 0x20000
#define SPEAKER_RESERVED 0x80000000

//#define  WAVE_FORMAT_EXTENSIBLE			0xFFFE  /* Microsoft */
#define  WAVE_FORMAT_EXTENSIBLE			0x0001  /* Normal */

typedef unsigned long DWORD;
typedef unsigned short WORD;
/*---------------------------------------------------------*/
typedef struct
 {
	char   RIFF[4];
	DWORD  RiffLength;
	char   WAVE[4];
	char   fmt_[4];
	DWORD  Fmt_Length;
	WORD   formatTag;
	WORD   Channels;
	DWORD  SampFreq;
	DWORD  BytesPerSec;
	WORD   BytesPerSamp;
	WORD   BitsPerSamp;
	WORD   ExtensionLength;
	WORD   wValidBitsPerSample;
	DWORD  dwChannelMask;
	char   SubFormat[16];
	char   fact[4];
	DWORD  FactLength;
	DWORD  dwSampleLength;
	char   data[4];
	DWORD  DataLength;
}WaveHeaderEx;

/*---------------------------------------------------------*/
inline void CreateWaveHeader(WaveHeaderEx &WaveHeader, WORD Nc, DWORD F, DWORD Ns)
{
 // Ns=0;        // Blocks
 // Nc=4;        // Channels
 //	F=96000;     // FS
  DWORD   M=2;    // Bytes per sample


  WaveHeader.RIFF[0]='R';
  WaveHeader.RIFF[1]='I';
  WaveHeader.RIFF[2]='F';
  WaveHeader.RIFF[3]='F';
  WaveHeader.RiffLength=4 + 48 + 12 +(8 + M * Nc * Ns);
  WaveHeader.WAVE[0]='W';
  WaveHeader.WAVE[1]='A';
  WaveHeader.WAVE[2]='V';
  WaveHeader.WAVE[3]='E';
  WaveHeader.fmt_[0]='f';
  WaveHeader.fmt_[1]='m';
  WaveHeader.fmt_[2]='t';
  WaveHeader.fmt_[3]=' ';
  WaveHeader.Fmt_Length=40;
  WaveHeader.formatTag=WAVE_FORMAT_EXTENSIBLE;
  WaveHeader.Channels=Nc;
  WaveHeader.SampFreq=F;
  WaveHeader.BytesPerSec=F * M * Nc;
  WaveHeader.BitsPerSamp=8 * M;
  WaveHeader.BytesPerSamp=M * Nc;
  WaveHeader.ExtensionLength=22;
  WaveHeader.wValidBitsPerSample=8 * M;
  WaveHeader.dwChannelMask= 0;
  if(Nc>2)
    WaveHeader.dwChannelMask=0;// SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT | SPEAKER_BACK_LEFT | SPEAKER_BACK_RIGHT;
  WaveHeader.SubFormat[0]=0x01;
  WaveHeader.SubFormat[1]=0x00;
  WaveHeader.SubFormat[2]=0x00;
  WaveHeader.SubFormat[3]=0x00;
  WaveHeader.SubFormat[4]=0x00;
  WaveHeader.SubFormat[5]=0x00;
  WaveHeader.SubFormat[6]=0x10;
  WaveHeader.SubFormat[7]=0x00;
  WaveHeader.SubFormat[8]=0x80;
  WaveHeader.SubFormat[9]=0x00;
  WaveHeader.SubFormat[10]=0x00;
  WaveHeader.SubFormat[11]=0xAA;
  WaveHeader.SubFormat[12]=0x00;
  WaveHeader.SubFormat[13]=0x38;
  WaveHeader.SubFormat[14]=0x9B;
  WaveHeader.SubFormat[15]=0x71;
  WaveHeader.fact[0]='f';
  WaveHeader.fact[1]='a';
  WaveHeader.fact[2]='c';
  WaveHeader.fact[3]='t';
  WaveHeader.FactLength=4;
  WaveHeader.dwSampleLength=Nc * Ns;
  WaveHeader.data[0]='d';
  WaveHeader.data[1]='a';
  WaveHeader.data[2]='t';
  WaveHeader.data[3]='a';
  WaveHeader.DataLength=M * Nc * Ns;

}

#endif // WAVE_H
