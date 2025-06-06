#include <inttypes.h>
#include <unistd.h>

#include "Hash.hh"
#include "Strings.hh"
#include "UnitTest.hh"

using namespace std;
using namespace phosg;

void check_string(const char* file, int line, const string& expected, const string& received) {
  if (expected != received) {
    fwrite_fmt(stderr, "({}:{}) Strings do not match; expected:\n", file, line);
    print_data(stderr, expected);
    fwrite_fmt(stderr, "Received:\n");
    print_data(stderr, received);
    throw logic_error("Strings do not match");
  }
}

int main(int, char**) {
  {
    fwrite_fmt(stdout, "-- crc32\n");
    expect_eq(0x00000000, crc32(nullptr, 0));
    expect_eq(0x00000000, crc32("", 0));
    expect_eq(0xD3D99E8B, crc32("A", 1));
    expect_eq(0xBF4FB41E, crc32("omg", 3));
    expect_eq(0xBB24C2E5, crc32("omg hax", 7));
    expect_eq(0x414FA339, crc32("The quick brown fox jumps over the lazy dog", 43));
  }

  {
    fwrite_fmt(stdout, "-- fnv1a32\n");
    expect_eq(0x811C9DC5, fnv1a32(nullptr, 0)); // technically undefined, but should work
    expect_eq(0x811C9DC5, fnv1a32("", 0));
    expect_eq(0x36E1DFD3, fnv1a32("omg hax", 7));
    expect_eq(0x0A73CA50, fnv1a32("lollercoaster", 13));
  }

  {
    fwrite_fmt(stdout, "-- fnv1a64\n");
    expect_eq(0xCBF29CE484222325, fnv1a64(nullptr, 0)); // technically undefined, but should work
    expect_eq(0xCBF29CE484222325, fnv1a64("", 0));
    expect_eq(0xE6CAC1F92EB65713, fnv1a64("omg hax", 7));
    expect_eq(0x594B81FB565E8D30, fnv1a64("lollercoaster", 13));
  }

  {
    fwrite_fmt(stdout, "-- md5\n");
    MD5 md5(nullptr, 0);
    check_string(__FILE__, __LINE__, string("\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E", 16), md5.bin());
    check_string(__FILE__, __LINE__, "D41D8CD98F00B204E9800998ECF8427E", md5.hex());
    md5 = MD5("", 0);
    check_string(__FILE__, __LINE__, string("\xD4\x1D\x8C\xD9\x8F\x00\xB2\x04\xE9\x80\x09\x98\xEC\xF8\x42\x7E", 16), md5.bin());
    check_string(__FILE__, __LINE__, "D41D8CD98F00B204E9800998ECF8427E", md5.hex());
    md5 = MD5("omg hax", 7);
    check_string(__FILE__, __LINE__, string("\xFA\xC7\xE1\x8E\xD6\x59\x9B\x37\x7C\x60\xF2\xCA\x94\xCC\xB4\x5B", 16), md5.bin());
    check_string(__FILE__, __LINE__, "FAC7E18ED6599B377C60F2CA94CCB45B", md5.hex());
    md5 = MD5("The quick brown fox jumps over the lazy dog", 43);
    check_string(__FILE__, __LINE__, string("\x9E\x10\x7D\x9D\x37\x2B\xB6\x82\x6B\xD8\x1D\x35\x42\xA4\x19\xD6", 16), md5.bin());
    check_string(__FILE__, __LINE__, "9E107D9D372BB6826BD81D3542A419D6", md5.hex());
  }

  {
    fwrite_fmt(stdout, "-- sha1\n");
    SHA1 sha1(nullptr, 0);
    check_string(__FILE__, __LINE__, string("\xDA\x39\xA3\xEE\x5E\x6B\x4B\x0D\x32\x55\xBF\xEF\x95\x60\x18\x90\xAF\xD8\x07\x09", 20), sha1.bin());
    check_string(__FILE__, __LINE__, "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709", sha1.hex());
    sha1 = SHA1("", 0);
    check_string(__FILE__, __LINE__, string("\xDA\x39\xA3\xEE\x5E\x6B\x4B\x0D\x32\x55\xBF\xEF\x95\x60\x18\x90\xAF\xD8\x07\x09", 20), sha1.bin());
    check_string(__FILE__, __LINE__, "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709", sha1.hex());
    sha1 = SHA1("omg hax", 7);
    check_string(__FILE__, __LINE__, string("\x6A\x30\xD0\x34\x3E\xD1\x31\x36\x96\xD2\x0B\xCC\x25\xFA\x7E\x2A\xD5\xA9\x77\x7F", 20), sha1.bin());
    check_string(__FILE__, __LINE__, "6A30D0343ED1313696D20BCC25FA7E2AD5A9777F", sha1.hex());
    sha1 = SHA1("The quick brown fox jumps over the lazy dog", 43);
    check_string(__FILE__, __LINE__, string("\x2F\xD4\xE1\xC6\x7A\x2D\x28\xFC\xED\x84\x9E\xE1\xBB\x76\xE7\x39\x1B\x93\xEB\x12", 20), sha1.bin());
    check_string(__FILE__, __LINE__, "2FD4E1C67A2D28FCED849EE1BB76E7391B93EB12", sha1.hex());
  }

  {
    fwrite_fmt(stdout, "-- sha256\n");
    SHA256 sha256(nullptr, 0);
    check_string(__FILE__, __LINE__, string("\xE3\xB0\xC4\x42\x98\xFC\x1C\x14\x9A\xFB\xF4\xC8\x99\x6F\xB9\x24\x27\xAE\x41\xE4\x64\x9B\x93\x4C\xA4\x95\x99\x1B\x78\x52\xB8\x55", 32), sha256.bin());
    check_string(__FILE__, __LINE__, "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", sha256.hex());
    sha256 = SHA256("", 0);
    check_string(__FILE__, __LINE__, string("\xE3\xB0\xC4\x42\x98\xFC\x1C\x14\x9A\xFB\xF4\xC8\x99\x6F\xB9\x24\x27\xAE\x41\xE4\x64\x9B\x93\x4C\xA4\x95\x99\x1B\x78\x52\xB8\x55", 32), sha256.bin());
    check_string(__FILE__, __LINE__, "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855", sha256.hex());
    sha256 = SHA256("omg hax", 7);
    check_string(__FILE__, __LINE__, string("\xC8\xFE\x90\x95\x16\x38\x92\x36\x7A\x31\xCE\xC8\x90\x25\xA8\xD8\x39\x4B\x47\x4D\x38\x8F\x10\xD4\x7A\x0F\xCC\x02\x19\xA7\x74\x30", 32), sha256.bin());
    check_string(__FILE__, __LINE__, "C8FE9095163892367A31CEC89025A8D8394B474D388F10D47A0FCC0219A77430", sha256.hex());
    sha256 = SHA256("The quick brown fox jumps over the lazy dog", 43);
    check_string(__FILE__, __LINE__, string("\xD7\xA8\xFB\xB3\x07\xD7\x80\x94\x69\xCA\x9A\xBC\xB0\x08\x2E\x4F\x8D\x56\x51\xE4\x6D\x3C\xDB\x76\x2D\x02\xD0\xBF\x37\xC9\xE5\x92", 32), sha256.bin());
    check_string(__FILE__, __LINE__, "D7A8FBB307D7809469CA9ABCB0082E4F8D5651E46D3CDB762D02D0BF37C9E592", sha256.hex());

    // MySQL caching_sha2_password challenge/response test (password = "root")
    string nonce = "\x15\x52\x16\x70\x06\x75\x22\x18\x77\x43\x53\x14\x71\x01\x43\x25\x53\x1F\x6A\x14";
    string password_sha256 = SHA256("root").bin();
    string password_sha256_sha256 = SHA256(password_sha256).bin();
    string hash_with_nonce = SHA256(password_sha256_sha256 + nonce).bin();
    string result(0x20, '\0');
    for (size_t x = 0; x < result.size(); x++) {
      result[x] = password_sha256[x] ^ hash_with_nonce[x];
    }
    expect_eq(result, "\x1A\xE1\x80\xD5\xE5\xDB\x7F\xDF\x59\xEA\x73\x91\xB6\x5E\x25\x16\x73\xE1\xB0\x01\xC1\x50\xAA\x3A\x48\xDC\x78\x48\x8B\x4B\x70\xC4");
  }

  fwrite_fmt(stdout, "HashTest: all tests passed\n");
  return 0;
}
