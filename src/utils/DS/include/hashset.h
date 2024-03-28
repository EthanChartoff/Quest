//===--= hashset.h =----------------------------------------------------===
//
// a generic hash set. you know whats a hash set. 
//
//===-----------------------------------------------------------------===

// Define a node for the hash table
typedef struct HASHSET_NODE_STRUCT {
    void *data;           				// Pointer to hold generic data
    struct HASHSET_NODE_STRUCT *next;
} hashset_node_T;

// Define the hash table structure
typedef struct HASHSET_STRUCT {
    int size;
	int capacity;  						// Current capacity of the hash table
    float load_factor;
    hashset_node_T **buckets;
    unsigned int (*hash_func)(void *);
    int (*compare_func)(void *, void *);
} hashset_T;


hashset_T *init_hash_set(int initial_capacity, float load_factor, unsigned int (*hash_func)(void *), int (*compare_func)(void *, void *));

int hash_set_add(hashset_T *set, void* data);
int hash_set_add_all(hashset_T *set, hashset_T *other_set);
int hash_set_contains(hashset_T *set, void* data);
int hash_set_resize(hashset_T *set, int new_capacity);

int hash_set_compare(void *a, void *b);
unsigned int hash_set_hash(void *data);
