#ifndef _STL_WT_ALLOC_HPP_
#define _STL_WT_ALLOC_HPP_

namespace wt{

class alloc {
    union _obj{
        union _obj* free_list_next;
        char        client_data[1];
    }; 
public:
    static void*    allocate(size_t n);
    static void     deallocate(void* p, size_t n);
    static void*    reallocate(void* p, size_t old_size, size_t new_size);

private:
    static size_t   round_up(size_t bytes);
    static size_t   free_list_index(size_t bytes);
    static void*    refill(size_t n);
    static char*    chunk_alloc(size_t sz, int& nobjs);

private:
    static constexpr int kAlign = 8;
    static constexpr int kMaxBytes = 128;
    static constexpr int kNFreeLists = kMaxBytes / kAlign;

    static _obj* free_list[kNFreeLists];

    static char*    start_free_list;
    static char*    end_free_list;
    static size_t   heap_size;
};




} // namespace wt

#endif