
DEP_NETBSD_PATH := netbsd
DEP_LIBC_PATH := picolibc
DEP_MKT_PATH := microkit
DEP_SDDF_PATH := api/sDDF
DEP_COMPILER_PATH := compiler

.PHONY: get
get: dep-get

.PHONY: dep-get
dep-get:
	make -C ${DEP_NETBSD_PATH} get
	make -C ${DEP_LIBC_PATH} get
	make -C ${DEP_MKT_PATH} get
	cd ../ && cd ${DEP_SDDF_PATH} && git submodule update --init --recursive


clean:
	make -C ${DEP_NETBSD_PATH} clean
	make -C ${DEP_LIBC_PATH} clean
	make -C ${DEP_MKT_PATH} clean

	