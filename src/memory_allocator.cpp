#include "tbb/scalable_allocator.h"

// No retry loop because we assume that scalable_malloc does
// all it takes to allocate the memory, so calling it repeatedly
// will not improve the situation at all
//
// No use of std::new_handler because it cannot be done in portable
// and thread-safe way (see sidebar)
//
// We throw std::bad_alloc() when scalable_malloc returns NULL
//(we return NULL if it is a no-throw implementation)

// Code is from Intel threading building blocks


void* operator new (size_t size) throw (std::bad_alloc)
{
	if (size == 0) size = 1;
	void* ptr = scalable_malloc(size);
	if (ptr == NULL)
	{
		throw std::bad_alloc();
	}
	return ptr;	
}

void* operator new[] (size_t size) throw (std::bad_alloc)
{
	void* ptr = scalable_malloc(size);
	if (ptr == NULL)
	{
		throw std::bad_alloc();
	}
	return ptr;	
}

void* operator new (size_t size, const std::nothrow_t&) throw ()
{	
	if (size == 0) size = 1;
	void* ptr = scalable_malloc(size);
	if (ptr == NULL)
	{
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void* operator new[] (size_t size, const std::nothrow_t&) throw ()
{
	void* ptr = scalable_malloc(size);
	if (ptr == NULL)
	{
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void operator delete (void* ptr) throw ()
{
	if (ptr != NULL)
	{
		scalable_free(ptr);
	}
}

void operator delete[] (void* ptr) throw ()
{
	operator delete (ptr);
}

void operator delete (void* ptr, const std::nothrow_t&) throw ()
{
	if (ptr != NULL)
	{
		scalable_free(ptr);
	}
}

void operator delete[] (void* ptr, const std::nothrow_t&) throw ()
{
	operator delete(ptr);
}