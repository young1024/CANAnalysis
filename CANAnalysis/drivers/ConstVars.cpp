#include "ConstVars.h"

void StuctValueTransform60B(CANRadarMessage60B &RadarMessage60B)
{
	RadarMessage60B.Object_DistLong = RadarMessage60B.Object_DistLong * OBJECT_DIST_RES + OBJECT_DIST_LONG_MIN;
	RadarMessage60B.Object_DistLat = RadarMessage60B.Object_DistLat * OBJECT_DIST_RES + OBJECT_DIST_LAT_MIN;
	RadarMessage60B.Object_VrelLong = RadarMessage60B.Object_VrelLong * OBJECT_VREL_RES + OBJECT_VREL_LONG_MIN;
	RadarMessage60B.Object_VrelLat = RadarMessage60B.Object_VrelLat * OBJECT_VREL_RES + OBJECT_VREL_LAT_MIN;
	RadarMessage60B.Object_RCS = pow(10, RadarMessage60B.Object_RCS * CLUSTER_RCS_RES + CLUSTER_RCS); // 由于求解出的单位为dbsm，需转换成平方米
}

void StuctValueTransform60C(CANRadarMessage60C &RadarMessage60C)
{
	RadarMessage60C.Obj_DistLong_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_DistLong_rms];
	RadarMessage60C.Obj_DistLat_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_DistLat_rms];
	RadarMessage60C.Obj_VrelLong_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_VrelLong_rms];
	RadarMessage60C.Obj_VrelLat_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_VrelLat_rms];
	RadarMessage60C.Obj_ArelLong_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_ArelLong_rms];
	RadarMessage60C.Obj_ArelLat_rms = LINEAR_RMS[(int)RadarMessage60C.Obj_ArelLat_rms];
	RadarMessage60C.Obj_Orientation_rms = ANGLE_RMS[(int)RadarMessage60C.Obj_Orientation_rms];
	RadarMessage60C.Obj_ProbOfExist = PROBOFEXIST[(int)RadarMessage60C.Obj_ProbOfExist];

}

void StuctValueTransform60D(CANRadarMessage60D &RadarMessage60D)
{
	RadarMessage60D.Object_ArelLong = RadarMessage60D.Object_ArelLong * OBJECT_AREL_RES + OBJECT_AREL_LONG_MIN;
	RadarMessage60D.Object_ArelLat = RadarMessage60D.Object_ArelLat * OBJECT_AREL_RES + OBJECT_AREL_LAT_MIN;
	RadarMessage60D.Object_OrientationAngel = RadarMessage60D.Object_OrientationAngel * OBJECT_ORIENTATION_ANGEL_RES + OBJECT_ORIENTATION_ANGEL_MIN;
	RadarMessage60D.Object_Length = RadarMessage60D.Object_Length * OBJECT_LENGTH_RES;
	RadarMessage60D.Object_Width = RadarMessage60D.Object_Width * OBJECT_WIDTH_RES;

}