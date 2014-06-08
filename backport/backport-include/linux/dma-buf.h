#ifndef _BACKPORT_DMA_BUF_H__
#define _BACKPORT_DMA_BUF_H__
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0)
#include_next <linux/dma-buf.h>
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
#define dma_buf_export(priv, ops, size, flags, resv)	\
	dma_buf_export(priv, ops, size, flags)
#elif LINUX_VERSION_CODE < KERNEL_VERSION(3,16,0)
#undef dma_buf_export
#define dma_buf_export(priv, ops, size, flags, resv)	\
	dma_buf_export_named(priv, ops, size, flags, KBUILD_MODNAME)
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0) */

#endif /* _BACKPORT_DMA_BUF_H__ */
