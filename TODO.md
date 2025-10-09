
Version 0.1

- [x] Remove registry data idea
- [ ] Scrap embedded idea and always align blocks and data inside them by 4 bytes. Resizer will happen if needed and the user should account for this too.
- [ ] Create pmal pointers akin to unique and shared which will be scope and reference. Scope will be a pointer where only its ownership is itself .Ref (Reference) will act like a shared ptr
- [ ] Program block and handle query logic
- [ ] Program an allocator
- [ ] Program MemoryManager::allocator logic
- [x] Change vector data structure to singly linked list (forward_list container) for blocks (insertion is quick and search was always going to be O(n))
