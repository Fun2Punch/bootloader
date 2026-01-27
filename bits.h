#ifndef _BITS_H
#define _BITS_H

#define _BIT_LEFT(x) ((1ULL) << (x))

#ifdef __ASSEMBLY__

#define _AC(X,Y)         X
#define _AT(T,X)         T

#else
#define __AC(X,Y)	(X##Y)
#define _AC(X,Y) __AC(X,Y)

#endif


#endif
