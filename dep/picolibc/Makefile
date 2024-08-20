################################################################################
# Makefile
################################################################################

#===========================================================
# Check
#===========================================================
ifndef FORCE
    EXP_INFO := sel4devkit-maaxboard-microkit-docker-dev-env 1 *
    CHK_PATH_FILE := /check.mk
    ifeq ($(wildcard ${CHK_PATH_FILE}),)
        HALT := TRUE
    else
        include ${CHK_PATH_FILE}
    endif
    ifdef HALT
        $(error Expected Environment Not Found: ${EXP_INFO})
    endif
endif

#===========================================================
# Layout
#===========================================================
OUT_PATH := out
LIB_PATH := sel4devkit-maaxboard-microkit-picolibc

#===========================================================
# Usage
#===========================================================
.PHONY: usage
usage: 
	@echo "usage: make <target> [FORCE=TRUE]"
	@echo ""
	@echo "<target> is one off:"
	@echo "get"
	@echo "clean"

#===========================================================
# Target
#===========================================================

.PHONY: get
get: | ${OUT_PATH}
	git -C ${OUT_PATH} clone "git@github.com:sel4devkit/sel4devkit-maaxboard-microkit-picolibc.git" ${LIB_PATH}
	cd ${OUT_PATH}/${LIB_PATH} && ./build_script.sh
	cp ${OUT_PATH}/${LIB_PATH}/picolibc-microkit/picolibc.specs ${OUT_PATH}/${LIB_PATH}/picolibc-microkit/newlib/libc.a ${OUT_PATH}/${LIB_PATH}/picolibc-microkit/newlib/libm.a ${OUT_PATH}
	mv libgcc.a ${OUT_PATH}

${OUT_PATH}:
	mkdir ${OUT_PATH}

.PHONY: clean
clean:
	mv ${OUT_PATH}/libgcc.a . 
	sudo rm -rf ${OUT_PATH}

################################################################################
# End of file
################################################################################
