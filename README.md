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

- `gcc xor_crypter.c -o xor_crypter`

## Usage

- `./xor_crypter -k [KEY] -m [MESSAGE] --ml [MSG_LENGTH] --kl [KEY_LENGTH]`
- `./xor_crypter -k [KEY] -m [HEX] --ml [MSG_LENGTH] --kl [KEY_LENGTH] -d [DECRYPT]`
