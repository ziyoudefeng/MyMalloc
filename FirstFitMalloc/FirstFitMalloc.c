#include "FirstFitMalloc.h"
#include <unistd.h>

void *
first_malloc(unsigned int nbytes)
{
	union header *p, *q;
	unsigned size = (nbytes + sizeof(union header) - 1) / sizeof(union header) + 1;
//	<search for a block that is >= size units>
	q = freep;
	do {
		p = q->s.link;
		if (p->s.size > size) {
			p->s.size -= size;
			p += p->s.size;
			freep = q;
			return p + 1;
		} else if (p->s.size == size) {
			q->s.link = p->s.link;
			freep = q;
			return p + 1;
		} else {
			q = p;
		}
	} while (p != freep);
// end

	if (size < BLOCK) {
	size = BLOCK;
	}
	p = (union header *)sbrk(size * sizeof(union header));
	if (p == (void *)-1) {
		return 0;
	}
	p->s.size = size;
//	<insert this block after freep blcok in free list>
	first_free(p + 1);
// end

	return first_malloc(nbytes);
}

void
first_free(void *ptr) {
	union header *bp = (union header *)ptr - 1, *p;
	if (ptr == 0) {
		return ;
	}
	// find the site
	for (p = freep; ; p = p->s.link) {
		if (((bp > p) && (bp < p->s.link)) || ((p >= p->s.link ) && ((bp > p) || (bp < p->s.link)))) {
			break;
		}
	}

	if (bp + bp->s.size == p->s.link) {
		bp->s.size += p->s.link->s.size;
		bp->s.link = p->s.link->s.link;
	} else {
		bp ->s.link = p->s.link;
	}

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.link = bp->s.link;
	} else {
		p->s.link = bp;
	}
	freep = p;
}

/* <search for a block that is >= size units>
q = freep;
do {
	p = q->s.link;
	if (p->s.size > size) {
		p->s.size -= size;
		p += p->s.size;
		freep = q;
		return p + 1;
	} else if (p->s.size == size) {
		q->s.link = p->s.link;
		freep = q;
		return p + 1;
	} else {
		q = p;
	}
} while (p != freep); */

//<insert this block after freep blcok in free list>
