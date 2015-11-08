// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_SYSTEM_ANDROID

#include <android/log.h>
#include <sys/time.h>
#include <stdio.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/configuration.h>

#ifdef TB_RUNTIME_DEBUG_INFO

#define  LOG_TAG    "TB"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void TBDebugOut(const char *str)
{
	LOGI("%s", str);
}

#endif // TB_RUNTIME_DEBUG_INFO

AAssetManager *g_pManager = NULL;

void SetAssetManager(AAssetManager *pManager)
{
	g_pManager = pManager;
}

namespace tb {

// == TBSystem ========================================

double TBSystem::GetTimeMS()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec / 1000 + now.tv_sec * 1000;
}

void TBSystem::RescheduleTimer(double fire_time)
{
}

int TBSystem::GetLongClickDelayMS()
{
	return 500;
}

int TBSystem::GetPanThreshold()
{
	return 5 * GetDPI() / 120;
}

int TBSystem::GetPixelsPerLine()
{
	return 40 * GetDPI() / 120;
}

int TBSystem::GetDPI()
{
	AConfiguration *config = AConfiguration_new();
	AConfiguration_fromAssetManager(config, g_pManager);
	int32_t density = AConfiguration_getDensity(config);
	AConfiguration_delete(config);
	if (density == 0 || density == ACONFIGURATION_DENSITY_NONE)
		return 120;
	return density;
}

// == TBFile =====================================

class TBAndroidFile : public TBFile
{
public:
	TBAndroidFile(AAsset* f) : file(f) {}
	virtual ~TBAndroidFile() { AAsset_close(file); }

	virtual long Size()
	{
		return AAsset_getLength(file);
	}
	virtual size_t Read(void *buf, size_t elemSize, size_t count)
	{
		return AAsset_read(file, buf, elemSize * count);
	}
private:
	AAsset *file;
};

TBFile *TBFile::Open(const char *filename, TBFileMode mode)
{
	AAsset *f = nullptr;
	switch (mode)
	{
	case MODE_READ:
		f = AAssetManager_open(g_pManager, filename, AASSET_MODE_UNKNOWN);
		break;
	default:
		break;
	}
	if (!f)
		return nullptr;
	TBAndroidFile *tbf = new TBAndroidFile(f);
	if (!tbf)
		AAsset_close(f);
	return tbf;
}

}; // namespace tb

#endif // TB_SYSTEM_ANDROID
