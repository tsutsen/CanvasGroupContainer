#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# Add source files
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "bin/libcanvasgroupcontainer.{}.{}.framework/libcanvasgroupcontainer.{}.{}".format(env["platform"], env["target"], env["platform"], env["target"]),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "bin/libcanvasgroupcontainer{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)