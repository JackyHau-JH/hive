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

#include "app_sdl2.h"
#include "app_mbedtls.h"
int main(int argc, char *argv[])
{

    // app_sdl2_run();

    app_mbedtls_run();

    return 0;
}