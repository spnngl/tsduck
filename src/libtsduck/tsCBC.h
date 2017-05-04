//----------------------------------------------------------------------------
//
// TSDuck - The MPEG Transport Stream Toolkit
// Copyright (c) 2005-2017, Thierry Lelegard
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//
//----------------------------------------------------------------------------
//!
//!  @file
//!  Cipher Block Chaining (CBC) mode.
//!
//----------------------------------------------------------------------------

#pragma once
#include "tsCipherChaining.h"

namespace ts {
    //!
    //! Cipher Block Chaining (CBC) mode.
    //!
    //! No padding is performed. The plain text and cipher text sizes must be
    //! multiples of the block size of the underlying block cipher.
    //!
    //! @tparam CIPHER A subclass of ts::BlockCipher, the underlying block cipher.
    //!
    template <class CIPHER>
    class CBC: public CipherChainingTemplate<CIPHER>
    {
    public:
        //!
        //! Constructor.
        //!
        CBC() : CipherChainingTemplate<CIPHER>(1, 1, 1) {}

        // Implementation of CipherChaining interface.
        virtual size_t minMessageSize() const {return this->block_size;}
        virtual bool residueAllowed() const {return false;}

        // Implementation of BlockCipher interface.
        virtual std::string name() const {return this->algo == 0 ? "" : this->algo->name() + "-CBC";}
        virtual bool encrypt(const void* plain, size_t plain_length,
                             void* cipher, size_t cipher_maxsize,
                             size_t* cipher_length = 0);
        virtual bool decrypt(const void* cipher, size_t cipher_length,
                             void* plain, size_t plain_maxsize,
                             size_t* plain_length = 0);
    };
}

#include "tsCBCTemplate.h"
