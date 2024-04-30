//===--= hashset.h =----------------------------------------------------===
//
// a generic hash set. you know whats a hash set. 
//
//===-----------------------------------------------------------------===

typedef struct HASHSET_NODE_STRUCT {
    void *data;           				/* The data stored in the node */
    struct HASHSET_NODE_STRUCT *next;  /* Pointer to the next node in the bucket */
} hashset_node_T;

typedef struct HASHSET_STRUCT {
    int size;               /* Number of elements in the set */
	int capacity;			/* Number of buckets in the set */
    float load_factor;      /* Maximum ratio of number of elements to number of buckets */
    hashset_node_T **buckets; /* Array of bucket pointers */
    unsigned int (*hash_func)(void *); /* Pointer to a hash function to hash data */
    int (*compare_func)(void *, void *); /* Pointer to a comparison function to compare data */
} hashset_T;


hashset_T *init_hash_set(int initial_capacity, float load_factor, unsigned int (*hash_func)(void *), int (*compare_func)(void *, void *));

int hash_set_add(hashset_T *set, void* data);
int hash_set_add_all(hashset_T *set, hashset_T *other_set);
int hash_set_contains(hashset_T *set, void* data);
int hash_set_resize(hashset_T *set, int new_capacity);

int hash_set_compare(void *a, void *b);
unsigned int hash_set_hash(void *data);
