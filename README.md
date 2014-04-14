# mmap-allocator

A C++ [allocator](http://en.cppreference.com/w/cpp/concept/Allocator) backed by a memory-mapped file.

## Usage

You can create a new allocator via the `mm::Allocator::New` method:

    unique_ptr<mm::Allocator<int>> alloc = mm::Allocator<int>::New("test.storage");

Space can be allocated via `allocate` and `deallocate`:

    int* data = alloc->allocate(10);  // space for 10 ints
    for (int i = 0; i < 10; ++i) {
      data[i] = i * i;
    }
    alloc->deallocate(data, 10);

### STL Containers

Most standard containers can be passed in a custom allocator to use. Given an allocator:

    unique_ptr<mm::Allocator<int>> alloc = mm::Allocator<int>::New("test.storage");

We can construct a `std::vector` that utilizes it like so:

    std::vector<int, mm::Allocator<int>> vec(*alloc);

For convenience, some STL containers have been typdefed:

    mm::vector<int> vec(*alloc);  // same as above

### Setting a default file

You can set a default storage location for **all** allocators via the `mm::SetDefault` method.

    mm::SetDefault("test.storage");

Now all `mm::Allocator`s construct via the default constructor will use the `"test.storage"` file. (Using `Allocator::New` will stil utilize whatever storage you specify).

This is convenient because most standard containers attempt to construct default allocators when not passed on explicitly. Thus, instead of 

    
    unique_ptr<mm::Allocator<int>> alloc = mm::Allocator<int>::New("test.storage");
    mm::vector<int> vec(*alloc);

We can do:

    mm::SetDefault("test.storage");
    mm::vector<int> vec;
