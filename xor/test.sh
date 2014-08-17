#!/bin/bash

./xor \
  ../test_data/example_text.txt \
  ../test_data/key.txt \
  ../test_data/encrypt_text.dat

./xor \
  ../test_data/encrypt_text.dat \
  ../test_data/key.txt \
  ../test_data/decrypt_text.txt



md5sum ../test_data/example_text.txt
md5sum ../test_data/decrypt_text.txt

