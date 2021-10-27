// The MIT License (MIT)

// Copyright (c) 2020 Chris Kazas

//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.

/* Hierarchical Deterministic Key Ring based on libbitcoin */

#include <bitcoin/bitcoin.hpp>
#include <fstream>
#include <string.h>

#include "HD_KeyRing.h"

using namespace bc;
using std::string;

// Generate new Key ring
HD_KeyRing::HD_KeyRing()
{
    auto seed = generate_seed();
    m_mnemonic = generate_mnemonic_word_list(seed);
    m_privateKey = generate_private_key(seed);
    m_publicKey = generate_public_key(m_privateKey);
}

// Import existing Key Ring
HD_KeyRing::HD_KeyRing(const string &owner)
{
    m_privateKey = hd_private_from_mnemonic_file(owner);
    m_publicKey = m_privateKey.to_public();
}

HD_KeyRing::~HD_KeyRing()
{
}

// Generate seed chunk
// Returns std::vector<uint8_t>
data_chunk HD_KeyRing::generate_seed()
{
    data_chunk seedChunk(16);
    pseudo_random_fill(seedChunk);
    return seedChunk;
}

// Generate private key
libbitcoin::wallet::hd_private HD_KeyRing::generate_private_key(data_chunk &seed)
{
    pseudo_random_fill(seed);
    auto privateKey = wallet::hd_private(seed);
    return privateKey;
}

// Derive public key from master private key
wallet::hd_public HD_KeyRing::generate_public_key(const libbitcoin::wallet::hd_private &privateKey)
{
    return privateKey.to_public();
}

// Derive child private key
wallet::hd_private HD_KeyRing::child_private_Key(const int &index)
{
    return m_privateKey.derive_private(index);
}

// Derive child public key
wallet::hd_public HD_KeyRing::child_public_Key(const int &index)
{
    return m_publicKey.derive_public(index);
}

// Generate payment address
wallet::payment_address HD_KeyRing::generate_payment_address(const int &index)
{
    return wallet::ec_public(child_public_Key(index).point()).to_payment_address();
}

// Generate menomic word list from private key
wallet::word_list HD_KeyRing::generate_mnemonic_word_list(const data_chunk &seed)
{
    return wallet::create_mnemonic(seed);
}

// Import mnemonic word list from file and return HD Private Key
wallet::hd_private HD_KeyRing::hd_private_from_mnemonic_file(const string &fileLoc)
{

    std::ifstream in{fileLoc};
    string mnemonicSeed{};
    if (in.good())
    {
        for (char c = in.get(); in.good(); c = in.get())
        {
            mnemonicSeed += c;
        }
    }

    wallet::word_list wl = split(mnemonicSeed, "\n");
    auto chunk = to_chunk(wallet::decode_mnemonic(wl));

    return wallet::hd_private(chunk);
}

// creates mnemonic word list and writes to file for storage *will be encrypted in future*
void HD_KeyRing::create_mnemonic_word_list_storage_file(const wallet::word_list &wl, const string &file_loc)
{
    std::ofstream out_file(file_loc);
    if (!out_file)
    {
        std::cerr << "Error: Some bad shit happened bro"
                  << "\n";
    }
    else
    {
        out_file << wl;
    }
}
