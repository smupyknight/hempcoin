#ifndef SCRYPT_H
#define SCRYPT_H
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "net.h"

static const int SCRYPT_SCRATCHPAD_SIZE = 131072 + 63;

void scrypt_1024_1_1_256(const uint8_t *input, uint8_t *output);
void scrypt_1024_1_1_256_sp_generic(const uint8_t *input, uint8_t *output, uint8_t *scratchpad);
uint256 scrypt_salted_multiround_hash(const uint8_t* input, size_t inputlen, const uint8_t* salt, size_t saltlen, const unsigned int nRounds);
uint256 scrypt_salted_hash(const uint8_t* input, size_t inputlen, const uint8_t* salt, size_t saltlen);
uint256 scrypt_blockhash(const uint8_t* input);

#if defined(USE_SSE2)
#include <string>
#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
#define USE_SSE2_ALWAYS 1
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_sse2((input), (output), (scratchpad))
#else
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_detected((input), (output), (scratchpad))
#endif

std::string scrypt_detect_sse2();
void scrypt_1024_1_1_256_sp_sse2(const uint8_t *input, uint8_t *output, uint8_t *scratchpad);
extern void (*scrypt_1024_1_1_256_sp_detected)(const uint8_t *input, uint8_t *output, uint8_t *scratchpad);
#else
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_generic((input), (output), (scratchpad))
#endif

void
PBKDF2_SHA256(const uint8_t *passwd, size_t passwdlen, const uint8_t *salt,
    size_t saltlen, uint64_t c, uint8_t *buf, size_t dkLen);

static inline uint32_t le32dec(const void *pp)
{
        const uint8_t *p = (uint8_t const *)pp;
        return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
            ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}

static inline void le32enc(void *pp, uint32_t x)
{
        uint8_t *p = (uint8_t *)pp;
        p[0] = x & 0xff;
        p[1] = (x >> 8) & 0xff;
        p[2] = (x >> 16) & 0xff;
        p[3] = (x >> 24) & 0xff;
}
#endif
