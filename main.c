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
 
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

static void dump_buf(const char *title, unsigned char *buf, size_t len)
{
    size_t i;

    mbedtls_printf("%s", title);
    for (i = 0; i < len; i++) {
        mbedtls_printf("%c%c", "0123456789ABCDEF" [buf[i] / 16],
                       "0123456789ABCDEF" [buf[i] % 16]);
    }
    mbedtls_printf("\n");
}

static void dump_pubkey(const char *title, mbedtls_ecdsa_context *key)
{
    unsigned char buf[300];
    size_t len;

    if (mbedtls_ecp_write_public_key(key, MBEDTLS_ECP_PF_UNCOMPRESSED,
                                     &len, buf, sizeof(buf)) != 0) {
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
    while(n)
    {
        printf("n is %d\n",n);
         n--;

    }

    return 0;
 }



#define ECPARAMS    MBEDTLS_ECP_DP_SECP256R1




#if 0
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
 

// 画实心圆函数（通用）
void DrawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}



// 渲染文字到屏幕居中
void DrawTextCenter(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color)
{
    // 生成文字表面
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect;
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

#endif















int main(int argc,char*argv[]) 
{

//------------------------------------------------------------------------

#if 0
FILE *fp;
fp = fopen("/home/mike/ws_mbedtls/client.crt","rb");

if(fp == NULL)
{
printf("fopen error\r\n");

}
else
{
    printf("fopen ok\r\n");
}
perror("fopen");
return 0;
#endif





#if 0

SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();   // 初始化字体

    SDL_Window* window = SDL_CreateWindow(
        "圆上显示文字",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
    // 加载中文字体 换成你实际的字体路径
    TTF_Font* font = TTF_OpenFont("D:\\etec\\mbedtls_test\\Simhei.ttf", 36);
    if (!font) {
        printf("字体加载失败\n");
        return -1;
    }

    SDL_Color textColor = {255, 255, 255, 255}; // 白色文字

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        // 清屏黑色
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 画红色实心圆
        DrawFilledCircle(renderer, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 120, 255, 0, 0);

        // 在圆正中间画：on 开
        DrawTextCenter(renderer, font, "on 开", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, textColor);

        SDL_RenderPresent(renderer);
    }
    

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;



#endif

















#if 1

int ret;
 uint8_t data[] = "hello world";         // 要签名的数据
    uint8_t hash[32];  
        uint8_t sig[256];                       // 签名缓冲区
    size_t sig_len = 0;                    // SHA256 输出
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
ret = mbedtls_pk_parse_keyfile(&ec_prik_ctx, "/home/mike/ws_mbedtls/client.key", NULL, NULL, NULL);

   if (ret != 0) {
        printf("mbedtls_pk_parse_keyfile failed\n");
    }

int fd;
fd = open("/home/mike/ws_mbedtls/hash.bin",O_WRONLY);
if(fd < 0)
{
    printf("open hash.bin failed\n");
}

write(fd,hash,32);
close(fd);

ret = mbedtls_sha256(data, strlen((char*)data), hash, 0);

  if(ret != 0) {
        printf("mbedtls_sha256 failed\n");
    }






    // 4. ✅ 执行 ECDSA 签名（核心函数）
    ret = mbedtls_pk_sign(&ec_prik_ctx, MBEDTLS_MD_SHA256,hash, 32,sig, 256,&sig_len, mbedtls_ctr_drbg_random, &ctr_drbg);
    if(ret == 0) {
        printf("签名成功！长度：%zu\n", sig_len);


fd = open("/home/mike/ws_mbedtls/sig.bin",O_WRONLY);
if(fd < 0)
{
    printf("open sig.bin failed\n");
}

write(fd,sig,sig_len);
close(fd);






    }
    else
    {
        printf("sign failed\n");
    }




//int mbedtls_pk_verify(mbedtls_pk_context *ctx, mbedtls_md_type_t md_alg,
 //                     const unsigned char *hash, size_t hash_len,
   //                   const unsigned char *sig, size_t sig_len)

mbedtls_pk_init(&ec_prik_ctx);
ret = mbedtls_pk_parse_keyfile(&ec_prik_ctx, "/home/mike/ws_mbedtls/client.key", NULL, NULL, NULL);

   if (ret != 0) {
        printf("mbedtls_pk_parse_keyfile failed\n");
    }
ret =  mbedtls_pk_verify(&ec_prik_ctx, MBEDTLS_MD_SHA256, hash, 32,sig, sig_len);


  if(ret != 0) {
        printf("mbedtls_pk_verify failed\n");
    }
    else
    {
        printf("mbedtls_pk_verify ok\n");
    }




#endif
















#if  0


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




//------------------------------------------------------------------------
























//---------------------------------------------------------------------------------------
#if 0



    //const char *data = "Hello MbedTLS 3.6.3";
    //unsigned char output[32];


    int ret = 1;
    int exit_code = MBEDTLS_EXIT_FAILURE;
    mbedtls_ecdsa_context ctx_sign, ctx_verify;
    mbedtls_ecp_point Q;
    mbedtls_ecp_point_init(&Q);
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    unsigned char message[100];
    unsigned char hash[32];
    unsigned char sig[MBEDTLS_ECDSA_MAX_LEN];
    size_t sig_len;
    const char *pers = "ecdsa";
    ((void) argv);
  
    mbedtls_ecdsa_init(&ctx_sign);

    mbedtls_ecdsa_init(&ctx_verify);


    mbedtls_ctr_drbg_init(&ctr_drbg);

    memset(sig, 0, sizeof(sig));
    memset(message, 0x25, sizeof(message));


    /*
     * Generate a key pair for signing
     */
    mbedtls_printf("\n  . Seeding the random number generator...");
    fflush(stdout);

    mbedtls_entropy_init(&entropy);
    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                                     (const unsigned char *) pers,
                                     strlen(pers))) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret);
        goto exit;
    }

    mbedtls_printf(" ok\n  . Generating key pair...");
    fflush(stdout);

    if ((ret = mbedtls_ecdsa_genkey(&ctx_sign, ECPARAMS,
                                    mbedtls_ctr_drbg_random, &ctr_drbg)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret);
        goto exit;
    }

    mbedtls_ecp_group_id grp_id = mbedtls_ecp_keypair_get_group_id(&ctx_sign);
    const mbedtls_ecp_curve_info *curve_info =
        mbedtls_ecp_curve_info_from_grp_id(grp_id);
    mbedtls_printf(" ok (key size: %d bits)\n", (int) curve_info->bit_size);

    dump_pubkey("  + Public key: ", &ctx_sign);




    /*
     * Compute message hash
     */
    mbedtls_printf("  . Computing message hash...");
    fflush(stdout);

    if ((ret = mbedtls_sha256(message, sizeof(message), hash, 0)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_sha256 returned %d\n", ret);
        goto exit;
    }

    mbedtls_printf(" ok\n");

    dump_buf("  + Hash: ", hash, sizeof(hash));



    /*
     * Sign message hash
     */
    mbedtls_printf("  . Signing message hash...");
    fflush(stdout);

    if ((ret = mbedtls_ecdsa_write_signature(&ctx_sign, MBEDTLS_MD_SHA256,
                                             hash, sizeof(hash),
                                             sig, sizeof(sig), &sig_len,
                                             mbedtls_ctr_drbg_random, &ctr_drbg)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ecdsa_write_signature returned %d\n", ret);
        goto exit;
    }
    mbedtls_printf(" ok (signature length = %u)\n", (unsigned int) sig_len);

    dump_buf("  + Signature: ", sig, sig_len);





    /*
     * Transfer public information to verifying context
     *
     * We could use the same context for verification and signatures, but we
     * chose to use a new one in order to make it clear that the verifying
     * context only needs the public key (Q), and not the private key (d).
     */
    mbedtls_printf("  . Preparing verification context...");
    fflush(stdout);

    if ((ret = mbedtls_ecp_export(&ctx_sign, NULL, NULL, &Q)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ecp_export returned %d\n", ret);
        goto exit;
    }

    if ((ret = mbedtls_ecp_set_public_key(grp_id, &ctx_verify, &Q)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ecp_set_public_key returned %d\n", ret);
        goto exit;
    }


    /*
     * Verify signature
     */
    mbedtls_printf(" ok\n  . Verifying signature...");
    fflush(stdout);

    if ((ret = mbedtls_ecdsa_read_signature(&ctx_verify,
                                            hash, sizeof(hash),
                                            sig, sig_len)) != 0) {
        mbedtls_printf(" failed\n  ! mbedtls_ecdsa_read_signature returned %d\n", ret);
        goto exit;
    }

    mbedtls_printf(" ok\n");

    exit_code = MBEDTLS_EXIT_SUCCESS;



exit:

    mbedtls_ecdsa_free(&ctx_verify);
    mbedtls_ecdsa_free(&ctx_sign);
    mbedtls_ecp_point_free(&Q);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

    mbedtls_exit(exit_code);
 

#endif
//-----------------------------------------------------------------------------------


















//----------------------------------------------------------------------------------


#if 0
    mbedtls_sha256((unsigned char*)data, strlen(data), output, 0);
    printf("test starts:\n");
    printf(" SHA256: ");

    for (int i = 0; i < 32; i++)
        printf("%02x", output[i]);
    printf("\n");
#endif

//----------------------------------------------------------------------------------









    return 0;
} 