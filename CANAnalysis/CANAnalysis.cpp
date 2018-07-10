// CANAnalysis.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>

#include "drivers/CANRadarStruct.h"
#include "drivers/ConstVars.h"

using namespace std;


void Printf60A(CANRadarMessage60A RadarMessage)
{
	cout << endl;
	cout << "******************* \t";
	cout << "Objects:"          << RadarMessage.Object_NofObjects       << "\t";
	cout << "MeasCounter:"      << RadarMessage.Object_MeasCounter      << "\t";
	cout << "InterfaceVersion:" << RadarMessage.Object_InterfaceVersion << "\t";
	cout << " *******************" << endl;
}

void Printf60B(CANRadarMessage60B RadarMessage)
{
	cout.setf(ios::fixed);
	cout << "60B ID:"       << setprecision(0) << RadarMessage.Object_ID   << " ";
	cout << "DistLong:" << setprecision(3) << RadarMessage.Object_DistLong << "\t\t";
	cout << "DistLat:"  << setprecision(3) << RadarMessage.Object_DistLat  << "\t\t";
	cout << "VrelLong:" << setprecision(3) << RadarMessage.Object_VrelLong << "\t\t";
	cout << "VrelLat:"  << setprecision(3) << RadarMessage.Object_VrelLat  << "\t\t";
	cout << "DynProp:"  << setprecision(0) << RadarMessage.Object_DynProp  << "\t\t";
	cout << "RCS:"      << setprecision(6) << RadarMessage.Object_RCS      << endl;
}

void Printf60C(CANRadarMessage60C RadarMessage)
{
	cout.setf(ios::fixed);
	cout << "60C ID:"          << setprecision(0) << RadarMessage.Object_ID           << " ";
	cout << "DistLong_rms:"    << setprecision(3) << RadarMessage.Obj_DistLong_rms    << "\t";
	cout << "DistLat_rms:"     << setprecision(3) << RadarMessage.Obj_DistLat_rms     << "\t";
	cout << "VrelLong_rms:"    << setprecision(3) << RadarMessage.Obj_VrelLong_rms    << "\t";
	cout << "VrelLat_rms:"     << setprecision(3) << RadarMessage.Obj_VrelLat_rms     << "\t";
	cout << "ArelLong_rms:"    << setprecision(3) << RadarMessage.Obj_ArelLong_rms    << "\t";
	cout << "ArelLat_rms:"     << setprecision(3) << RadarMessage.Obj_ArelLat_rms     << "\t";
	cout << "Orientation_rms:" << setprecision(3) << RadarMessage.Obj_Orientation_rms << "\t";
	cout << "MeasState:"       << setprecision(0) << RadarMessage.Obj_MeasState       << "\t";
	cout << "ProbOfExist:"     << setprecision(3) << RadarMessage.Obj_ProbOfExist     << endl;
}

void Printf60D(CANRadarMessage60D RadarMessage)
{
	cout.setf(ios::fixed);
	cout << "60D ID:"           << setprecision(0) << RadarMessage.Object_ID               << " ";
	cout << "ArelLong:"         << setprecision(3) << RadarMessage.Object_ArelLong         << "\t\t";
	cout << "ArelLat:"          << setprecision(3) << RadarMessage.Object_ArelLat          << "\t\t";
	cout << "Width:"            << setprecision(3) << RadarMessage.Object_Width            << "\t\t";
	cout << "Length:"           << setprecision(3) << RadarMessage.Object_Length           << "\t\t";
	cout << "OrientationAngel:" << setprecision(3) << RadarMessage.Object_OrientationAngel << "\t";
	cout << "Class:"            << setprecision(0) << RadarMessage.Object_Class            << endl;
}

void Printf60E(CANRadarMessage60E RadarMessage)
{
	cout << "60E ID:"       << RadarMessage.Object_ID                              << " ";
	cout << "Region:"   << bitset<8>(RadarMessage.Object_CollDetRegionBitfield)    << endl;
}

int main()
{
	ifstream inFile;
	char FileName[256] = "CANMessage.txt";
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
	CANRadarMessage RadarMessage = {};
	CANRadarMessage201 RadarMessage201 = {};
	CANRadarMessage60A RadarMessage60A = {};
	CANRadarMessage60B RadarMessage60B = {};
	CANRadarMessage60C RadarMessage60C = {};
	CANRadarMessage60D RadarMessage60D = {};
	CANRadarMessage60E RadarMessage60E = {};
	while(getline(inFile,str)) // 按行读取,遇到换行符结束
	{
		//cout << str << endl;
		Str2StuctData(str, RadarMessage);

		switch (RadarMessage.iFrameID)
		{
		case 0x201: // 参数输出，长度为8
			StuctData2StuctValue201(RadarMessage, RadarMessage201);
			break;
		case 0x60A: // 目标总属性，长度为4
			StuctData2StuctValue60A(RadarMessage, RadarMessage60A);
			Printf60A(RadarMessage60A);
			break;
		case 0x60B: // 目标属性，长度为8
			StuctData2StuctValue60B(RadarMessage, RadarMessage60B);
			StuctValueTransform60B(RadarMessage60B);
			Printf60B(RadarMessage60B);
 			break;
		case 0x60C: // 目标质量属性，长度为7
			StuctData2StuctValue60C(RadarMessage, RadarMessage60C);
			StuctValueTransform60C(RadarMessage60C);
			Printf60C(RadarMessage60C);
			break;
		case 0x60D: // 目标扩展属性，长度为8
			StuctData2StuctValue60D(RadarMessage, RadarMessage60D);
			StuctValueTransform60D(RadarMessage60D);
			Printf60D(RadarMessage60D);
			break;
		case 0x60E:
			RadarMessage60E = {};
			RadarMessage60E.Object_ID = RadarMessage.cFrameData[0];
			RadarMessage60E.Object_CollDetRegionBitfield = RadarMessage.cFrameData[1];
			//Printf60E(RadarMessage60E);
			break;
		default:
			break;
		}


	}
	system("pause");
    return 0;
}

