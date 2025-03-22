
#include "Util.hpp"

unsigned int Util::generateHash65599(const std::string& str)
{
	unsigned int	hash = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		hash = 65599 * hash + str[i];
	}
	return (hash ^ (hash >> 16));
}
