# Questions

## What's `stdint.h`?
### stdint.h is a header file in the C standard library that allows programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined min and max allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
### using the above specifies the size of the type to prevent error for software/systems that may define the types differently. For instance an int can be 8 bits, 16 bits or 32 bits because the size of types is not defined in C. itself.
### aliases for C primitive data types. typedefs: uint8_t  BYTE; uint32_t DWORD; int32_t  LONG;uint16_t WORD;

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
### 1 byte = 8 bits; dword = 32 bits, 4 bytes; long = 32 bits, 8 bytes ; word = 16 bits, 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
### B M

## What's the difference between `bfSize` and `biSize`?
### bfSize is the size of the whole bmp file, which includes the headerfiles
### biSize is the size of the BITMAPINFOHEADER header file and always = 40 bytes for BMP

## What does it mean if `biHeight` is negative?
### If biHeight is negative, the bitmap is a top-down with the origin at the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
### biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
### The file may not exist or has permissions that prevent current user from opening

## Why is the third argument to `fread` always `1` in our code?
### because can only 'read' one item

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
### 3

## What does `fseek` do?
### allows you to rewind or fast forward in a file; move file pointer assiociated w specific file to a specific location

## What is `SEEK_CUR`?
### denotes file pointer's current position
