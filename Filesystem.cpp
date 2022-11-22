#include <filesystem>
#include "Filesystem.h"

std::string Filesystem::retrieve_config_path()
{
	return std::filesystem::current_path().string() + '/' + CONFIG_NAME;
}