cmake_minimum_required(VERSION 3.1)

project(tests LANGUAGES CXX)

###############################################################################
# Add Tests
###############################################################################

dbg_macro_add_test(test_array "src/test_array.cpp")
dbg_macro_add_test(test_class "src/test_class.cpp")
dbg_macro_add_test(test_enum "src/test_enum.cpp")
dbg_macro_add_test(test_expressions "src/test_expressions.cpp")
dbg_macro_add_test(test_lambda "src/test_lambda.cpp")
dbg_macro_add_test(test_list "src/test_list.cpp")
dbg_macro_add_test(test_literals "src/test_literals.cpp")
dbg_macro_add_test(test_primitives "src/test_primitives.cpp")
dbg_macro_add_test(test_rvalues "src/test_rvalues.cpp")
dbg_macro_add_test(test_side_effects "src/test_side_effects.cpp")
dbg_macro_add_test(test_struct "src/test_struct.cpp")
dbg_macro_add_test(test_vector "src/test_vector.cpp")
