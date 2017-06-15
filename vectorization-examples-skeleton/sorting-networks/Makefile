sorting-network: sorting-network.cpp
	clang -O3 -std=c++1z -O3 -march=corei7-avx sorting-network.cpp

sorting-network.ll: sorting-network.cpp
	clang -O3 -std=c++1z -O3 -march=corei7-avx sorting-network.cpp -S -emit-llvm

sorting-network.s: sorting-network.cpp
	clang -O3 -std=c++1z -O3 -march=corei7-avx sorting-network.cpp -S
