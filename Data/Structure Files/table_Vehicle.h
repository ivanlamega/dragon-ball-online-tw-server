#pragma pack(push,4)
struct sVEHICLE_DATA
{
	char			szModelName[32 + 1];
	BYTE			bySRPType;
	BYTE			bySpeed;
	BYTE			byVehicleType;
	WORD			wRunHeight;
	BYTE			byPersonnel;
};