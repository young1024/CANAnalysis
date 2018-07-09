#pragma once

#ifndef _CANRADARSTRUCT_H_
#define _CANRADARSTRUCT_H_

#include <string>
using namespace std;

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


typedef struct _CANRadarMessage201
{
	int RadarState_NVMReadStatus = 0;
	int RadarState_NVMwriteStatus = 0;
	int RadarState_MaxDistanceCfg = 0;
	int RadarState_Persistent_Error = 0;
	int RadarState_Interference = 0;
	int RadarState_Temperature_Error = 0;
	int RadarState_Temporary_Error = 0;
	int RadarState_Voltage_Error = 0;
	int RadarState_SensorID = 0;
	int RadarState_SortIndex = 0;
	int RadarState_RadarPowerCfg = 0;
	int RadarState_CtrlRelayCfg = 0;
	int RadarState_OutputTypeCfg = 0;
	int RadarState_SendQualityCfg = 0;
	int RadarState_SendExtInfoCfg = 0;
	int RadarState_MotionRxState = 0;
	int RadarState_RCS_Threshold = 0;

}CANRadarMessage201;

typedef struct _CANRadarMessage60A
{
	int  Object_NofObjects = 0;
	int Object_InterfaceVersion = 0;
	short Object_MeasCounter = 0;

}CANRadarMessage60A;

typedef struct _CANRadarMessage60B
{
	int  Object_ID = 0;
	int Object_DynProp = 0;
	double Object_RCS = 0;
	double Object_DistLong = 0;
	double Object_DistLat = 0;
	double Object_VrelLong = 0;
	double Object_VrelLat = 0;

}CANRadarMessage60B;

typedef struct _CANRadarMessage60C
{
	int  Object_ID = 0;
	double Obj_DistLong_rms = 0;
	double Obj_VrelLong_rms = 0;
	double Obj_DistLat_rms = 0;
	double Obj_VrelLat_rms = 0;
	double Obj_ArelLat_rms = 0;
	double Obj_ArelLong_rms = 0;
	double Obj_Orientation_rms = 0;
	int Obj_MeasState = 0;
	double Obj_ProbOfExist = 0;

}CANRadarMessage60C;

typedef struct _CANRadarMessage60D
{
	int  Object_ID = 0;
	int Object_Class = 0;
	double Object_Length = 0;
	double Object_Width = 0;
	double Object_ArelLong = 0;
	double Object_ArelLat = 0;
	double Object_OrientationAngel = 0;

}CANRadarMessage60D;

typedef struct _CANRadarMessage60E
{
	int  Object_ID = 0;
	int Object_CollDetRegionBitfield = 0;
}CANRadarMessage60E;

int Str2StuctData(string str, CANRadarMessage &RadarMessage);

int Char2Int(char c);

void StuctData2StuctValue201(CANRadarMessage RadarMessage, CANRadarMessage201 &RadarMessageOut);

void StuctData2StuctValue60A(CANRadarMessage RadarMessage, CANRadarMessage60A &RadarMessageOut);
void StuctData2StuctValue60B(CANRadarMessage RadarMessage, CANRadarMessage60B &RadarMessageOut);
void StuctData2StuctValue60C(CANRadarMessage RadarMessage, CANRadarMessage60C &RadarMessageOut);
void StuctData2StuctValue60D(CANRadarMessage RadarMessage, CANRadarMessage60D &RadarMessageOut);


#endif // !_CANRADARSTRUCT_H_
