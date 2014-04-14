mmap_allocator_test: mmap_allocator_test.o
	clang++ -std=c++11 mmap_allocator_test.o -lgtest -lgtest_main -pthread -o mmap_allocator_test

mmap_allocator_test.o: mmap_allocator_test.cc ../mmap_allocator.h
	clang++ -std=c++11 -c mmap_allocator_test.cc -I..

clean:
	rm *.o mmap_allocator_test
