# seakg-hack-xor

1. Encrypt/Decrypt file use a xor
2. Try hack xor crypt

Concept of hack: Filtering possible key values based on a specific alphabet of the initial file and key length.


## Build

Requirements for build (MacOS):
```
$ brew install pkg-config cmake
```

Requirements for build (Ubuntu/Debian):
```
$ sudo apt install cmake make g++ pkg-config git-core
```

## Integrate to your project via wsjcpp

```
$ wsjcpp install https://github.com/sea-kg/seakg-hack-xor:master
```

or include files:

- src.wsjcpp/wsjcpp_core.h
- src.wsjcpp/wsjcpp_core.cpp
- src/seakg_hack_xor.h
- src/seakg_hack_xor.cpp

## Run && Usage

Crypt file
```
$ ./seakg-hack-xor xor orig_filepath key_filepath crypted_filepath
```

Decrypt file
```
$ ./seakg-hack-xor xor crypted_filepath key_filepath decrypted_filepath
```

Try hack crypted file example run and output
```
$ ./seakg-hack-xor xor crypted_filepath 38 key_alphabet_filepath text_alphabet_filepath
2020-03-19 17:40:09.032, 0x0x10fbe5dc0 [OK] SeakgHackXor::hackXor: Found one solution: 
Hex   : [546869732069732073696d706c65206b657920666f7220584f52206f7065726174696f6e2e]
String: [This is simple key for XOR operation.]
```

or when you have different sollutions output will be like:

