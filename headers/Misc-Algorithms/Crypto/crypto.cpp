#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cassert>

// SHA-256 constants
const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

class Crypto {

public:
    static std::string sha256(const std::string &data) {
        uint32_t h[] = {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };

        std::vector<uint8_t> padded_data = pad(data);

        for (size_t i = 0; i < padded_data.size(); i += 64) {
            uint32_t w[64];
            std::memcpy(w, &padded_data[i], 64);

            for (int t = 16; t < 64; ++t) {
                uint32_t s0 = rotr(w[t-15], 7) ^ rotr(w[t-15], 18) ^ (w[t-15] >> 3);
                uint32_t s1 = rotr(w[t-2], 17) ^ rotr(w[t-2], 19) ^ (w[t-2] >> 10);
                w[t] = w[t-16] + s0 + w[t-7] + s1;
            }

            uint32_t a = h[0];
            uint32_t b = h[1];
            uint32_t c = h[2];
            uint32_t d = h[3];
            uint32_t e = h[4];
            uint32_t f = h[5];
            uint32_t g = h[6];
            uint32_t h_val = h[7];

            for (int t = 0; t < 64; ++t) {
                uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
                uint32_t ch = (e & f) ^ ((~e) & g);
                uint32_t temp1 = h_val + S1 + ch + k[t] + w[t];
                uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
                uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
                uint32_t temp2 = S0 + maj;

                h_val = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
            h[5] += f;
            h[6] += g;
            h[7] += h_val;
        }

        std::ostringstream result;
        for (uint32_t val : h) {
            result << std::hex << std::setw(8) << std::setfill('0') << val;
        }

        return result.str();
    }

    //md5
    static std::string md5(const std::string &data) {

    }

    //sha1
    static std::string sha1(const std::string &data) {

    }

    //sha384
    static std::string sha384(const std::string &data) {

    }

    //base64
    static std::string base64(const std::string &data) {

    }

    //blowfish
    static std::string blowfish(const std::string &data) {
    
    }

    //rsa
    static std::string rsa(const std::string &data) {

    }

private:
    static std::vector<uint8_t> pad(const std::string &data) {
        size_t original_length = data.size();
        size_t new_length = ((original_length + 8) / 64 + 1) * 64;
        std::vector<uint8_t> padded_data(new_length, 0);

        std::memcpy(padded_data.data(), data.data(), original_length);
        padded_data[original_length] = 0x80;

        uint64_t bit_length = original_length * 8;
        for (size_t i = 0; i < 8; ++i) {
            padded_data[new_length - 1 - i] = (bit_length >> (8 * i)) & 0xff;
        }

        return padded_data;
    }

    static uint32_t rotr(uint32_t x, uint32_t n) {
        return (x >> n) | (x << (32 - n));
    }
};

//sha256, md5, sha1, sha512, sha224, sha384
