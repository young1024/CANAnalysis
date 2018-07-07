#pragma once

#ifndef _CANRADARSTRUCT_H_
#define _CANRADARSTRUCT_H_

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long      DWORD;

typedef union WtoB
{
	unsigned short w;
	BYTE b[2];
}wtob;

typedef struct _CANRadarMessage
{
	int  iSerialNumber = 0;
	int iChannelNumber = 0;
	float fTimeStamp = 0;
	int iTransformDirection = 0; // 0 接收；1 发送
	int iFrameID = 0;
	int iFrameType = 0; // 0 标准帧；1 扩展帧
	int iFrameFormat = 0; // 0 数据帧；1 远程帧
	int iFrameLength = 0;
	char cFrameData[8] = { 0 };
}CANRadarMessage;

typedef struct _CANRadarMessage60A
{
	unsigned char  Object_NofObjects = 0;
	unsigned char Object_InterfaceVersion = 0;
	short Object_MeasCounter = 0;

}CANRadarMessage60A;

typedef struct _CANRadarMessage60B
{
	unsigned char  Object_ID = 0;
	unsigned char  Object_DynProp = 0;
	unsigned char Object_RCS = 0;
	short Object_DistLong = 0;
	short Object_DistLat = 0;
	short Object_VrelLong = 0;
	short Object_VrelLat = 0;

}CANRadarMessage60B;

typedef struct _CANRadarMessage60C
{
	unsigned char  Object_ID = 0;
	unsigned char Obj_DistLong_rms = 0;
	unsigned char Obj_VrelLong_rms = 0;
	unsigned char Obj_DistLat_rms = 0;
	unsigned char Obj_VrelLat_rms = 0;
	unsigned char Obj_ArelLat_rms = 0;
	unsigned char Obj_ArelLong_rms = 0;
	unsigned char Obj_Orientation_rms = 0;
	unsigned char Obj_MeasState = 0;
	unsigned char Obj_ProbOfExist = 0;

}CANRadarMessage60C;

typedef struct _CANRadarMessage60D
{
	unsigned char  Object_ID = 0;
	unsigned char Object_Class = 0;
	unsigned char Object_Length = 0;
	unsigned char Object_Width = 0;
	short Object_ArelLong = 0;
	short Object_ArelLat = 0;
	short Object_OrientationAngel = 0;

}CANRadarMessage60D;

typedef struct _CANRadarMessage60E
{
	unsigned char  Object_ID = 0;
	unsigned char Object_CollDetRegionBitfield = 0;
	unsigned char Reserved1 = 0;
	unsigned char Reserved2 = 0;
}CANRadarMessage60E;

#endif // !_CANRADARSTRUCT_H_
