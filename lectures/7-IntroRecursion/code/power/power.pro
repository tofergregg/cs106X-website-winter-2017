TEMPLATE = app

# Make sure we do not accidentally #include files placed in 'res'
CONFIG += no_include_pwd

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/lib/StanfordCPPLib/*.cpp

HEADERS += $$PWD/lib/StanfordCPPLib/*.h \
    src/ghanoi.h

# set up flags for the compiler and Stanford C++ libraries
QMAKE_CXXFLAGS += -std=c++11 \
    -Wall \
    -Wextra \
    -Wreturn-type \
    -Werror=return-type \
    -Wunreachable-code \
    -Wno-sign-compare \
    -Wno-enum-compare \
    -Wno-dangling-field \
    -g \
    -O0 \
    -DSPL_CONSOLE_WIDTH=750 \
    -DSPL_CONSOLE_HEIGHT=400 \
    -DSPL_CONSOLE_FONTSIZE=16 \
    -DSPL_CONSOLE_ECHO \
    -DSPL_CONSOLE_EXIT_ON_CLOSE \
    -DSPL_CONSOLE_PRINT_EXCEPTIONS \
    -DSPL_CONSOLE_X=999999 \
    -DSPL_CONSOLE_Y=999999 \

INCLUDEPATH += $$PWD/lib/StanfordCPPLib/

# Copies the given files to the destination directory
# The rest of this file defines how to copy the resources folder
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$OUT_PWD

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        !win32 {
            copyResources.commands += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
        }
        win32 {
            copyResources.commands += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
        }
    }
    export(copyResources.commands)
}

!win32 {
    copyToDestdir($$files($$PWD/res/*))
    copyToDestdir($$files($$PWD/lib/*.jar))
}
win32 {
    copyToDestdir($$PWD/res)
    copyToDestdir($$PWD/lib/*.jar)
}

copyResources.input = $$files($$PWD/res/*)
OTHER_FILES = $$files(res/*)
QMAKE_EXTRA_TARGETS += copyResources

POST_TARGETDEPS += copyResources

macx {
    cache()
    QMAKE_MAC_SDK = macosx
}
