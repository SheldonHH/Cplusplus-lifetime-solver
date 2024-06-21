# Cplusplus-lifetime-solver

# 原理


| Tool              | Detection Principle                                                                                   |
|-------------------|-------------------------------------------------------------------------------------------------------|
| Valgrind          | Uses dynamic instrumentation to insert checking code at runtime, monitoring memory allocation and deallocation to detect issues like memory leaks and illegal memory accesses. |
| MemorySanitizer   | Uses compile-time instrumentation to insert checking code into the target program, tracking the initialization state of each memory byte at runtime to detect use-of-uninitialized-memory errors. |
| AddressSanitizer  | Uses compile-time instrumentation to monitor memory access at runtime, detecting and reporting memory errors such as buffer overflows and use-after-free issues. |
| Dr. Memory        | Uses dynamic instrumentation to insert checking code at runtime, monitoring memory usage to detect errors like memory leaks, out-of-bounds accesses, and use of uninitialized memory. |


| 工具              | 检测原理                                                                                   | 推荐排序 | 优点                                                                                  | 缺点                                         |
|-------------------|------------------------------------------------------------------------------------------|---------|-------------------------------------------------------------------------------------|--------------------------------------------|
| AddressSanitizer  | 使用编译时插桩技术，在运行时监控内存访问，检测并报告内存错误，如缓冲区溢出和使用释放的内存。                                              | 1       | 高效、使用方便、提供详细错误报告。                                                         | 需要重新编译代码，有一定的运行时开销。                    |
| Valgrind          | 使用动态插桩技术，在程序运行时插入检测代码，监控内存的分配和释放操作，检测内存泄漏、非法内存访问等问题。                                           | 2       | 强大的内存错误检测功能，无需修改编译选项。                                                  | 运行时开销较大，可能显著降低程序运行速度。                |
| Dr. Memory        | 使用动态插桩技术，在程序运行时插入检测代码，监控内存使用情况，检测内存错误，如内存泄漏、越界访问和使用未初始化的内存等。                                        | 3       | 类似 Valgrind，检测多种内存问题。                                                         | 性能开销较大，可能不适用于大规模应用程序。                |
| MemorySanitizer   | 使用编译时插桩技术，在编译时将检测代码插入目标程序，并在运行时跟踪每个内存字节的初始化状态，检测未初始化内存读取（use-of-uninitialized-memory）错误。 | 4       | 专门用于检测未初始化内存访问错误。                                                         | 主要针对未初始化内存访问问题，不适用于所有内存错误检测。    |






# Asan
## 原理
ASan (AddressSanitizer) works by using compile-time instrumentation to monitor memory access at runtime, detecting and reporting memory errors such as buffer overflows and use-after-free issues.
通过编译时插桩技术，在运行时监控内存访问，检测并报告内存错误，如缓冲区溢出和使用释放的内存

## 检测
ASan 能检测多种内存错误，包括堆缓冲区溢出、栈缓冲区溢出、使用释放的内存
```bash
g++ -fsanitize=address -g -o example example.cpp
```

1. 这行代码试图写入一个整数（4 个字节）到地址 0xffff7be00f78。但是，这个地址超出了分配的数组范围。

2. 报告还包括影子字节`Shadow Bytes`的状态，这些字节帮助 ASan 
`fa` 表示堆左红区（heap left redzone），`00` 表示可寻址区域，`fa` 后面的区域表示溢出部分。

