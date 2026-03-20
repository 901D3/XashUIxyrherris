#! /usr/bin/env python
# encoding: utf-8
# a1batross, mittorn, 2018

from waflib import Logs, Configure
import os

top = "."


def options(opt):
    grp = opt.add_option_group("XashUIxyrherris C++ options")
    return


def configure(conf):
    conf.load("fwgslib cxx11")

    nortti = {"msvc": ["/GR-"], "default": ["-fno-rtti"]}
    conf.env.append_unique(
        "CXXFLAGS", conf.get_flags_by_compiler(nortti, conf.env.COMPILER_CC)
    )


def build(bld):
    source = bld.path.ant_glob(
        [
            "*.cpp",
            "ContactToEngine/*.cpp",
            "Data/*.cpp",
            "src/**/*.cpp",
        ]
    )

    includes = [
        ".",
        "ContactToEngine/",
        "src/",
        "sdk_includes/",
        "sdk_includes/common",
        "sdk_includes/engine",
        "sdk_includes/pm_shared",
        "sdk_includes/public",
    ]

    bld.shlib(
        source=source,
        target="menu",
        includes=includes,
        use="werror FT2 GDI32 USER32",
        install_path=bld.env.LIBDIR,
        cmake_skip=True,
    )
