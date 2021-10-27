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

#ifndef HD_KEYRING_H
#define HD_KEYRING_H

#include <bitcoin/bitcoin.hpp>
#include <string.h>

using namespace bc;
using std::string;

class HD_KeyRing
{

public:
    HD_KeyRing();
    HD_KeyRing(const string &);
    ~HD_KeyRing();

    data_chunk generate_seed();
    wallet::hd_private generate_private_key(data_chunk &);
    wallet::hd_public generate_public_key(const libbitcoin::wallet::hd_private &);
    wallet::payment_address generate_payment_address(const int &);
    wallet::hd_private child_private_Key(const int &);
    wallet::hd_public child_public_Key(const int &);
    wallet::word_list generate_mnemonic_word_list(const data_chunk &);
    wallet::hd_private hd_private_from_mnemonic_file(const std::string &);
    void create_mnemonic_word_list_storage_file(const wallet::word_list &, const string &);

private:
    wallet::hd_private m_privateKey;
    wallet::hd_public m_publicKey;
    wallet::word_list m_mnemonic;
};

#endif // HD_KEYRING_H