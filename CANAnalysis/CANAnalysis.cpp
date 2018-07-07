// CANAnalysis.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CANRadarStruct.h"
#include "drivers/common/byte.h"

using namespace std;

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
	RadarMessage.iFrameID =  256 * Char2Int(cBuff[4][5]) + 16 * Char2Int(cBuff[4][6]) + Char2Int(cBuff[4][7]); // atoi(cBuff[4]);
	RadarMessage.iFrameType = atoi(cBuff[5]);
	RadarMessage.iFrameFormat = atoi(cBuff[6]);
	RadarMessage.iFrameLength = atoi(cBuff[7]);
	for (int i = 0; i < RadarMessage.iFrameLength; i++)
	{
		RadarMessage.cFrameData[i] = 16 * Char2Int(cBuff[i + 8][0]) + Char2Int(cBuff[i + 8][1]);
	}

	return 0;
}


int main()
{
	ifstream inFile;
	char FileName[256] = "CANMessage3.txt";
	inFile.open(FileName);
	if (!inFile)
	{
		cout << "error" << endl;
		system("pause");
	}
	else
	{
		cout << FileName << " open success" << endl;
	}

	string str;
	string strHeader = "00000600";
	CANRadarMessage RadarMessage = {};
	CANRadarMessage60A RadarMessage60A = {};
	CANRadarMessage60B RadarMessage60B = {};
	CANRadarMessage60C RadarMessage60C = {};
	CANRadarMessage60D RadarMessage60D = {};
	CANRadarMessage60E RadarMessage60E = {};
	while(getline(inFile,str)) // 按行读取,遇到换行符结束
	{
		cout << str << endl;
		Str2StuctData(str, RadarMessage);

		wtob wb;

		switch (RadarMessage.iFrameID)
		{
		case 0x201: // 设置参数

			break;
		case 0x60A: // 目标总属性，长度为4
			RadarMessage60A = {};
			RadarMessage60A.Object_NofObjects = RadarMessage.cFrameData[0];
			wb.b[0] = RadarMessage.cFrameData[2];
			wb.b[1] = RadarMessage.cFrameData[1];
			RadarMessage60A.Object_MeasCounter = wb.w;
			RadarMessage60A.Object_InterfaceVersion = RadarMessage.cFrameData[3] >> 4;
			break;
		case 0x60B: // 目标属性，长度为8
			RadarMessage60B = {};
			RadarMessage60B.Object_ID = RadarMessage.cFrameData[0];
			wb.b[0] = RadarMessage.cFrameData[2];
			wb.b[1] = RadarMessage.cFrameData[1];
			RadarMessage60B.Object_DistLong = wb.w >> 3;
			wb.b[0] = RadarMessage.cFrameData[3];
			wb.b[1] = RadarMessage.cFrameData[2];
			RadarMessage60B.Object_DistLat = wb.w & 0x07FF;
			wb.b[0] = RadarMessage.cFrameData[5];
			wb.b[1] = RadarMessage.cFrameData[4];
			RadarMessage60B.Object_VrelLong = wb.w >> 6;
			wb.b[0] = RadarMessage.cFrameData[6];
			wb.b[1] = RadarMessage.cFrameData[5];
			RadarMessage60B.Object_VrelLat = (wb.w >> 5) & 0x01FF;
			RadarMessage60B.Object_DynProp = RadarMessage.cFrameData[6] & 0x07;
			RadarMessage60B.Object_RCS = RadarMessage.cFrameData[7];
			break;
		case 0x60C: // 目标质量属性，长度为7
			RadarMessage60C = {};
			RadarMessage60C.Object_ID = RadarMessage.cFrameData[0];
			RadarMessage60C.Obj_DistLong_rms = (RadarMessage.cFrameData[1] >> 3) & 0x1F;
			wb.b[0] = RadarMessage.cFrameData[2];
			wb.b[1] = RadarMessage.cFrameData[1];
			RadarMessage60C.Obj_DistLat_rms = (wb.w >> 6) & 0x1F;
			RadarMessage60C.Obj_VrelLong_rms = (RadarMessage.cFrameData[2] >> 1) & 0x1F;
			wb.b[0] = RadarMessage.cFrameData[3];
			wb.b[1] = RadarMessage.cFrameData[2];
			RadarMessage60C.Obj_VrelLat_rms = (wb.w >> 4) & 0x1F;
			wb.b[0] = RadarMessage.cFrameData[4];
			wb.b[0] = RadarMessage.cFrameData[3];
			RadarMessage60C.Obj_ArelLong_rms = (wb.w >> 7) & 0x1F;
			RadarMessage60C.Obj_ArelLat_rms = (RadarMessage.cFrameData[4] >> 2) & 0x1F;
			wb.b[0] = RadarMessage.cFrameData[5];
			wb.b[0] = RadarMessage.cFrameData[4];
			RadarMessage60C.Obj_Orientation_rms = (wb.w >> 5) & 0x1F;
			RadarMessage60C.Obj_ProbOfExist = (RadarMessage.cFrameData[6] >> 5) & 0x07;
			RadarMessage60C.Obj_MeasState = (RadarMessage.cFrameData[6] >> 2) & 0x07;
			break;
		case 0x60D: // 目标扩展属性，长度为8
			RadarMessage60D = {};
			RadarMessage60D.Object_ID = RadarMessage.cFrameData[0];
			wb.b[0] = RadarMessage.cFrameData[2];
			wb.b[1] = RadarMessage.cFrameData[1];
			RadarMessage60D.Object_ArelLong = (wb.w >> 5) & 0x7F;
			wb.b[0] = RadarMessage.cFrameData[3];
			wb.b[1] = RadarMessage.cFrameData[2];
			RadarMessage60D.Object_ArelLat = (wb.w >> 4) & 0x1F;
			RadarMessage60D.Object_Class = RadarMessage.cFrameData[4] & 0x07;
			wb.b[0] = RadarMessage.cFrameData[5];
			wb.b[1] = RadarMessage.cFrameData[4];
			RadarMessage60D.Object_OrientationAngel = (wb.w >> 6) & 0x3F;
			RadarMessage60D.Object_Length = RadarMessage.cFrameData[6];
			RadarMessage60D.Object_Width = RadarMessage.cFrameData[7];
			break;
		case 0x60E:
			RadarMessage60E = {};
			RadarMessage60E.Object_ID = RadarMessage.cFrameData[0];
			RadarMessage60E.Object_CollDetRegionBitfield = RadarMessage.cFrameData[1];
			break;
		default:
			break;
		}


	}

    return 0;
}

