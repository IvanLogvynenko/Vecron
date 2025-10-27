# CMake generated Testfile for 
# Source directory: /home/ivan/Dev/Projects/vecron
# Build directory: /home/ivan/Dev/Projects/vecron/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[vecron_common_tests]=] "/home/ivan/Dev/Projects/vecron/build/vecron_common_tests")
set_tests_properties([=[vecron_common_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Dev/Projects/vecron/CMakeLists.txt;55;add_test;/home/ivan/Dev/Projects/vecron/CMakeLists.txt;0;")
add_test([=[vecron_tests]=] "/home/ivan/Dev/Projects/vecron/build/vecron_tests")
set_tests_properties([=[vecron_tests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/ivan/Dev/Projects/vecron/CMakeLists.txt;62;add_test;/home/ivan/Dev/Projects/vecron/CMakeLists.txt;0;")
subdirs("common")
