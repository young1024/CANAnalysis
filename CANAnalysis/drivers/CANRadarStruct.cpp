#include "CANRadarStruct.h"

int Str2StuctData(string str, CANRadarMessage &RadarMessage)
{
	if ("" == str)
	{
		return -1;
	}
	char cBuff[16][64] = { "" };
	int ret;
	ret = sscanf(str.c_str(), "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
		cBuff[0], cBuff[1], cBuff[2], cBuff[3], cBuff[4], cBuff[5], cBuff[6], cBuff[7], cBuff[8],
		cBuff[9], cBuff[10], cBuff[11], cBuff[12], cBuff[13], cBuff[14], cBuff[15]);
	if (ret < 12 || ret > 16)
	{
		return -1;
	}
	RadarMessage.iSerialNumber = atoi(cBuff[0]);
	RadarMessage.iChannelNumber = atoi(cBuff[1]);
	RadarMessage.fTimeStamp = atof(cBuff[2]);
	RadarMessage.iTransformDirection = atoi(cBuff[3]);
	RadarMessage.iFrameID = 256 * Char2Int(cBuff[4][5]) + 16 * Char2Int(cBuff[4][6]) + Char2Int(cBuff[4][7]); // atoi(cBuff[4]);
	RadarMessage.iFrameType = atoi(cBuff[5]);
	RadarMessage.iFrameFormat = atoi(cBuff[6]);
	RadarMessage.iFrameLength = atoi(cBuff[7]);
	for (int i = 0; i < RadarMessage.iFrameLength; i++)
	{
		RadarMessage.cFrameData[i] = 16 * Char2Int(cBuff[i + 8][0]) + Char2Int(cBuff[i + 8][1]);
	}

	return 0;
}



int Char2Int(char c)
{
	int b = 0;

	if (c >= '0' && c <= '9')
	{
		return b = c - '0';
	}
	if (c >= 'a' && c <= 'f')
	{
		return b = c - 'a' + 10;
	}
	if (c >= 'A' && c <= 'F')
	{
		return b = c - 'A' + 10;
	}

	return -1;
}



void StuctData2StuctValue201(CANRadarMessage RadarMessage, CANRadarMessage201 &RadarMessageOut)
{
	wtob wb;

	RadarMessageOut.RadarState_NVMReadStatus = RadarMessage.cFrameData[0] >> 7; // 0x0: failed;0x1: successful
	RadarMessageOut.RadarState_NVMwriteStatus = (RadarMessage.cFrameData[0] >> 6) & 0x01; // 0x0: failed;0x1: successful 
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[1];
	RadarMessageOut.RadarState_MaxDistanceCfg = (wb.w >> 6) & 0x3F; // m (200m - 250 m are supported in the standard version)
	RadarMessageOut.RadarState_Persistent_Error = (RadarMessage.cFrameData[2] >> 5) & 0x01; // 0x0: No error;0x1: Persistent error active
	RadarMessageOut.RadarState_Interference = (RadarMessage.cFrameData[2] >> 4) & 0x01; // 0x0: No interference;0x1: Interference detected
	RadarMessageOut.RadarState_Temperature_Error = (RadarMessage.cFrameData[2] >> 3) & 0x01; // 0x0: No error;0x1: Temperature error;active
	RadarMessageOut.RadarState_Temporary_Error = (RadarMessage.cFrameData[2] >> 2) & 0x01; // 0x0: No error;0x1: Temporary error active
	RadarMessageOut.RadarState_Voltage_Error = (RadarMessage.cFrameData[2] >> 1) & 0x01; // 0x0: No error;0x1: Voltage error active
	wb.b[0] = RadarMessage.cFrameData[4];
	wb.b[1] = RadarMessage.cFrameData[3];
	RadarMessageOut.RadarState_RadarPowerCfg = (wb.w >> 7) & 0x07; // 0x0: Standard;0x1: -3dB Tx gain;0x2 : -6dB Tx gain;0x3 : -9dB Tx gain
	RadarMessageOut.RadarState_SortIndex = (RadarMessage.cFrameData[4] >> 4) & 0x07; // 0x0: no sorting;0x1: sorted by range;0x2 : sorted by RCS
	RadarMessageOut.RadarState_SensorID = RadarMessage.cFrameData[4] & 0x07; // Current sensor ID (0-7)
	RadarMessageOut.RadarState_MotionRxState = (RadarMessage.cFrameData[5] >> 6) & 0x03; // 0x0: input ok;0x1 : speed missing;0x2 : yaw rate missing;0x3 : speed and yaw rate missing
	RadarMessageOut.RadarState_SendExtInfoCfg = (RadarMessage.cFrameData[5] >> 5) & 0x01; // 0x0: inactive;0x1: active
	RadarMessageOut.RadarState_SendQualityCfg = (RadarMessage.cFrameData[5] >> 4) & 0x01; // 0x0: inactive;0x1: active
	RadarMessageOut.RadarState_OutputTypeCfg = (RadarMessage.cFrameData[5] >> 2) & 0x01; // 0x0: none;0x1: send objects;0x2 : send clusters
	RadarMessageOut.RadarState_CtrlRelayCfg = (RadarMessage.cFrameData[5] >> 1) & 0x01; // 0x0: inactive;0x1: active
	RadarMessageOut.RadarState_RCS_Threshold = (RadarMessage.cFrameData[7] >> 2) & 0x07; // 0x0 Standard;0x1 High sensitivity
}

