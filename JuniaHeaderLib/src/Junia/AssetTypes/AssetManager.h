#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H

#include "Asset.h"
#include <vector>

namespace AssetManager {
	std::vector<Asset*> loadedAssets;

	template <typename T>
	static T* loadAssetFromPath(const char* path) {
		T* a = new T();
		loadedAssets.push_back(a);
		a->loadFromPath(path);
		return a;
	}

	static void unloadAll() {
		for (Asset*& a : loadedAssets) a->unload();
		while (!loadedAssets.empty()) delete loadedAssets.back(), loadedAssets.pop_back();
	}
}

#endif // _ASSETMANAGER_H