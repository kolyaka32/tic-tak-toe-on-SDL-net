/*
 * Copyright (C) 2024-2025, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "archieveLoader.hpp"
#include "../../../define.hpp"


#define CHUNK 16384

int inf(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decompress until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            //assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


ArchieveLoader::ArchieveLoader() {
    // Open archive with need name
    /*archive = zip_open(DATA_FILE, ZIP_RDONLY, NULL);

    #if ARCHIEVE_PASSWORD
    zip_set_default_password(archive, ARCHIEVE_PASSWORD);
    #endif

    // Checking openning correction
    #if CHECK_CORRECTION
    if (!archive) {
        throw DataLoadException("load archieve: " + std::string(DATA_FILE));
    }
    #endif*/

    FILE* fin = fopen(DATA_FILE, "r");
    FILE* fout = fopen("fout.txt", "w");

    inf(fin, fout);
}

ArchieveLoader::~ArchieveLoader() {
    //zip_close(archive);
}

SDL_IOStream* ArchieveLoader::load(const char* _file) const {
    // Openning need file
    /*zip_file_t *file = zip_fopen_encrypted(archive, _file, 0, ARCHIEVE_PASSWORD);

    // Checking correction of openned file
    #if CHECK_CORRECTION
    if (file == nullptr) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Getting states of need file
    zip_stat_t st;
    zip_stat(archive, _file, 0, &st);

    // Checking correction of openned file
    #if CHECK_CORRECTION
    if (st.size == 0) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Creating buffer for data
    Uint8* buffer = new Uint8[st.size];

    // Copping data to buffer
    zip_fread(file, buffer, st.size);

    // Closing readed file
    zip_fclose(file);

    // Creating SDL-based structure with this data
    SDL_IOStream *tempIO = SDL_IOFromConstMem(buffer, st.size);

    // Checking correction of loaded object
    #if CHECK_CORRECTION
    if (!tempIO) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Returning created data structure
    return tempIO;*/
    return nullptr;
}
