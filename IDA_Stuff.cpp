#include "IDA_Stuff.h"

Tools::Tool Objects::get_tool_from_object(Object object)
{
	switch (object)
	{
	case Objects::SHOVEL:
		return Tools::SHOVEL;
	case Objects::WATERING_CAN:
		return Tools::WATERING_CAN;
	case Objects::FERTILIZER:
		return Tools::FERTILIZER;
	case Objects::BUG_SPRAY:
		return Tools::BUG_SPRAY;
	case Objects::MUSIC_PLAYER:
		return Tools::MUSIC_PLAYER;
	case Objects::CHOCOLATE:
		return Tools::CHOCOLATE;
	case Objects::MOVE_POT:
		return Tools::MOVE_POT;
	case Objects::SELL_PLANT:
		return Tools::SELL_PLANT;
	case Objects::CART:
		return Tools::CART;
	case Objects::WISDOM_TREE_FOOD:
		return Tools::WISDOM_TREE_FOOD;
	default:
		return Tools::Tool(-1);
	}
}
