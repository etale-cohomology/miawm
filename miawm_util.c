/* @blk0  libutil: stuff that should be in the C standard library to begin with! */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk1  libkeyword */
#define fdef   static           // function definition
#define fdefi  static __inline  // function definition, inline
#define fdefe  extern           // function definition, extern
#define tdef   typedef struct   // type     definition
#define edef   typedef enum     // enum     definition
#define udef   typedef union    // union    definition
#define cdef   static const     // constant definition

#define mexternal    extern  // Only use this keyword for function declarations/names?
#define minternal    static  // Only use this keyword for function declarations/names? This doesn't seem to work on C++!
#define mpersistent  static  // Only use this keyword INSIDE function definitions!
#define minline      __attribute__((always_inline))
#define mnoinline    __attribute__((noinline))
#define moverload    __attribute__((overloadable))  // clang only?! =(
#define mauto        __auto_type      // compile-time type inference

// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk1  libtype */
#include <stdint.h>  // sexy types!
typedef    int8_t     i8;
typedef    int16_t    i16;
typedef    int32_t    i32;
typedef    int64_t    i64;

typedef    uint8_t    u8;
typedef    uint16_t   u16;
typedef    uint32_t   u32;
typedef    uint64_t   u64;

// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk1  libmisc */
#include <errno.h>
#define m_chk( ST)  if(      (ST) !=0)     printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()\n",                    __FILE__,__LINE__,__func__)
#define m_chks(ST)  if(((i64)(ST))==-1ll)  printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()  \x1b[37m%s\x1b[0m\n", __FILE__,__LINE__,__func__, strerror(errno))
#define m_fail()                           printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()\n",                    __FILE__,__LINE__,__func__)
#define m_warn()                           printf("\x1b[91mWARN  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()\n",                    __FILE__,__LINE__,__func__)
#define m_meta()                           printf("\x1b[33mMETA  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()\n",                    __FILE__,__LINE__,__func__)
#define m_sep()                            puts("\n-------------------------------------------------------------------------------------------------------------------------------\x1b[91m#\x1b[0m")

#define m_for( IDX, IDX_INI,IDX_END)  for(i64 (IDX)=(IDX_INI); (IDX)<(IDX_END); ++(IDX))  // Default `for` loop! Flexibility over speed, ie. i64 vs i32? As always, of course, u64 is out of the question for looping! =D
#define m_fori(IDX, IDX_INI,IDX_END)  for(i32 (IDX)=(IDX_INI); (IDX)<(IDX_END); ++(IDX))  // Fastest `for` loop: signed yields a faster loop than unsigned because there's no need for overflow checks (or something), and i32 is faster than i64!
#define m_foru(IDX, IDX_INI,IDX_END)  for(u32 (IDX)=(IDX_INI); (IDX)<(IDX_END); ++(IDX))  // 2nd fastest `for` loop!

#define m_array_idim(ARR)  (sizeof((ARR)) / sizeof((*(ARR))))
#define m_array_bdim(ARR)  (sizeof((ARR))

