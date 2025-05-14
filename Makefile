prepare:
	cmake -S llvm -B build -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS="clang" -DCMAKE_INSTALL_PREFIX=install/ -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=On -DLLVM_TARGETS_TO_BUILD=X86";"Rune -DLLVM_INCLUDE_TESTS=OFF -DLLVM_INCLUDE_EXAMPLES=OFF

build: prepare
	cd build && make install && cd ..

test: # build
	install/bin/llc _tmp/test.ll -march x86 -o _tmp/test.x86
	echo && echo && echo "========= test.ll, x86 ========="
	cat _tmp/test.x86 && echo && echo
	install/bin/llc _tmp/test.ll -march rune -o _tmp/test.r
	echo && echo && echo "========= test.ll, rune ========="
	cat _tmp/test.r && echo && echo
	install/bin/llc _tmp/test.ll -march rune -o _tmp/test.o -filetype=obj

app: # build
	install/bin/llc _tmp/app.ll -march x86 -o _tmp/app.x86
#	echo && echo && echo "========= app.ll, x86 ========="
#	cat _tmp/app.x86 && echo && echo
	install/bin/llc _tmp/app.ll -march rune -o _tmp/test.r
	echo && echo && echo "========= app.ll, rune ========="
	cat _tmp/app.r && echo && echo
