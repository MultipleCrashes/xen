#ifndef __HVM_CACHEATTR_H__
#define __HVM_CACHEATTR_H__

void hvm_init_cacheattr_region_list(
    struct domain *d);
void hvm_destroy_cacheattr_region_list(
    struct domain *d);

/*
 * To see guest_fn is in the pinned range or not,
 * if yes, return the (non-negative) type
 * if no or ambiguous, return a negative error code
 */
int hvm_get_mem_pinned_cacheattr(
    struct domain *d,
    uint64_t guest_fn,
    unsigned int order);


/* Set pinned caching type for a domain. */
int32_t hvm_set_mem_pinned_cacheattr(
    struct domain *d,
    uint64_t gfn_start,
    uint64_t gfn_end,
    uint32_t  type);

#endif /* __HVM_CACHEATTR_H__ */
