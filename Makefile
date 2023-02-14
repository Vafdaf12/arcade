SRCDIR = .
BUILDDIR = build
BUILDDIR_WIN = build-win
NAME_EXE = Arcade

all:
	make configure
	make build

configure:
	cmake -S "${SRCDIR}" -B "${BUILDDIR}"

configure_win:
	cmake -S "${SRCDIR}" -B "${BUILDDIR_WIN}" -DCMAKE_TOOLCHAIN_FILE=Win32MinGW.cmake


build:
	cmake --build "${BUILDDIR}"

build_win32:
	cmake --build "${BUILDDIR_WIN}"

debug:
	cmake -S "${SRCDIR}" -B "${BUILDDIR}" -DCMAKE_BUILD_TYPE=Debug
	make build 
	gdb "./${BUILDDIR}/${NAME_EXE}"

run:
	"./${BUILDDIR}/${NAME_EXE}"

.PHONY: configure build run all