```cpp
=================================================================
==17882==ERROR: AddressSanitizer: heap-buffer-overflow on address 0xffff7be00f78 at pc 0xaaaac2a00cc0 bp 0xffffe4799680 sp 0xffffe4799690
WRITE of size 4 at 0xffff7be00f78 thread T0
    #0 0xaaaac2a00cbc in main /root/trading-programming/CPP-Lifetime-Solver/example.cpp:5
    #1 0xffff800473f8  (/lib/aarch64-linux-gnu/libc.so.6+0x273f8)
    #2 0xffff800474c8 in __libc_start_main (/lib/aarch64-linux-gnu/libc.so.6+0x274c8)
    #3 0xaaaac2a00b6c in _start (/root/trading-programming/CPP-Lifetime-Solver/example+0xb6c)

0xffff7be00f78 is located 0 bytes to the right of 40-byte region [0xffff7be00f50,0xffff7be00f78)
allocated by thread T0 here:
    #0 0xffff8057bcec in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:102
    #1 0xaaaac2a00c60 in main /root/trading-programming/CPP-Lifetime-Solver/example.cpp:4
    #2 0xffff800473f8  (/lib/aarch64-linux-gnu/libc.so.6+0x273f8)
    #3 0xffff800474c8 in __libc_start_main (/lib/aarch64-linux-gnu/libc.so.6+0x274c8)
    #4 0xaaaac2a00b6c in _start (/root/trading-programming/CPP-Lifetime-Solver/example+0xb6c)

SUMMARY: AddressSanitizer: heap-buffer-overflow /root/trading-programming/CPP-Lifetime-Solver/example.cpp:5 in main
Shadow bytes around the buggy address:
  0x200fef7c0190: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c01a0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c01b0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c01c0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c01d0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x200fef7c01e0: fa fa fa fa fa fa fa fa fa fa 00 00 00 00 00[fa]
  0x200fef7c01f0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c0200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c0210: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c0220: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x200fef7c0230: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==17882==ABORTING
```


# Valgrind
1. 安装Valgrind
```bash
sudo apt-get install valgrind -y
```
2. 编译代码（不需要特别的编译选项）
```bash
g++ -g -o use_after_free_example use_after_free_example.cpp
```
## 检测
```bash
root@e500e0d544ab:~/trading-programming/CPP-Lifetime-Solver# valgrind --leak-check=full ./use_after_free_example
==40289== Memcheck, a memory error detector
==40289== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==40289== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==40289== Command: ./use_after_free_example
==40289== 
==40289== Invalid write of size 4
==40289==    at 0x108A84: main (use_after_free_example.cpp:7)
==40289==  Address 0x4d46c80 is 0 bytes inside a block of size 40 free'd
==40289==    at 0x48690B0: operator delete[](void*) (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==40289==    by 0x108A7B: main (use_after_free_example.cpp:5)
==40289==  Block was alloc'd at
==40289==    at 0x4866AE8: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==40289==    by 0x108A63: main (use_after_free_example.cpp:4)
==40289== 
==40289== Invalid read of size 4
==40289==    at 0x108A8C: main (use_after_free_example.cpp:8)
==40289==  Address 0x4d46c80 is 0 bytes inside a block of size 40 free'd
==40289==    at 0x48690B0: operator delete[](void*) (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==40289==    by 0x108A7B: main (use_after_free_example.cpp:5)
==40289==  Block was alloc'd at
==40289==    at 0x4866AE8: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==40289==    by 0x108A63: main (use_after_free_example.cpp:4)
==40289== 
1
==40289== 
==40289== HEAP SUMMARY:
==40289==     in use at exit: 0 bytes in 0 blocks
==40289==   total heap usage: 3 allocs, 3 frees, 73,768 bytes allocated
==40289== 
==40289== All heap blocks were freed -- no leaks are possible
==40289== 
==40289== For lists of detected and suppressed errors, rerun with: -s
==40289== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

# Dr.Memory

```bash
# root@e500e0d544ab:~/trading-programming/CPP-Lifetime-Solver# uname -m
# aarch64

sudo apt-get install qemu-user-static
sudo apt-get install libc6:i386 -y

wget https://github.com/DynamoRIO/drmemory/releases/download/release_2.6.0/DrMemory-Linux-2.6.0.tar.gz

tar -xvzf DrMemory-Linux-2.6.0.tar.gz 
g++ -g -o use_after_free_example use_after_free_example.cpp

```