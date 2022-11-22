#ifndef IDA_STUFF_H
#define IDA_STUFF_H
#include <Windows.h>
namespace Addition_Levels_ID {
	enum Addition_Levels_ID
	{
		Not_Mission = 0,
		Zen_Garden = 0x2B,
		Wisdom_Tree = 0x32,
		Vasebreaker = 0x33,
		To_The_Left = 0x34,
		Third_Vase = 0x35,
		Chain_Reaction = 0x36,
		M_Is_For_Metal = 0x37,
		Scary_Potter = 0x38,
		Hokey_Pokey = 0x39,
		Another_Chain_Reaction = 0x3A,
		Ace_Of_Vase = 0x3B,
		Vasebreaker_Endless = 0x3C,
		I_Zombie = 0x3D,
		I_Zombie_Too = 0x3E,
		Cau_You_Dig_It = 0x3F,
		Totally_Nuts = 0x40,
		Dead_Zoppelin = 0x41,
		Me_Smash = 0x42,
		ZomBoogie = 0x43,
		Three_Hit_Wonder = 0x44,
		All_Your_Brainz_R_Belong_To_Us = 0x45,
		I_Zombie_Endless = 0x46,
	};
};


struct Game_Field
{
	int* vtable;
	int* unknown1;
	int cursor_x_coord;
	int cursor_y_coord;
	int unknown2[2];
	int bInsideWinodw;
	int unknown3[2];
	int choosen_seed_index;
	int plant_table_index;
	int unknown4;
	int HoldingObjectType_or_isHoldingSmth;
};

struct User_Profile
{
	char user_name[16];
	int unknown[5];
	int some_profile_parameter;
};


struct Game_Params
{
	DWORD unknown[510];
	int additional_levels_id;
	int unknown1[12];
	User_Profile* user_profile;
};


struct Game
{
	int unknown[35];
	Game_Params* game_params;
	int unknown1[42];
	Game_Field* game_field;
	int unknown2[10];
	int bIsGamePaused;
	int unknown3[5414];
	int sun_amount;
	int flags_amount;
};


struct Seed_Packet_Vtable
{
	int unknown[517];
	int bFreePlantingHack;
};

struct __declspec(align(4)) Seed_packet
{
	Seed_Packet_Vtable* vtable;
	Game* game;
};

#endif // !IDA_STUFF_H
