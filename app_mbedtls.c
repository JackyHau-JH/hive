#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "mbedtls/build_info.h"
#include "mbedtls/platform.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/sha256.h"
#include "mbedtls/x509_crt.h"
#include "mbedtls/pk.h"

#include "app_mbedtls.h"

static void dump_buf(const char *title, unsigned char *buf, size_t len)
{
    size_t i;

    mbedtls_printf("%s", title);
    for (i = 0; i < len; i++)
    {
        mbedtls_printf("%c%c", "0123456789ABCDEF"[buf[i] / 16],
                       "0123456789ABCDEF"[buf[i] % 16]);
    }
    mbedtls_printf("\n");
}

static void dump_pubkey(const char *title, mbedtls_ecdsa_context *key)
{
    unsigned char buf[300];
    size_t len;

    if (mbedtls_ecp_write_public_key(key, MBEDTLS_ECP_PF_UNCOMPRESSED,
                                     &len, buf, sizeof(buf)) != 0)
    {
        mbedtls_printf("internal error\n");
        return;
    }

    dump_buf(title, buf, len);
}

int my_f_rng(void *x, unsigned char *rnbuf, size_t n)
{
    return 0;
}

int my_test(int n)
{
    while (n)
    {
        printf("n is %d\n", n);
        n--;
    }

    return 0;
}

void app_mbedtls_run(void)
{

    int ret;
    uint8_t data[] = "hello world"; // 要签名的数据
    uint8_t hash[32];
    uint8_t sig[256];   // 签名缓冲区
    size_t sig_len = 0; // SHA256 输出
    mbedtls_pk_context ec_prik_ctx;

    my_test(5);

    // ------------- 新增：RNG 初始化 -------------
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    const char *pers = "ecdsa_sign"; // 自定义字符串，随便写

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    // 初始化随机数发生器
    mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                          (const unsigned char *)pers, strlen(pers));

    mbedtls_pk_init(&ec_prik_ctx);
    ret = mbedtls_pk_parse_keyfile(&ec_prik_ctx, "/home/mike/hive/util_keys/client.key", NULL, NULL, NULL);

    if (ret != 0)
    {
        printf("mbedtls_pk_parse_keyfile failed\n");
    }

    int fd;
    fd = open("/home/mike/hive/util_keys/hash.bin", O_WRONLY);
    if (fd < 0)
    {
        printf("open hash.bin failed\n");
    }

    write(fd, hash, 32);
    close(fd);

    ret = mbedtls_sha256(data, strlen((char *)data), hash, 0);

    if (ret != 0)
    {
        printf("mbedtls_sha256 failed\n");
    }

    // 4. ✅ 执行 ECDSA 签名（核心函数）
    ret = mbedtls_pk_sign(&ec_prik_ctx, MBEDTLS_MD_SHA256, hash, 32, sig, 256, &sig_len, mbedtls_ctr_drbg_random, &ctr_drbg);
    if (ret == 0)
    {
        printf("签名成功！长度：%zu\n", sig_len);

        fd = open("/home/mike/hive/util_keys/sig.bin", O_WRONLY);
        if (fd < 0)
        {
            printf("open sig.bin failed\n");
        }

        write(fd, sig, sig_len);
        close(fd);
    }
    else
    {
        printf("sign failed\n");
    }

    // int mbedtls_pk_verify(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
    //                      const unsigned char *hash, size_t hash_len,
    //                    const unsigned char *sig, size_t sig_len)

    mbedtls_pk_init(&ec_prik_ctx);
    ret = mbedtls_pk_parse_keyfile(&ec_prik_ctx, "/home/mike/hive/util_keys/client.key", NULL, NULL, NULL);

    if (ret != 0)
    {
        printf("mbedtls_pk_parse_keyfile failed\n");
    }
    ret = mbedtls_pk_verify(&ec_prik_ctx, MBEDTLS_MD_SHA256, hash, 32, sig, sig_len);

    if (ret != 0)
    {
        printf("mbedtls_pk_verify failed\n");
    }
    else
    {
        printf("mbedtls_pk_verify ok\n");
    }

#if 0


mbedtls_x509_crt client_crt;
mbedtls_x509_crt_init(&client_crt);


//mbedtls_x509_crt_parse

int ret = mbedtls_x509_crt_parse_file(&client_crt,"D:\\etec\\mbedtls_test\\client.crt");

if(ret != 0)
{
printf("mbedtls_x509_crt_parse_file error\r\n");

}
else
{
printf("mbedtls_x509_crt_parse_file ok\r\n");

}

#endif
}