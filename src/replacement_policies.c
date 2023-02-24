//
// This file contains all of the implementations of the replacement_policy
// constructors from the replacement_policies.h file.
//
// It also contains stubs of all of the functions that are added to each
// replacement_policy struct at construction time.
//
// ============================================================================
// NOTE: It is recommended that you read the comments in the
// replacement_policies.h file for further context on what each function is
// for.
// ============================================================================
//

#include "replacement_policies.h"

// LRU Replacement Policy
// ============================================================================
// TODO feel free to create additional structs/enums as necessary

void lru_cache_access(struct replacement_policy *replacement_policy,
                      struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
    int set_start = set_idx * cache_system->associativity;
    for(int i = 0; i < cache_system->associativity; i++){
        cache_system->cache_lines[set_start+i].age++;
        if(cache_system->cache_lines[set_start+i].tag == tag){
            cache_system->cache_lines[set_start+i].age = 0;
        }
    }
}

uint32_t lru_eviction_index(struct replacement_policy *replacement_policy,
                            struct cache_system *cache_system, uint32_t set_idx)
{
    int set_start = set_idx * cache_system->associativity;
    int oldest = -1;
    int oldest_idx = -1;
    for(int i = 0; i < cache_system->associativity; i++){
        if(cache_system->cache_lines[set_start+i].age > oldest){
            oldest = cache_system->cache_lines[set_start+i].age;
            oldest_idx = i;
        }
    }
    cache_system->cache_lines[set_start+oldest_idx].age = 0;
    return oldest_idx;
}

void lru_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // lru_replacement_policy_new function.
}

struct replacement_policy *lru_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    struct replacement_policy *lru_rp = calloc(1, sizeof(struct replacement_policy));
    lru_rp->cache_access = &lru_cache_access;
    lru_rp->eviction_index = &lru_eviction_index;
    lru_rp->cleanup = &lru_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to

    // lru_rp->data.

    return lru_rp;
}

// RAND Replacement Policy
// ============================================================================
void rand_cache_access(struct replacement_policy *replacement_policy,
                       struct cache_system *cache_system, uint32_t set_idx, uint32_t tag)
{
    // TODO update the RAND replacement policy state given a new memory access
}

uint32_t rand_eviction_index(struct replacement_policy *replacement_policy,
                             struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.
    return rand() % cache_system->associativity;
}

void rand_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // rand_replacement_policy_new function.
}

struct replacement_policy *rand_replacement_policy_new(uint32_t sets, uint32_t associativity)
{
    // Seed randomness
    srand(time(NULL));

    struct replacement_policy *rand_rp = malloc(sizeof(struct replacement_policy));
    rand_rp->cache_access = &rand_cache_access;
    rand_rp->eviction_index = &rand_eviction_index;
    rand_rp->cleanup = &rand_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // rand_rp->data.

    return rand_rp;
}

// LRU_PREFER_CLEAN Replacement Policy
// ============================================================================
void lru_prefer_clean_cache_access(struct replacement_policy *replacement_policy,
                                   struct cache_system *cache_system, uint32_t set_idx,
                                   uint32_t tag)
{
    int set_start = set_idx * cache_system->associativity;
    for(int i = 0; i < cache_system->associativity; i++){
        cache_system->cache_lines[set_start+i].age++;
        if(cache_system->cache_lines[set_start+i].tag == tag){
            cache_system->cache_lines[set_start+i].age = 0;
        }
    }
}

uint32_t lru_prefer_clean_eviction_index(struct replacement_policy *replacement_policy,
                                         struct cache_system *cache_system, uint32_t set_idx)
{
    // TODO return the index within the set that should be evicted.
    int set_start = set_idx * cache_system->associativity;
    int oldest = -1;
    int oldest_idx = -1;
    for(int i = 0; i < cache_system->associativity; i++){
        if(cache_system->cache_lines[set_start+i].age > oldest){
            if(cache_system->cache_lines[set_start+i].status != MODIFIED){
                oldest = cache_system->cache_lines[set_start+i].age;
                oldest_idx = i;
            }
        }
    }
    if(oldest_idx == -1){
        for(int i = 0; i < cache_system->associativity; i++){
            if(cache_system->cache_lines[set_start+i].age > oldest){
                oldest = cache_system->cache_lines[set_start+i].age;
                oldest_idx = i;
            }
        }
    }
    cache_system->cache_lines[set_start+oldest_idx].age = 0;
    return oldest_idx;
}

void lru_prefer_clean_replacement_policy_cleanup(struct replacement_policy *replacement_policy)
{
    // TODO cleanup any additional memory that you allocated in the
    // lru_prefer_clean_replacement_policy_new function.
}

struct replacement_policy *lru_prefer_clean_replacement_policy_new(uint32_t sets,
                                                                   uint32_t associativity)
{
    struct replacement_policy *lru_prefer_clean_rp = malloc(sizeof(struct replacement_policy));
    lru_prefer_clean_rp->cache_access = &lru_prefer_clean_cache_access;
    lru_prefer_clean_rp->eviction_index = &lru_prefer_clean_eviction_index;
    lru_prefer_clean_rp->cleanup = &lru_prefer_clean_replacement_policy_cleanup;

    // TODO allocate any additional memory to store metadata here and assign to
    // lru_prefer_clean_rp->data.

    return lru_prefer_clean_rp;
}
