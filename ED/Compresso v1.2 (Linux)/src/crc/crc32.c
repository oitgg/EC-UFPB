#include "crc32.h"

static uint32_t crc_table[256];

void generate_crc32_table()
{
    uint32_t rem;
    int i;
    int j;

    /* Calcula a tabela CRC */
    for (i = 0; i < 256; i++)
    {
        rem = i;  /* restante de divisão polinomial */
        for (j = 0; j < 8; j++)
        {
            if (rem & 1)
            {
                rem >>= 1;
                rem ^= POLY_REVERSED;
            }
            else
                rem >>= 1;
        }
        crc_table[i] = rem;
    }
}

uint32_t crc32(uint32_t crc, const void *buf, uint64_t len)
{
    uint8_t octet;
    const uint8_t *p;
    const uint8_t *q;

    crc = ~crc;
    q = (uint8_t*)buf + len;
    for (p = (uint8_t*)buf; p < q; p++)
    {
        octet = *p;
        crc = (crc >> 8) ^ crc_table[(crc & 0xff) ^ octet];
    }
    return ~crc;
} 