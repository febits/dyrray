# Dyrray

I was wondering myself how dynamic arrays in high-level languages work (such as Python and Javascript). So, I've tried to implement a tiny visualization of that.

Operations supported: `append`, `insert`, `delete`, `pop` and `get`.

In those programming languages, you can add and remove dynamically any element from any index (using any datatype). In other words, just abstractions.

When I think about dynamic arrays, the first idea that comes (in C): an array of pointers to a generic object structure, being the "generic object" like this below:

```c
typedef struct object_t {
  enum data_types dt;
  void *data;
} object_t;
```

C Language provides a way to obtain generic-like behavior with `void *`, being that void pointer to wherever. Alright, now we need a proper way to interpret the value stored in the `data` field. That can be reached by different approaches, but I choose a simple `enum`:

```c
enum data_types {
  I8,
  U8,
  I16,
  U16,
  I32,
  U32,
  I64,
  U64,
  F32,
  F64,
  CHAR_PTR,
  VOID_PTR
};
```

Well, you can handle the data types whatever you want to. In my case, I do handle just for print purposes with `dyrray_show(...);`.

The summary of the main struct `dyrray_t`:

```c
typedef struct dyrray_t {
  object_t **items;

  const char *label;
  u64 capacity;
  u64 csize;   

  // Other fields
  ...
}
```

Talking about the `REALLOC_FACTOR` which is the increment to the current value of `capacity`, it isn't explored based on efficiency. Remember, just a 4fun project. If you want to know more about those improvements, check the link below:

https://youtu.be/Ij7NQ-0mIVA?si=6LlU6nCXGv9mrWj9

Let's talk about the individual functions:

`append` and `pop` are operations (in core) fast. In the best case of `append`, the current `capacity` is enough to store a new item. In the worst case, it's necessary to realloc the entire array (which is an operation allocator-dependent). Once resized, you put the item there.

`insert` and `delete` are basically dependent of which `index` you want to insert or remove. In other words, it's an operation `O(N)` because you need to do a `shift` to LEFT or RIGHT in array.

Index `0` is the worst index because it would be necessary to run throughout the entire array, re-positioning all the elements.

Another approach would be to implement using linked-list.

4Fun challange.

## Compiling, testing and benchmarking
```bash
make
```

Run tests (you'll need to install [cmocka lib](https://cmocka.org/index.html)):
```bash
make tests
```

Run benchmark:
```bash
make bench
```