```
2020-03-19 18:09:41.694, 0x0x109ab9dc0 [WARN] SeakgHackXor::hackXor: Difference solutions have
2020-03-19 18:09:41.695, 0x0x109ab9dc0 [WARN] SeakgHackXor::hackXor: Found several solutions, printed keys (HEX): 
HEX   : possible_key[0] = {54}
HEX   : possible_key[1] = {68, 2a, 22}
HEX   : possible_key[2] = {43, 69, 2b, 3b}
HEX   : possible_key[3] = {73, 37}
HEX   : possible_key[4] = {20, 75, 7a, 26}
HEX   : possible_key[5] = {69, 6f, 6a, 6e, 6d, 25, 2b, 35, 27, 2f, 2c}
HEX   : possible_key[6] = {71, 74, 75, 73, 6a, 2a, 31, 36, 30, 3f, 3e}
HEX   : possible_key[7] = {20, 65, 74, 75, 69, 6f, 70, 61, 64, 66, 67, 68, 6a, 6b, 7a, 78, 63, 76, 6e, 6d, 23, 3d}
HEX   : possible_key[8] = {73, 2b, 39, 3b}
HEX   : possible_key[9] = {69, 6e, 25, 31, 30, 2f}
HEX   : possible_key[10] = {6d, 38}
HEX   : possible_key[11] = {5a, 72, 70, 32, 36}
HEX   : possible_key[12] = {6b, 6c, 6d, 2f}
HEX   : possible_key[13] = {65, 26, 29, 33, 37, 2d, 2e}
HEX   : possible_key[14] = {20, 72, 69, 73, 68, 7a, 26}
HEX   : possible_key[15] = {41, 69, 6b, 6c, 2a, 31, 39, 2f, 3c}
HEX   : possible_key[16] = {65, 66, 23, 28, 3d, 3f}
HEX   : possible_key[17] = {79, 7a, 32, 3d}
HEX   : possible_key[18] = {20, 65, 74, 79, 69, 6f, 61, 64, 66, 67, 68, 6a, 6b, 7a, 78, 63, 76, 62, 6d, 7c}
HEX   : possible_key[19] = {4c, 66, 23, 25, 28, 2b, 33, 35, 30, 27, 2f, 3f, 2e, 3c}
HEX   : possible_key[20] = {45, 6f, 68}
HEX   : possible_key[21] = {72, 30}
HEX   : possible_key[22] = {20, 6f, 6a, 78, 27, 22}
HEX   : possible_key[23] = {58}
HEX   : possible_key[24] = {0a, 09, 52, 4f, 53, 56, 4d}
HEX   : possible_key[25] = {52}
HEX   : possible_key[26] = {20, 6f, 66, 6c}
HEX   : possible_key[27] = {6f, 27}
HEX   : possible_key[28] = {70, 28, 33, 37, 3f}
HEX   : possible_key[29] = {65, 28, 2d, 2e}
HEX   : possible_key[30] = {58, 72, 39}
HEX   : possible_key[31] = {65, 61, 66, 67, 38}
HEX   : possible_key[32] = {77, 74, 70, 76, 28, 35, 3f, 3e, 2c}
HEX   : possible_key[33] = {69, 6a, 6d, 23, 2a, 2b, 33, 30, 3d, 22, 3f, 2e, 3c}
HEX   : possible_key[34] = {20, 72, 6f, 70, 6e, 21, 24, 25, 26, 2a, 28, 29, 2b, 33, 35, 36, 37, 39, 2d, 27, 22, 3f, 3b, 3a, 2e, 3c, 2c}
HEX   : possible_key[35] = {68, 6e, 27}
HEX   : possible_key[36] = {61, 68, 6c, 2e}
2020-03-19 18:09:41.703, 0x0x109ab9dc0 [WARN] SeakgHackXor::hackXor: Found several solutions, printed keys (Printable keys): 
String: possible_key[0] = {T}
String: possible_key[1] = {h, *, "}
String: possible_key[2] = {C, i, +, ;}
String: possible_key[3] = {s, 7}
String: possible_key[4] = { , u, z, &}
String: possible_key[5] = {i, o, j, n, m, %, +, 5, ', /, ,}
String: possible_key[6] = {q, t, u, s, j, *, 1, 6, 0, ?, >}
String: possible_key[7] = { , e, t, u, i, o, p, a, d, f, g, h, j, k, z, x, c, v, n, m, #, =}
String: possible_key[8] = {s, +, 9, ;}
String: possible_key[9] = {i, n, %, 1, 0, /}
String: possible_key[10] = {m, 8}
String: possible_key[11] = {Z, r, p, 2, 6}
String: possible_key[12] = {k, l, m, /}
String: possible_key[13] = {e, &, ), 3, 7, -, .}
String: possible_key[14] = { , r, i, s, h, z, &}
String: possible_key[15] = {A, i, k, l, *, 1, 9, /, <}
String: possible_key[16] = {e, f, #, (, =, ?}
String: possible_key[17] = {y, z, 2, =}
String: possible_key[18] = { , e, t, y, i, o, a, d, f, g, h, j, k, z, x, c, v, b, m, |}
String: possible_key[19] = {L, f, #, %, (, +, 3, 5, 0, ', /, ?, ., <}
String: possible_key[20] = {E, o, h}
String: possible_key[21] = {r, 0}
String: possible_key[22] = { , o, j, x, ', "}
String: possible_key[23] = {X}
String: possible_key[24] = {0x0a, 0x09, R, O, S, V, M}
String: possible_key[25] = {R}
String: possible_key[26] = { , o, f, l}
String: possible_key[27] = {o, '}
String: possible_key[28] = {p, (, 3, 7, ?}
String: possible_key[29] = {e, (, -, .}
String: possible_key[30] = {X, r, 9}
String: possible_key[31] = {e, a, f, g, 8}
String: possible_key[32] = {w, t, p, v, (, 5, ?, >, ,}
String: possible_key[33] = {i, j, m, #, *, +, 3, 0, =, ", ?, ., <}
String: possible_key[34] = { , r, o, p, n, !, $, %, &, *, (, ), +, 3, 5, 6, 7, 9, -, ', ", ?, ;, :, ., <, ,}
String: possible_key[35] = {h, n, '}
String: possible_key[36] = {a, h, l, .}
2020-03-19 18:09:41.708, 0x0x109ab9dc0 [WARN] SeakgHackXor::hackXor: Found several solutions, all possible combinations: 2013265920
```