#define m_min(       A, B)             ({  typeof(A) _a=(A);  typeof(B) _b=(B);  _a<_b ?  _a : _b;  })  // @typeof() is useful w/ `statement expressions`. Here's how they can be used to define a safe macro which operates on any arithmetic type and `evaluates each of its arguments exactly once`
#define m_max(       A, B)             ({  typeof(A) _a=(A);  typeof(B) _b=(B);  _a<_b ?  _b : _a;  })  // @typeof() is useful w/ `statement expressions`. Here's how they can be used to define a safe macro which operates on any arithmetic type and `evaluates each of its arguments exactly once`
#define m_abs(       A)                ({  typeof(A) _a=(A);                     _a< 0 ? -_a : _a;  })  // @typeof() is useful w/ `statement expressions`. Here's how they can be used to define a safe macro which operates on any arithmetic type and `evaluates each of its arguments exactly once`
#define m_clamp(     X, A,B)           m_min(m_max((X), (A)), (B))
#define m_is_in( X, A,B)               ({  typeof(X) _x=(X);  typeof(X) _a=(A);  typeof(X) _b=(B);  (_a<=_x && _x< _b);  })  // closed-open interval!
#define m_nis_in(X, A,B)               ({  typeof(X) _x=(X);  typeof(X) _a=(A);  typeof(X) _b=(B);  (_x< _a || _b<=_x);  })  // closed-open interval!
#define m_udivceil(  DIVIDEND, DIVISOR)({  u32 _a=(u32)(DIVIDEND);  u32 _b=(u32)(DIVISOR);  _a/_b + (_a%_b ? 1 : 0);  })  // NOTE! Would-be expensive, since there's a mod; BUT most ISA's idiv/udiv computes the mod anyway, so, FAST? Works for the WHOLE domain?
#define m_udivceil64(DIVIDEND, DIVISOR)({  u64 _a=(u64)(DIVIDEND);  u64 _b=(u64)(DIVISOR);  _a/_b + (_a%_b ? 1 : 0);  })  // NOTE! Would-be expensive, since there's a mod; BUT most ISA's idiv/udiv computes the mod anyway, so, FAST? Works for the WHOLE domain?

// 0b000000000000000011111111  // bgr888_b
// 0b000000000000000000011111  // bgr565_b
// 0b000000001111100000000000  // rgb565_b
// 0b000000001111111100000000  // bgr888_g
// 0b000000000000011111100000  // bgr565_g
// 0b000000000000011111100000  // rgb565_g
// 0b111111110000000000000000  // bgr888_r
// 0b000000001111100000000000  // bgr565_r
// 0b000000000000000000011111  // rgb565_r
#define bgr888_to_bgr565(BGR888)({  u32 _bgr888=BGR888;  (((_bgr888>>((0)    +(8-5)-(0)))&0b0000000000011111) | ((_bgr888>>((0+8)+(8-6)-(0+5)))&0b0000011111100000) | ((_bgr888>>((0+8+8)+(8-5)-(0+5+6)))&0b1111100000000000));  })
#define rgb888_to_rgb565(RGB888)({  u32 _rgb888=RGB888;  (((_rgb888>>((0)    +(8-5)-(0)))&0b0000000000011111) | ((_rgb888>>((0+8)+(8-6)-(0+5)))&0b0000011111100000) | ((_rgb888>>((0+8+8)+(8-5)-(0+5+6)))&0b1111100000000000));  })
#define bgr888_to_rgb565(BGR888)({  u32 _bgr888=BGR888;  (((_bgr888>>((0+8+8)+(8-5)-(0)))&0b0000000000011111) | ((_bgr888>>((0+8)+(8-6)-(0+5)))&0b0000011111100000) | ((_bgr888<<((0)    -(8-5)+(0+5+6)))&0b1111100000000000));  })
#define rgb888_to_bgr565(RGB888)({  u32 _rgb888=RGB888;  (((_rgb888>>((0+8+8)+(8-5)-(0)))&0b0000000000011111) | ((_rgb888>>((0+8)+(8-6)-(0+5)))&0b0000011111100000) | ((_rgb888<<((0)    -(8-5)+(0+5+6)))&0b1111100000000000));  })
#define bgr888_to_rgb888(BGR888)({  u32 _bgr888=BGR888;  (((_bgr888>>0x10)&0b000000000000000011111111) | ((_bgr888>>0x00)&0b000000001111111100000000) | ((_bgr888<<0x10)&0b111111110000000000000000));  })
#define rgb888_to_bgr888(RGB888)({  u32 _rgb888=RGB888;  (((_rgb888>>0x10)&0b000000000000000011111111) | ((_rgb888>>0x00)&0b000000001111111100000000) | ((_rgb888<<0x10)&0b111111110000000000000000));  })

#define xorswap(A,B)  ((&(A)==&(B)) ? (A) : ((A)^=(B), (B)^=(A), (A)^=(B)))  // xorswap fails when A and B are the same object (sets it to 0), so first check for distinct addresses!

// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk1  libexec
In Linux, @fork() is implemented using copy-on-write pages, so the only @fork() penalty is the time/mem needed to duplicate the parent's page tables and to create a unique task structure for the child!
@vfork() is 10x faster than @fork()! No parent-child communication! @vfork() is a special case of @clone(), used to create new processes w/o copying the page tables of the parent process, for high-performance apps where a child is created which then immediately issues an execve()! fork()/vfork() return twice! Once for the child (zero pid) and once for the parent (positive pid).
To run SYNC (and not ASYNC), call wait()/waitpid() on the PARENT (which has nonzero pid as returned by fork()/vfork()!
*/
#include <unistd.h>  // @vfork(), @fork(), @dup2()
#include <fcntl.h>   // @open()
#include <sys/wait.h>

fdef pid_t exec(char* args[]){  /*launch a process ASYNCHRONOUSLY*/
  pid_t  pid   = vfork();  m_chks(pid);
  if(pid==0){  /*child*/ /*Should @exit() after @execv(), so the child doesn't return from this function/macro?*/
    int fd = open("/dev/null", O_WRONLY);  m_chks(fd);  /*silence stdout/stderr for this process!*/
    m_chks(dup2(fd, STDOUT_FILENO));
    m_chks(dup2(fd, STDERR_FILENO));
    m_chks(close(fd));
    m_chks(execv(args[0],args));  /*@execv() only returns if there's an error!*/
    exit(1);  /*If @execv() fails, we @exit() the child!*/
  }else if(pid>0){  /*parent*/
    /*m_chks(waitpid(pid,NULL,0));*/  /*IF 0) we don't @wait()/@waitpid() on children AND 1) we don't @signal(SIGCHLD,SIG_IGN), THEN they become zombies!*/
  }
  return pid;
}

#include <limits.h>  // @PATH_MAX
#define TASK_COMM_LEN  0x10  // https://elixir.bootlin.com/linux/latest/source/include/linux/sched.h#L213
fdef void pid_comm(pid_t pid, int comm_bdim,char* comm_cstr){  if(pid==0){  memcpy(comm_cstr,"???",4); return;  }  // EXAMPLE! `char comm[TASK_COMM_LEN]; pid_comm(pid, TASK_COMM_LEN,comm);`  // NOTE! @comm_bdim should be @TASK_COMM_LEN (0x10 bytes)
  char comm_path[PATH_MAX]; comm_path[sizeof(comm_path)-1]=0x00;  snprintf(comm_path,sizeof(comm_path)-1, "/proc/%d/comm", pid);   // prep, fill
  int  comm_fd = open(comm_path, O_RDONLY);  if(comm_fd==-1)  printf("\x1b[91mFAIL  \x1b[31m%s\x1b[91m:\x1b[0mL\x1b[32m%d\x1b[91m:\x1b[94m%s\x1b[0m()  \x1b[37m%s  \x1b[31m%s  \x1b[0m\n", __FILE__,__LINE__,__func__, strerror(errno), comm_path);
  comm_cstr[comm_bdim-1]=0x00;  i64 comm_read_bdim=read(comm_fd, comm_cstr,comm_bdim-1);  m_chks(comm_read_bdim);  // prep, fill
  if(comm_cstr[comm_read_bdim-1]==0x0a)  comm_cstr[comm_read_bdim-1]=0x00;  // sanitize
  m_chks(close(comm_fd));
}

// ----------------------------------------------------------------------------------------------------------------------------#
/* @blk1  libvec: A dynamic array implementation in C similar to the one found in standard C++. Originally by Evan Teran.  https://github.com/eteran/c-vector */
#define VEC_IDIM_CAP_INI  0x100  // NOTE! This CANNOT be zero!! =)

#define vec__idim_set(    VEC, VAL)  (((i64*)(VEC))[-2] = (VAL))  // Don't call these if the vec is an invalid (eg. NULL) pointer!
#define vec__idim_cap_set(VEC, VAL)  (((i64*)(VEC))[-1] = (VAL))  // Don't call these if the vec is an invalid (eg. NULL) pointer!
#define vec_idim(         VEC)       (((i64*)(VEC))[-2])
#define vec_idim_cap(     VEC)       (((i64*)(VEC))[-1])
#define vec_bdim(         VEC)       (sizeof(*VEC) * vec_idim(VEC))
#define vec_bdim_cap(     VEC)       (sizeof(*VEC) * vec_idim_cap(VEC))

#define vec_head(  VEC)              (VEC)                      // @fun `vec_head`. Get an iterator to 1st item of a vec!
#define vec_tail(  VEC)              (&((VEC)[vec_idim(VEC)]))  // @fun `vec_tail`. Get an iterator to one past the last item of a vec!
#define vec_next(  VEC, IT)          (++(IT))                   // @fun `vec_next`. Advance an iterator!
#define vec_forall(VEC, IT)          for(typeof(VEC) (IT) = vec_head((VEC));  (IT) != vec_tail((VEC));  vec_next((VEC),(IT)))

#define vec_meta(VEC)                printf("\x1b[94mvec_t  \x1b[32midim \x1b[0m%'ld\x1b[91m/\x1b[0m%'ld  \x1b[94mbdim \x1b[0m%'ld\x1b[91m/\x1b[0m%'ld\x1b[0m\n", vec_idim(VEC), vec_idim_cap(VEC), vec_bdim(VEC), vec_bdim_cap(VEC))

// ----------------------------------------------------------------
// @fun `vec_ini`.
// This is a mighty GCC macro kind called a `statement expression`! BEST GGC FEATURE EVER!  https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html
// The last thing in the compound statement should be an expression followed by a semicolon; the value of this subexpression serves as the value of the entire construct. (If you use some other kind of statement last within the braces, the construct has type void, and thus effectively no value!)
#define vec_ini(VEC_TYPE_T)({                                                \
  i64* _base = malloc(2*sizeof(i64) + sizeof(VEC_TYPE_T)*VEC_IDIM_CAP_INI);  \
  vec__idim_set(    (void*)(&_base[2]), 0);                                  \
  vec__idim_cap_set((void*)(&_base[2]), VEC_IDIM_CAP_INI);                   \
  (void*)(&_base[2]);  /*Return value!*/                                     \
})

