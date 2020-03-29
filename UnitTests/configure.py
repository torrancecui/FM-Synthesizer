import os
from subprocess import call
from sys import platform

if not os.path.exists("../external/FRUT/docs" or "../external/JUCE/doxygen/"):
		os.chdir("../")
		call("git submodule update --init --recursive", shell = True)
		os.chdir("UnitTests")

if not os.path.exists("../external/FRUT/prefix"):
    os.chdir("../external/FRUT/")
    call(["cmake","-E","make_directory","build"])
    os.chdir("build/")
    call(["cmake", "..", "-DCMAKE_INSTALL_PREFIX=../prefix", "-DJUCE_ROOT=../../JUCE"])
    call("cmake --build . --target install", shell = True)
    os.chdir("../../../UnitTests")
    
call("../external/FRUT/prefix/FRUT/bin/Jucer2Reprojucer UnitTestRunner.jucer ../external/FRUT/prefix/FRUT/cmake/Reprojucer.cmake", shell = True)
call(["cmake","-E","make_directory","build"])
os.chdir("build/")

if platform == "linux" or platform == "darwin":
    call("cmake .. -G 'Unix Makefiles'", shell = True)
    
else :
    call("cmake .. -G 'MinGW'", shell = True)
    
    
