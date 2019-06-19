test_dbg_macro: test_dbg_macro.cpp ../dbg.h
	$(CXX) \
		-I ".." \
		-Wall \
		-Wextra \
		-pedantic \
		-std="c++11" \
		-o test_dbg_macro \
		-g \
		test_dbg_macro.cpp

example: example.cpp ../dbg.h
	$(CXX) \
		-I ".." \
		-Wall \
		-Wextra \
		-pedantic \
		-std="c++11" \
		-o example \
		-g \
		example.cpp

test: test_dbg_macro
	./test_dbg_macro
