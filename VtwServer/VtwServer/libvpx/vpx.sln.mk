MSBUILD_TOOL := msbuild.exe
found_devenv := $(shell which $(MSBUILD_TOOL) >/dev/null 2>&1 && echo yes)
.nodevenv.once:
	@echo "  * $(MSBUILD_TOOL) not found in path."
	@echo "  * "
	@echo "  * You will have to build all configurations manually using the"
	@echo "  * Visual Studio IDE. To allow make to build them automatically,"
	@echo "  * add the Common7/IDE directory of your Visual Studio"
	@echo "  * installation to your path, eg:"
	@echo "  *   C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE"
	@echo "  * "
	@touch $@
CLEAN-OBJS += $(if $(found_devenv),,.nodevenv.once)

BUILD_TARGETS += $(if $(NO_LAUNCH_DEVENV),,Release_Mixed_Platforms)
clean::
	rm -rf "Mixed Platforms"/"Release"
.PHONY: Release_Mixed_Platforms
ifneq ($(found_devenv),)
Release_Mixed_Platforms: vpx.sln
	$(MSBUILD_TOOL) vpx.sln -m -t:Build \
		-p:Configuration="Release" -p:Platform="Mixed Platforms"
else
Release_Mixed_Platforms: vpx.sln .nodevenv.once
	@echo "  * Skipping build of Release|Mixed Platforms ($(MSBUILD_TOOL) not in path)."
	@echo "  * "
endif

BUILD_TARGETS += $(if $(NO_LAUNCH_DEVENV),,Debug_Mixed_Platforms)
clean::
	rm -rf "Mixed Platforms"/"Debug"
.PHONY: Debug_Mixed_Platforms
ifneq ($(found_devenv),)
Debug_Mixed_Platforms: vpx.sln
	$(MSBUILD_TOOL) vpx.sln -m -t:Build \
		-p:Configuration="Debug" -p:Platform="Mixed Platforms"
else
Debug_Mixed_Platforms: vpx.sln .nodevenv.once
	@echo "  * Skipping build of Debug|Mixed Platforms ($(MSBUILD_TOOL) not in path)."
	@echo "  * "
endif

