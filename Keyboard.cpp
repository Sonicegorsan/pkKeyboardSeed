#include <Windows.h>
#include <algorithm>
#include "Keyboard.h"
#include "Filesystem.h"

namespace Keyboard_Storages
{
	namespace Utils
	{

		unsigned int convert_string_to_virtual_code(std::string value,unsigned int default_value)
		{
			if (value.length() == 1)
			{
				unsigned int symbol = value.at(0);
				switch (symbol)
				{
				case '`':
				case '~':
					return VK_OEM_3;
				default:
					return std::toupper(symbol);
				}
			}
			else
			{
				std::transform(value.cbegin(), value.cend(),value.begin(),[](unsigned char c) { return std::toupper(c); });
				if (value == "F1") return VK_F1;
				if (value == "F2") return VK_F2;
				if (value == "F3") return VK_F3;
				if (value == "F4") return VK_F4;
				if (value == "F5") return VK_F5;
				if (value == "F6") return VK_F6;
				if (value == "F7") return VK_F7;
				if (value == "F8") return VK_F8;
				if (value == "F9") return VK_F9;
				if (value == "F10") return VK_F10;
				if (value == "F11") return VK_F11;
				if (value == "F12") return VK_F12;
				return default_value;
			}
		}

		void initialize_heys_storages()
		{

			Keyboard_Storages::Utils::initialize_keys_from_config(Keyboard_Storages::Seeds::seed_keys, Keyboard_Storages::Seeds::Strings::MAIN_GAME_SEGMENT);
			Keyboard_Storages::Utils::initialize_keys_from_config(Keyboard_Storages::Zen_Garden::zen_garden_keys, Keyboard_Storages::Zen_Garden::Strings::ZEN_GARDEN_SEGMENT);
			Keyboard_Storages::Utils::initialize_keys_from_config(Keyboard_Storages::Wisdom_Tree::wisdom_tree_keys, Keyboard_Storages::Wisdom_Tree::Strings::WISDOM_TREE_SEGMENT);
		}

		void initialize_keys_from_config(Keyboard_VK_ID& keys_storage, const std::string& segment_name)
		{
			std::vector<unsigned int> key_values;
			for (auto& key : keys_storage)
			{
				constexpr int PARAMETER_LENGTH{ 16 };
				char config_value[PARAMETER_LENGTH];
				int read_param_length = GetPrivateProfileStringA(segment_name.c_str(), key.first.c_str(), std::to_string(key.second).c_str(), config_value, PARAMETER_LENGTH, Filesystem::CONFIG_PATH.c_str());
				if (config_value == std::to_string(key.second))
					key_values.push_back(key.second);
				else
					key_values.push_back(convert_string_to_virtual_code(config_value,key.second));
			}
			for (int i{}; auto& key : key_values)
			{
				keys_storage.at(i).second = key;
				++i;
			}
		}

		int get_vk_key(const Keyboard_VK_ID& keys_storage,const std::string& action_name)
		{
			for (auto& pair : keys_storage)
			{
				if (pair.first == action_name)
					return pair.second;
			}
			return -1;
		}

		size_t get_index_of_vk(const Keyboard_VK_ID& keys_storage, int vk_key)
		{
			size_t i{};
			for (auto& pair : keys_storage)
			{
				if (pair.second == vk_key)
					return i;
				++i;
			}
			return -1;
		}
		const std::string& get_vk_action_name(const Keyboard_VK_ID& keys_storage, int vk_key)
		{
			for (auto& pair : keys_storage)
			{
				if (pair.second == vk_key)
					return pair.first;
			}
			return "NULL";

		}
		int get_action_id(const std::string& action_name)
		{
			if (action_name == Zen_Garden::Strings::WATERING_CAN)
				return Map_Keys::Tools::WATERING_CAN;
			if (action_name == Zen_Garden::Strings::FERTILIZER)
				return Map_Keys::Tools::FERTILIZER;
			if (action_name == Zen_Garden::Strings::BUG_SPRAY)
				return Map_Keys::Tools::BUG_SPRAY;
			if (action_name == Zen_Garden::Strings::MUSIC_PLAYER)
				return Map_Keys::Tools::MUSIC_PLAYER;
			if (action_name == Zen_Garden::Strings::CHOCOLATE)
				return Map_Keys::Tools::CHOCOLATE;
			if (action_name == Zen_Garden::Strings::MOVE_POT)
				return Map_Keys::Tools::MOVE_POT;
			if (action_name == Zen_Garden::Strings::SELL_PLANT)
				return Map_Keys::Tools::SELL_PLANT;
			if (action_name == Zen_Garden::Strings::CART)
				return Map_Keys::Tools::CART;
			if (action_name == Wisdom_Tree::Strings::WISDOM_TREE_FOOD)
				return Map_Keys::Tools::WISDOM_TREE_FOOD;
			return -1;
		}
	}

	namespace Seeds
	{
		extern Keyboard_VK_ID seed_keys
		{
			{Strings::SEED_SLOT_1,0x31},
			{Strings::SEED_SLOT_2,0x32},
			{Strings::SEED_SLOT_3,0x33},
			{Strings::SEED_SLOT_4,0x34},
			{Strings::SEED_SLOT_5,0x35},
			{Strings::SEED_SLOT_6,0x36},
			{Strings::SEED_SLOT_7,0x37},
			{Strings::SEED_SLOT_8,0x38},
			{Strings::SEED_SLOT_9,0x39},
			{Strings::SEED_SLOT_10,0x30},
			{Strings::SHOVEL,0xC0}
		};
	}
	namespace Zen_Garden
	{
		extern Keyboard_VK_ID zen_garden_keys
		{
			{Strings::WATERING_CAN,0x31},
			{Strings::FERTILIZER,0x32},
			{Strings::BUG_SPRAY,0x33},
			{Strings::MUSIC_PLAYER,0x34},
			{Strings::CHOCOLATE,0x35},
			{Strings::MOVE_POT,0x36},
			{Strings::SELL_PLANT,0x37},
			{Strings::CART,0x38}
		};

	}

	namespace Wisdom_Tree
	{

		extern Keyboard_VK_ID wisdom_tree_keys
		{
			{Strings::WISDOM_TREE_FOOD,0x31}
		};
		
	}

}