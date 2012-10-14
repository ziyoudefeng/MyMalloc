MyMalloc
========

几种动态内存分配算法的实现

FirstFitMalloc:

FirstFitMalloc.h:
		keep a linked list of free blocks
		search for the first one that's big enough
		// Free list is sorted in order of increasing addresses so that adjacent free blocks can be coalesced
