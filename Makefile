all:
	@echo "test, lib, clean"

test: lib 
	build/test_phobos2390_hex_grid_lib
	
lib:
	@mkdir -p build
	@cd build; cmake ..
	@cd build; make

demo: lib
#	build/demo '(20,5)' '(10,20)'
	build/demo '(25,3)' '(13,25)'
#	build/demo '(30,15)' '(15,30)'

clean:
	@rm -rf build