void StuctData2StuctValue60A(CANRadarMessage RadarMessage, CANRadarMessage60A &RadarMessageOut)
{
	wtob wb;

	RadarMessageOut = {};
	RadarMessageOut.Object_NofObjects = RadarMessage.cFrameData[0];
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[1];
	RadarMessageOut.Object_MeasCounter = wb.w;
	RadarMessageOut.Object_InterfaceVersion = RadarMessage.cFrameData[3] >> 4;
}


void StuctData2StuctValue60B(CANRadarMessage RadarMessage, CANRadarMessage60B &RadarMessageOut)
{
	wtob wb;

	RadarMessageOut = {};
	RadarMessageOut.Object_ID = RadarMessage.cFrameData[0];
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[1];
	RadarMessageOut.Object_DistLong = (wb.w >> 3) & 0x1FFF;
	wb.b[0] = RadarMessage.cFrameData[3];
	wb.b[1] = RadarMessage.cFrameData[2];
	RadarMessageOut.Object_DistLat = wb.w & 0x07FF;
	wb.b[0] = RadarMessage.cFrameData[5];
	wb.b[1] = RadarMessage.cFrameData[4];
	RadarMessageOut.Object_VrelLong = (wb.w >> 6) & 0x03FF;
	wb.b[0] = RadarMessage.cFrameData[6];
	wb.b[1] = RadarMessage.cFrameData[5];
	RadarMessageOut.Object_VrelLat = (wb.w >> 5) & 0x01FF;
	RadarMessageOut.Object_DynProp = RadarMessage.cFrameData[6] & 0x07;
	RadarMessageOut.Object_RCS = RadarMessage.cFrameData[7];
}

void StuctData2StuctValue60C(CANRadarMessage RadarMessage, CANRadarMessage60C &RadarMessageOut)
{
	wtob wb;

	RadarMessageOut = {};
	RadarMessageOut.Object_ID = RadarMessage.cFrameData[0];
	RadarMessageOut.Obj_DistLong_rms = (RadarMessage.cFrameData[1] >> 3) & 0x1F;
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[1];
	RadarMessageOut.Obj_DistLat_rms = (wb.w >> 6) & 0x1F;
	RadarMessageOut.Obj_VrelLong_rms = (RadarMessage.cFrameData[2] >> 1) & 0x1F;
	wb.b[0] = RadarMessage.cFrameData[3];
	wb.b[1] = RadarMessage.cFrameData[2];
	RadarMessageOut.Obj_VrelLat_rms = (wb.w >> 4) & 0x1F;
	wb.b[0] = RadarMessage.cFrameData[4];
	wb.b[0] = RadarMessage.cFrameData[3];
	RadarMessageOut.Obj_ArelLong_rms = (wb.w >> 7) & 0x1F;
	RadarMessageOut.Obj_ArelLat_rms = (RadarMessage.cFrameData[4] >> 2) & 0x1F;
	wb.b[0] = RadarMessage.cFrameData[5];
	wb.b[0] = RadarMessage.cFrameData[4];
	RadarMessageOut.Obj_Orientation_rms = (wb.w >> 5) & 0x1F;
	RadarMessageOut.Obj_ProbOfExist = (RadarMessage.cFrameData[6] >> 5) & 0x07;
	RadarMessageOut.Obj_MeasState = (RadarMessage.cFrameData[6] >> 2) & 0x07;
}

void StuctData2StuctValue60D(CANRadarMessage RadarMessage, CANRadarMessage60D &RadarMessageOut)
{
	wtob wb;

	RadarMessageOut = {};
	RadarMessageOut.Object_ID = RadarMessage.cFrameData[0];
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[1];
	RadarMessageOut.Object_ArelLong = (wb.w >> 5) & 0x07FF;
	wb.b[0] = RadarMessage.cFrameData[3];
	wb.b[1] = RadarMessage.cFrameData[2];
	RadarMessageOut.Object_ArelLat = (wb.w >> 4) & 0x01FF;
	RadarMessageOut.Object_Class = RadarMessage.cFrameData[4] & 0x07;
	wb.b[0] = RadarMessage.cFrameData[5];
	wb.b[1] = RadarMessage.cFrameData[4];
	RadarMessageOut.Object_OrientationAngel = (wb.w >> 6) & 0x03FF;
	RadarMessageOut.Object_Length = RadarMessage.cFrameData[6];
	RadarMessageOut.Object_Width = RadarMessage.cFrameData[7];
}
