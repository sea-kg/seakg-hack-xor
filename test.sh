
#!/bin/bash

mkdir -p tmp.data

echo ""
echo "CHECK XOR"
./seakg-hack-xor xor data/example_text_english.txt data/example_key_simple.txt tmp.data/encrypted_text
./seakg-hack-xor xor tmp.data/encrypted_text data/example_key_simple.txt tmp.data/decrypted_text.txt
md5sum data/example_text_english.txt
md5sum tmp.data/encrypted_text
md5sum tmp.data/decrypted_text.txt


echo ""
echo "TRY HACK"
./seakg-hack-xor hack tmp.data/encrypted_text 37 data/alphabet256 data/alphabet_text_english

echo ""
echo "TRY HACK2"
./seakg-hack-xor xor data/example_text_english_small.txt data/example_key_simple.txt tmp.data/encrypted_text2
./seakg-hack-xor hack tmp.data/encrypted_text2 37 data/alphabet_text_english data/alphabet_text_english