// @fun `vec_end`.  Free all mem associated w/ a vec, from the base (which is -2 spots from the actual vec, because it starts at the metadata)!
#define vec_end(VEC)  do{           \
  i64* _base = &((i64*)(VEC))[-2];  \
  free(_base);                      \
}while(0)

// @fun `vec_clear`. O[1]. Equivalent to @vec_keepn(0)
#define vec_clear(VEC)  vec__idim_set(VEC, 0)

// @fun `vec_keepn`. O[1].
#define vec_keepn(VEC, N)  vec__idim_set(VEC, m_min((N), vec_idim(VEC)))

// ----------------------------------------------------------------
// @fun `vec__resize`.  Resize VEC to hold up to @nvals items!
#define vec__resize(VEC, N)  do{                           \
  i64  _idim = (N);                                        \
  i64  _bdim = sizeof(i64)*2  + sizeof(*(VEC))*_idim;      \
  i64* _base = realloc(&((i64*)(VEC))[-2], _bdim);         \
  (VEC) = (void*)(&_base[2]);  /*We NEED this!*/           \
  vec__idim_set(    (VEC), m_min(vec_idim((VEC)),_idim));  \
  vec__idim_cap_set((VEC), _idim);                         \
}while(0)

// ----------------------------------------------------------------
// @fun `vec_push`.  O[1]. Append an item to (the end of) a vec. The most important function of the whole thing!
#define vec_push(VEC, VAL)  do{         \
  i64 _idx      = vec_idim((VEC));      \
  i64 _idim_new = _idx+1;               \
  i64 _idim_cap = vec_idim_cap((VEC));  \
  if(_idim_cap < _idim_new){            \
    vec__resize((VEC), 2*_idim_cap+1);  \
  }                                     \
  vec__idim_set((VEC), _idim_new);      \
  (VEC)[_idx] = (VAL);                  \
}while(0)

