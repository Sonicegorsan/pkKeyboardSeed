#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
namespace Filesystem
{
	std::string retrieve_config_path();

	inline const std::string PROJECT_NAME{ "pkSeedKeys" };

	inline const std::string CONFIG_NAME{ "pkSeedKeys.ini" };
	
	inline const std::string CONFIG_PATH{retrieve_config_path()};
}

#endif // !FILESYSTEM_H
