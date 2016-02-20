#include <sys/types.h>
#include <unistd.h>

#define BLOCK_SIZE 40 /* 由于存在虚拟的data字段,sizeof不能正确计算meta长度，这里手工设置 */
void *first_block = NULL;

typedef struct s_block *t_block;

/* 要区分block list和 heap的物理存储空间 */
struct s_block {
    size_t size;  /* 数据区大小 */
    t_block prev; 
    t_block next; /* 指向下个块的指针 */
    int free;     /* 是否是空闲块 */
    int padding;  /* 填充4字节，保证meta块长度为8的倍数 */
    void *ptr; /* Magic pointer，指向data, malloc返回的也是指向data的指针 */
    char data[1]  /* 这是一个虚拟字段，表示数据块的第一个字节，长度不应计入meta */
};

/* First fit */
t_block find_block(t_block *last, size_t size) {
    t_block b = first_block;
    while(b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return b;
}

t_block extend_heap(t_block last, size_t s) {
    t_block b;
    b = sbrk(0);
    if(sbrk(BLOCK_SIZE + s) == (void *)-1)
        return NULL;
    b->size = s;
    b->prev = NULL;
    b->next = NULL;
    if(last) {
        last->next = b;
        b->prev = last;  
    }
    b->free = 0;
    return b;
}

void split_block(t_block b, size_t s) {
    t_block new;
    new = b->data + s;
    new->size = b->size - s - BLOCK_SIZE ;
    new->prev = b;
    new->next = b->next;
    new->free = 1;
    b->size = s;
    new->next->prev = new;
    b->next = new;
}

t_block fusion(t_block b) {
    if (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next) {
            b->next->prev = b;
        }
    }
    return b;
}

size_t align8(size_t s) {
    if(s & 0x7 == 0)
        return s;
    return ((s >> 3) + 1) << 3;
}

t_block get_block(void *p) {
    char *tmp;
    tmp = p;
    return (p = tmp -= BLOCK_SIZE);
}

int valid_addr(void *p) {
    if (first_block) {
        if (p > first_block && p < sbrk(0)) {
            return p == (get_block(p))->ptr;
        }
    }
    return 0;
}

void copy_block(t_block src, t_block dst) {
    size_t *sdata, *ddata;
    size_t i;
    sdata = src->ptr;
    ddata = dst->ptr;
    for (i = 0; (i * 8) < src->size && (i * 8) < dst->size; i++) {
        ddata[i] = sdata[i];
    }
}

void *malloc(size_t size) {
    t_block b, last; /* last 是承接find_block和extend_heap的 */
    size_t s;
    s = align8(size);
    
    if (fist_block) {
        last = first_block;
        b = find_block(&last, s);
        if (b) {
            if ((b->size - s) > BLOCK_SIZE + 8) {
                split_block(b, s);
            }
            b->free = 0;
        } else {
            b = extend_heap(last, s); /* 因为find_block此时返回的是NULL，没有last的开辟出来的空间就没法插入block_list了 */
            if (!b) {
                return NULL;
            }
        }
    } else {
        b = extend_heap(last, s);
        if (!b) {
            return NULL;
        }
        first_block = b;
    }
    return b->data;
}


void *calloc(size_t number, size_t size) {
    size_t *new;
    size_t s8, i;
    new = malloc(number * size);
    if (new) {
        s8 = align8(number * size) >> 3; /* 这里假设OS 64bit,size_t是long unsigned int */
        for (i = 0; i < s8; i++) {
            new[i] = 0; /* 基于64bit OS,此次复制处理了8个子节 */
        }
    }
    return new;
}

void free(void *p) {
    t_block b;
    if (valid_addr(p)) {
        b = get_block(p);
        b->free = 1;
        if (b->prev && b->prev->free) {
            b = fusion(b->prev);
        }
        if (b->next && b->next->free) {
            b = fusion(b);
        }
        if (!b->next) {
            if (b->prev) {
                b->prev->next = NULL;
            } else {
                first_block = NUL
            }
            brk(b);
        }
    }
}

void *realloc(void *p, size_t size) {
    size_t s;
    t_block b, new;
    void *newp;
    if (!p) {
        return malloc(size);
    }
    
    if (valid_addr(p)) {
        s = align8(size);
        b = get_block(p);
        if (b->size >= s) {
            if (b->size - s >= (BLOCK_SIZE + 8)) {
                split_block(b, s);
            }
        } else {
            if (b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s) {
                fusion(b);
                if (b->size - s >= (BLOCK_SIZE + 8)) {
                    split_block(b, s);
                }
            } else {
                newp = malloc(s);
                if (!newp) {
                    return NULL;
                }
                new = get_block(newp);
                copy_block(b, new);
                free(p);
                return newp;
            }
        }
        return p;
    }
    return NULL;
}

