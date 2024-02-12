all:
	mkdir -p build
	time { cd build; cmake ..; make -j$(shell nproc); }

run:
	cd build; ./Runtime

fclean:
	rm -rf build

re: fclean all
