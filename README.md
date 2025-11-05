# XOR Crypter

A **XOR encryption tool** written in C.  
This program takes a plaintext message and a user-defined key, performs XOR encryption, and outputs the encrypted data in **hexadecimal format**.

## Overview

This project demonstrates a fundamental concept of symmetric encryption using the XOR operation.  
It’s a minimal and educational example, ideal for understanding how basic encryption mechanisms work at the byte level.

The current version:
- Takes a **message** (plaintext input)
- Takes a **key** (string)
- Produces a **hexadecimal output** after applying XOR encryption

## Compilation

- `gcc functions.c main.c -o xor_crypter`

## Usage

- `./xor_crypter [-h], [--help]: Prints this.`
- `./xor_crypter [-m <MESSAGE>]: Reads message from stdin.`
- `./xor_crypter [-M <FILE>]:    Reads message from file.`
- `./xor_crypter [-k <KEY>]:     Reads message from stdin.`
- `./xor_crypter [-K <FILE>]:    Reads key from file.`
- `./xor_crypter [-d DECRYPT]:   Enables decrypt mode.`
- `./xor_crypter [-o OUTPUT]:    Outputs result in a file.`
- `./xor_crypter [--debug] enables debug output (key/message size information).`
- `./xor_crypter [--examples] Show examples of how to use.`
