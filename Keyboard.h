#pragma once
#include <vector>
#include <string>

namespace Keyboard_Storages
{
	using Keyboard_VK_ID = std::vector<std::pair<std::string, int>>;

	namespace Utils
	{
		void initialize_heys_storages();

		void initialize_keys_from_config(Keyboard_VK_ID& keys_storage,const std::string& branch_name);

		int get_vk_key(const Keyboard_VK_ID& keys_storage,const std::string& action_name);

		size_t get_index_of_vk(const Keyboard_VK_ID& keys_storage,int vk_key);

		const std::string& get_vk_action_name(const Keyboard_VK_ID& keys_storage, int vk_key);

		int get_action_id(const std::string& action_name);
	}

	namespace Seeds
	{
		namespace Strings 
		{
			static inline const std::string MAIN_GAME_SEGMENT{ "MAIN_GAME" };
			static inline const std::string SEED_SLOT_1{ "SEED_SLOT_1" };
			static inline const std::string SEED_SLOT_2{ "SEED_SLOT_2" };
			static inline const std::string SEED_SLOT_3{ "SEED_SLOT_3" };
			static inline const std::string SEED_SLOT_4{ "SEED_SLOT_4" };
			static inline const std::string SEED_SLOT_5{ "SEED_SLOT_5" };
			static inline const std::string SEED_SLOT_6{ "SEED_SLOT_6" };
			static inline const std::string SEED_SLOT_7{ "SEED_SLOT_7" };
			static inline const std::string SEED_SLOT_8{ "SEED_SLOT_8" };
			static inline const std::string SEED_SLOT_9{ "SEED_SLOT_9" };
			static inline const std::string SEED_SLOT_10{ "SEED_SLOT_10" };
			static inline const std::string SHOVEL{ "SHOVEL" };
		}
		extern Keyboard_VK_ID seed_keys;
	}

	namespace Zen_Garden
	{

		namespace Strings
		{
			static inline const std::string ZEN_GARDEN_SEGMENT{ "ZEN_GARDEN" };
			static inline const std::string WATERING_CAN{ "WATERING_CAN" };
			static inline const std::string FERTILIZER{ "FERTILIZER" };
			static inline const std::string BUG_SPRAY{ "BUG_SPRAY" };
			static inline const std::string MUSIC_PLAYER{ "MUSIC_PLAYER" };
			static inline const std::string CHOCOLATE{ "CHOCOLATE" };
			static inline const std::string MOVE_POT{ "MOVE_POT" };
			static inline const std::string SELL_PLANT{ "SELL_PLANT" };
			static inline const std::string CART{ "CART" };
		}
		extern Keyboard_VK_ID zen_garden_keys;
	}

	namespace Wisdom_Tree
	{

		namespace Strings
		{
			static inline const std::string WISDOM_TREE_SEGMENT{ "WISDOM_TREE" };
			static inline const std::string WISDOM_TREE_FOOD{ "WISDOM_TREE_FOOD" };
		}
		extern Keyboard_VK_ID wisdom_tree_keys;

	}

	namespace Map_Keys {
		namespace Slots
		{
			enum Slots
			{
				SEED_SLOT_1,
				SEED_SLOT_2,
				SEED_SLOT_3,
				SEED_SLOT_4,
				SEED_SLOT_5,
				SEED_SLOT_6,
				SEED_SLOT_7,
				SEED_SLOT_8,
				SEED_SLOT_9,
				SEED_SLOT_10,
			};
		}
		namespace Tools
		{
			enum Tools
			{
				SHOVEL = 6,
				WATERING_CAN = 9,
				FERTILIZER = 10,
				BUG_SPRAY = 11,
				MUSIC_PLAYER = 12,
				CHOCOLATE = 13,
				MOVE_POT = 14,
				SELL_PLANT = 15,
				CART = 16,
				WISDOM_TREE_FOOD = 17,
			};
		}
	}

}
