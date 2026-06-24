#include <resources.h>

const char *ApplicationDirectory;
bool initialized_resources = false;

void InitResources(void) {
	ApplicationDirectory = GetApplicationDirectory();
	initialized_resources = true;
}

Image Resources_LoadImage(const char *path) {
	if (!initialized_resources) InitResources();
	return LoadImage(TextFormat("%s%s", ApplicationDirectory, path));
}
