/*
Notes owner: Helen Deng, yiman@stanford.edu
Winter 2023, Stanford CS107 Week 1 notes for self-study only. 
These notes reflect more of personal interest than syllabus material.

    1. how are integers represented in computers
    2. boolean algebra
    3. data types & sizes
    4. a basic c program
    5. Unix commands
    6. emacs editor
*/

#include <bits/stdc++.h>
using namespace std;

/*
1. how are integers represented in computers
    - binary bits
    - two's complement
        For representing signed int;
        Top most bit is the negative power of 2, rest of which are positive;
        In practice: [negative binary of num] = ~[positive binary of num] + 1;
        Trick: go from right until you get a 1, then flip all the bits to the left;
        If you want to go from negative to positive, you can do the same thing;
        Works well for computers, all nums are unique, no 2 zeros, can add and subtract;
        All 1s is either the MAX in unsigned int, or -1 in signed int.
        Biggest positive signed int is 0 followed by all 1s.
    - -1       | 11111111 11111111 11111111 11111111
      INT_MAX  | 01111111 11111111 11111111 11111111
      INT_MIN  | 10000000 00000000 00000000 00000000
      UINT_MAX | 11111111 11111111 11111111 11111111
    - conversion between different base: 16 - 2 - 10
        0 - 0000 - 0,    1 - 0001 - 1,    2 - 0010 - 2,    3 - 0011 - 3
        4 - 0100 - 4,    5 - 0101 - 5,    6 - 0110 - 6,    7 - 0111 - 7
        8 - 1000 - 8,    9 - 1001 - 9,    a - 1010 - 10,   b - 1011 - 11
        c - 1100 - 12,   d - 1101 - 13,   e - 1110 - 14,   f - 1111 - 15
*/
string unsigned_binary_addition(string bin1, string bin2) {
    if (bin1.size() < bin2.size()) return unsigned_binary_addition(bin2, bin1);
    else {
        bin2 = string(bin1.size() - bin2.size(), '0') + bin2;
        int sum = 0, carry = 0;
        string sol = "";
        for (int i=bin1.size()-1; i>=0; i--) {
            int sum = carry + (bin1[i]-'0') + (bin2[i]-'0');
            carry = (sum >= 2) ? 1 : 0;
            sol += to_string(sum%2);
        }
        if (carry) sol += '1';
        reverse(sol.begin(), sol.end());
        return sol;
    }
}

string unsigned_binary_subtraction(string bin1, string bin2) {
    if (bin1.size() < bin2.size()) return "Error: minuend is shorter than subtrahend.";
    else {
        bin2 = string(bin1.size() - bin2.size(), '0') + bin2;
        int diff = 0, borrow = 0;
        string sol = "";
        for (int i=bin1.size()-1; i>=0; i--) {
            diff = (bin1[i] - '0') - (bin2[i] - '0') - borrow;
            borrow = 0;
            if (diff < 0) {
                diff += 2;
                borrow = 1;
            }
            sol += (char)(diff + '0');
        }
        reverse(sol.begin(), sol.end());
        return sol;
    }
}

long binary_to_decimal(long bin) {
    int sol = 0, counter = 0;
    while (bin) {
        if (bin%2) sol += pow(2, counter);
        bin /= 10;
        counter++;
    }
    return sol;
}

string decimal_to_binary(int dec) {
    string sol = "";
    while (dec) {
        sol += to_string(dec%2);
        dec >>= 1;
    }
    reverse(sol.begin(), sol.end());
    return sol;
}

string decimal_to_hex(int dec) {
    string sol = "";
    char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (dec) {
        sol += hex_digits[dec % 16];
        dec /= 16;
    }
    reverse(sol.begin(), sol.end());
    return sol;
}

/*
2. boolean algebra / bitwise manipulation
    - In c, there is no boolean, only ints, any number other than 0 is true;
        AND &, OR |, XOR ^, NOT ~
        << left shift (same effect as appending 00 in binary), >> right shift;
    - bit masking
        e.g. the mask of 0xFF means the lowest byte in an integer, 11111111 in binary;
*/
int j = 0x89ABCDEF;
int k = j & 0xFF; // k now holds the value 0xEF, which is the low-order byte of j
int all_ones = ~0; // makes an integer with all 1s

#define isOn(S, j) (S & (1<<j))
#define setBit(S, j) (S |= (1<<j))
#define clearBit(S, j) (S &= ~(1<<j))
#define toggleBit(S, j) (S ^= (1<<j))
#define lowBit(S) (S & (-S)) // same as (S & ~(S-1))
#define setAll(S, n) (S = (1<<n)-1) // set all bits in a set of size n

#define modulo(S, N) ((S) & (N-1))   // returns S % N, where N is a power of 2
#define isPowerOfTwo(S) (!(S & (S-1)))
#define nearestPowerOfTwo(S) (1<<lround(log2(S)))
#define turnOffLastBit(S) ((S) & (S-1))
#define turnOnLastZero(S) ((S) | (S+1))
#define turnOffLastConsecutiveBits(S) ((S) & (S+1))
#define turnOnLastConsecutiveZeroes(S) ((S) | (S-1))

