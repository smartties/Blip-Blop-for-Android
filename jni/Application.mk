# ndk-build settings. AGP passes APP_ABI (from abiFilters) and APP_PLATFORM (from minSdk).
APP_STL := c++_static
APP_PLATFORM := android-21

# 16 KB page-size support (required by Play for targetSdk 35+ on 64-bit devices).
APP_SUPPORT_FLEXIBLE_PAGE_SIZES := true
