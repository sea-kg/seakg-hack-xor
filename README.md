# seakg-hack-xor

1. Crypt file use a xor
2. Try hack xor crypt (trying calculate passphrase) for xor crypt

## Build

Requirements for build (MacOS):
```
$ brew install pkg-config cmake
```

Requirements for build (Ubuntu/Debian):
```
$ sudo apt install cmake make g++ pkg-config git-core
```

## Run && Usage

Crypt file
```
$ ./seakg-hack-xor xor orig_filepath key_filepath crypted_filepath
```

Decrypt file
```
$ ./seakg-hack-xor xor crypted_filepath key_filepath orig_filepath
```

## Integrate to your project via wsjcpp

```
$ wsjcpp install https://github.com/sea-kg/seakg-hack-xor:master
```


## hackxor

(must be installed Qt 4.7 and later )

Building:
	$ cd ../hackxor
	$ qmake
	$ make

for hack xor:
./hackxor <input file> <length key> <alphabet key file> <alphabet text file>




