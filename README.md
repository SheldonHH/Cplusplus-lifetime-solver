# Cplusplus-lifetime-solver

ASan 能检测多种内存错误，包括堆缓冲区溢出、栈缓冲区溢出、使用释放的内存
```bash
g++ -fsanitize=address -g -o example example.cpp
```


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