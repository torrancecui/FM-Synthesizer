from subprocess import call
import os

os.chdir("build/")
call("cmake --build .", shell=True)


call("../build/UnitTestRunner", shell = True)