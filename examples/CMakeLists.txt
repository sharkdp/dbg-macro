cmake_minimum_required(VERSION 3.8)

project(examples LANGUAGES CXX)

###############################################################################
# Add Examples
###############################################################################

dbg_macro_add_example(example_factorial "src/example_factorial.cpp")
dbg_macro_add_example(example_gcd "src/example_gcd.cpp")
dbg_macro_add_example(example_temperature "src/example_temperature.cpp")
