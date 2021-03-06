/* vi: set sw=4 ts=4: */
/*
 * mknod() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>

int mknod(const char *path, mode_t mode, dev_t dev)
{
	unsigned long long int k_dev;

	/* We must convert the value to dev_t type used by the kernel.  */
	k_dev = (dev) & ((1ULL << 32) - 1);

#ifdef __NR_mknod
	return INLINE_SYSCALL(mknod, 3, path, mode, (unsigned int)k_dev);
#elif defined __NR_mknodat
	return INLINE_SYSCALL(mknodat, 4, AT_FDCWD, path, mode, (unsigned int)k_dev);
#endif
}
libc_hidden_def(mknod)