1 << x // 2 to the power x
~x + 1 // -x, arithmetic negation
x >> 31 // -1 if x is negative, 0 otherwise
x &= (x - 1) // clears lowest "on" bit in x
(x ^ y) < 0 // true if x and y have opposite signs

/*
3. data types & sizes
    - data sizes (for 64-bit UNIX applications)
        32-bit vs 64-bit: on myth machines, all pointers are 64-bit long. Pointer points to an individual byte of 8 bits. A 64-bit machine can address up to 2^64 bytes of memory, 4 billion times more than 32-bit machine. 
    - how is a byte stored in memory
        ordering of bytes in 4-byte hex numbers: store the bytes ordered from LSB is called "little endian," ordered from MSB is called "big endian."
        e.g. represent an int as a hex number 0x01234567, separate the bytes
        Small endian in computers:
            address: 0x100 0x101 0x102 0x103
            value:   67    45    23    01
    - sizeof(variable), returns size in bytes of that type
        type name	size (in bits)	size (in bytes) 
        char	        8	            1
        short	        16	            2  
        int	            32	~10e9       4
        long	        64	~10e18      8
        float           32              4
        double          64              8
    - use <limit.h> to access MIN and MAX of the types
    - for signed int, the first bit in front indicates sign, 0 for +, 1 for -
    - when comparing an int to unsigned, put them on the number wheel and compare the position of the two. The sign doesn't matter.
    - casting
        When casting between signed and unsigned, the underlying bits don't change;
    - expanding the bit representation of a number
        For unsigned, "zero-extension," simply add leading zeros;
        For signed, "sign-extension," repeating the sign of the value for the new digits;
    - truncating numbers
        casting to a smaller size data type, don't have enough bits to store, may result in overflow and change the value;
*/

/*
4. a basic c program
    - #include and #define
    - argc, argv
        argc, always at least one;
        argv, array of command line arguments (strings), first one is program name
    - error handling
        <error.h> void error(int status, int errnum, const char *format, ...);
        <errno.h>
    - printf format specifiers
        %d, signed 32-bit integer;
        %u, unsigned 32-bit integer; 
        %x, unsiged dexadecimal 32-bit integer;
        %c,	a single-byte sharacter
*/
#include <stdio.h> // for printf()
#include <stdlib.h> // for stoi()
#include <errno.h> // for error handling

#define MY_NUM 9
#define MY_NAME "Helen"
#define min(X, Y) (X<Y ? X : Y)

int example_main(int argc, char *argv[]) {
    int num = MY_NUM;
    if (argc == 2) {
        num = atoi(argv[1]);
        if (num < 0 || num > 100) {
            fprintf(stderr, "Error: input number must be between 0 and 100 inclusive.\n");
            return 1;
        }
        for (int i = 0; i < num; i++) {
            printf("%s's lucky number is %d\n", MY_NAME, num);
        }
    } else if (argc > 2) {
        fprintf(stderr, "Error: there can only be one input number.\n");
        return 1;
    }
    return 0;
}

/*
5. Unix commands
    - Unix is an operating system. It defines the commands and system calls you are allowed to make in the terminal.
    - Navigation
        tree
            recursive directory listing;
        man
           display manual of command; press q to quit;
        cd
            ~ to home directory;
            .. to parent diirectory;
            . to current directory;
        ls -al
            a means list hidden files;
            l means list extra information;
    - Create & Delete
        mkdir /file_path
            make directory at file_path;
        cp -r /file_path_1 /file_path 2
            copy files;
        mv /file_path_1 /file_path_2
            move/rename files;
        rm -rf /file_path
            r means recursive, so apply command to everuthing in that directory; 
            f means remove with force;
            use rmdir for directories;
    - Print, Search, Compare
        cat
            print out contents of files;
        grep "pattern" /file_path
            search files and print lines that include pattern;
            pattern can have "*~", which means everything that ends with ~;
        find /directory -name "*.c"
            search directory and print lines of files with specified name;
        diff file_path_1 file_path_2
            print the difference in contents of the two files;
    - Manipulating Input & Output
        command > out.txt
            saves text output of command to out.txt;
            use >> to append the output to an already existing file;
        command < in.txt
            send text contents of a file as input to a command;
        command_1 | command_2
            make output of command-1 the input of command_2;
    - Edit & Run
        emacs /file_path
            open and edit file_path in emacs;
        make
            compiles;
        ./program_name
            to run an executable;
        command+t
            open up a new terminal tab;
*/

/*
6. emacs editor
    - emacs is like an app, a text editor that lets you edit files on any OS.
        ctrl-x ctrl-s 
            to save
        ctrl-x ctrl-c 
            to exit
*/
