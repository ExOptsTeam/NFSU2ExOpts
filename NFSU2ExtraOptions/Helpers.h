#pragma once

inline bool DoesFileExist(char const* path)
{
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}
