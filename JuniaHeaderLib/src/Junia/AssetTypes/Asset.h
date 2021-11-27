#ifndef _ASSET_H
#define _ASSET_H

class Asset {
public:
	virtual ~Asset() {  }
	virtual void loadFromPath(const char* path) {  }
	virtual void unload() {  }
};

#endif // _ASSET_H