// @fun `vec_pop`.  O[1]. Delete the last item from a vec!
#define vec_pop(VEC)  do{                         \
  i64 _idim_new = m_max(0, vec_idim((VEC)) - 1);  \
  vec__idim_set((VEC), _idim_new);                \
}while(0)

// @fun `vec_pushn`.  O[k]. Append k elements to a vec!
#define vec_pushn(VEC, N,DATA)  do{                      \
  i64 _n        = (N);                                   \
  i64 _idx      = vec_idim((VEC));                       \
  i64 _idim_new = _idx+_n;                               \
  i64 _idim_cap = vec_idim_cap((VEC));                   \
  if(_idim_cap < _idim_new){                             \
    vec__resize((VEC), 2*m_max(_idim_cap,_idim_new)+1);  \
  }                                                      \
  vec__idim_set((VEC), _idim_new);                       \
  for(i64 _i=0; _i<_n; ++_i){                            \
    (VEC)[_idx+_i] = (DATA)[_i];                         \
  }                                                      \
}while(0)

// @fun `vec_popn`.  O[1]. Delete the last k items from a vec!
#define vec_popn(VEC, N)  do{                       \
  i64 _idim_new = m_max(0, vec_idim((VEC)) - (N));  \
  vec__idim_set((VEC), _idim_new);                  \
}while(0)

// ----------------------------------------------------------------
// @fun `vec_get`.
#define vec_get(VEC, IDX)  ((VEC)[(IDX)])

// @fun `vec_put`.  O[n]. Insert an item at index @IDX in a vec!
#define vec_put(VEC, IDX, VAL)  do{              \
  i64 _idx      = (IDX);                         \
  i64 _idim_new = vec_idim((VEC)) + 1;           \
  i64 _idim_cap = vec_idim_cap((VEC));           \
  if(0<=_idx && _idx<_idim_new-1){               \
    if(_idim_cap < _idim_new){                   \
      vec__resize((VEC), 2*_idim_cap+1);         \
    }                                            \
    vec__idim_set((VEC), _idim_new);             \
    for(i64 _i=_idim_new-1; _i>=_idx; --_i){     \
      (VEC)[_i+1] = (VEC)[_i];                   \
    }                                            \
    (VEC)[_idx] = (VAL);                         \
  }                                              \
}while(0)

// @fun `vec_del`.  O[n]. Delete the item at index @IDX from a vec!
#define vec_del(VEC, IDX)  do{                    \
  i64 _idx      = (IDX);                          \
  i64 _idim_new = m_max(0, vec_idim((VEC)) - 1);  \
  if(0<=_idx && _idx<_idim_new+1){                \
    vec__idim_set((VEC), _idim_new);              \
    for(i64 _i=_idx; _i<_idim_new+1; ++_i){       \
      (VEC)[_i] = (VEC)[_i+1];                    \
    }                                             \
  }                                               \
}while(0)

#define vec_putn(VEC, IDX, N,DATA)  // TODO!
#define vec_deln(VEC, IDX, N,DATA)  // TODO!

// ----------------------------------------------------------------
// @fun  @vec_idx()  O[n]  Get the index of a given item if it the item exist! If it doesn't exist, its index is -1
#define vec_idx(VEC, ITEM)({             \
  i64 _idx  = -1;                        \
  for(i64 _i=0; _i<vec_idim(VEC); ++_i)  \
    if((VEC)[_i]==(ITEM))  _idx=_i;      \
  _idx;                                  \
})

// @fun  @vec_swap()  O[1]
#define vec_swap(VEC, I,J)  do{   \
  i64 _i            = (I);        \
  i64 _j            = (J);        \
  typeof(*VEC) _tmp = (VEC)[_i];  \
  (VEC)[_i]         = (VEC)[_j];  \
  (VEC)[_j]         = _tmp;       \
}while(0)

// ----------------------------------------------------------------
#define vec_sort(VEC, CMP_FN)  qsort((VEC), vec_idim((VEC)), sizeof(*(VEC)), CMP_FN);
