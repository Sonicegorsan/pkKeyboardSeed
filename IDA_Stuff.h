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

namespace Tools
{
	enum Tool
	{
		SHOVEL = 0x5,
		WATERING_CAN = 0x6,
		FERTILIZER = 0x7,
		BUG_SPRAY = 0x8,
		MUSIC_PLAYER = 0x9,
		CHOCOLATE = 0xA,
		MOVE_POT = 0xB,
		SELL_PLANT = 0xC,
		CART = 0xD,
		WISDOM_TREE_FOOD = 0xE,
	};

}
namespace Objects
{
	enum Object
	{
		SEED_PACKET = 0x1,
		SHOVEL = 0x6,
		COB_CANNON_HOMING = 0x8,
		WATERING_CAN = 0x9,
		FERTILIZER = 0xA,
		BUG_SPRAY = 0xB,
		MUSIC_PLAYER = 0xC,
		CHOCOLATE = 0xD,
		MOVE_POT = 0xE,
		SELL_PLANT = 0xF,
		CART = 0x10,
		WISDOM_TREE_FOOD = 0x11,
	};

	Tools::Tool get_tool_from_object(Object object);
}

struct Main_Class;
struct Game;
struct Game_Field;
struct Seed_Packet;
struct Seed_Packet_Storage;
struct User_Profile;
struct Window_Widget;

struct __declspec(align(4)) Main_Class
{
	int unknown[200];
	Window_Widget* window_widget;
	int unknown1[273];
	Game* game;
	int unknown2[35];
	int additional_levels_id;
	int unknown3[12];
	User_Profile* user_profile;
};

struct Game
{
	int unknown[11];
	int paused;
	int draw_field_y_alignment;
	int draw_field_x_alignment;
	int clickable_plane_x;
	int clickable_plane_y;
	int unknown2[19];
	Main_Class* main_class;
	int unknown3[42];
	Game_Field* game_field;
	int unknown4[2];
	Seed_Packet_Storage* seed_packet_storage;
	int unknown5[7];
	int bIsGamePaused;
	int unknown6[5374];
	int sun_amount;
	int flags_amount;
	int unknown7[7];
	int tutorial_phase;
	bool unknown8[105];
	bool shovel_present;
};


struct Seed_Packet
{
	Main_Class* main_class;
	Game* parent_things;
	int seed_slot_offset_x;
	int seed_slot_offset_y;
	int clickable_matrix_x;
	int clickable_matrix_y;
	int isPresent;
	int unknown[2];
	int recharge_counter;
	int recharge_time;
	int slot_index;
	int seed_icon_offset_for_conveyor;
	int plant_id;
	int imitated_plant_id;
	int activate_slot_machine_switch;
	int to_which_plant_switch;
	int unknown1;
	bool recharged;
	bool rechargeble;
	bool unknown2;
	bool unknown3;
	int how_many_times_used;

};

struct Seed_Packet_Storage
{
	int unknown[10];
	Seed_Packet seed_packet[10];
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


struct Window_Widget
{
	int unknown[23];
	Main_Class* main_class;
	int unknown1[11];
	int* active_window_ptr;
	int unknown2[20];
	int window_x_mouse;
	int window_y_mouse;
	int mouse_click_type1;
	int mouse_click_type2;
};





#endif // !IDA_STUFF_H
