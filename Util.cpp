
#include "Util.hpp"

unsigned int Util::generateHash65599(const char* str)
{
	unsigned int	hash = 0;

	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		hash = 65599 * hash + str[i];
	}
	return (hash ^ (hash >> 16));
}
