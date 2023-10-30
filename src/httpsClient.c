#define _GNU_SOURCE
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define HOST "api.genderize.io"
#define PORT "443"

char * getJsonFromRawResponse(char * response) {
    int jsonLength= 1;
    char * actualJson = calloc(1, sizeof(char)*jsonLength);
    int i = 0;
    while (response[i] != '\0') {
        if (response[i] == '{') {
            // here starts the json
            actualJson[jsonLength-1] = response[i];
            jsonLength++;
            actualJson = realloc(actualJson, sizeof(char) * jsonLength);
            i++;
            do {
                actualJson[jsonLength-1] = response[i];
                jsonLength++;
                actualJson = realloc(actualJson, sizeof(char) * jsonLength);
                i++;
            } while (response[i] != '}');
            break;
        } else {
            i++;
        }
    }
    actualJson[jsonLength-1] = '}';
    actualJson[jsonLength] = '\0';
    return actualJson;
}

char * findJsonByName(char * name) {
    char host[] = HOST;

    BIO* bio;
    SSL* ssl;
    SSL_CTX* ctx;

    //Register the SSL/TLS ciphers and digests, start the security layer.
    SSL_library_init();
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL)
    {
        printf("Ctx is null\n");
    }
    bio = BIO_new_ssl_connect(ctx);

    BIO_set_conn_hostname(bio, HOST ":" PORT);

    if(BIO_do_connect(bio) <= 0)
    {
        printf("Failed connection\n");
    }
    else
    {
        printf("Connected\n");
    }

    // http GET request to the server
    char* write_buf;
    asprintf(&write_buf, "GET /?name=%s HTTP/1.1\r\n"
     "Host: %s \r\n" 
     "Connection: close \r\n"
     "\r\n", name, host);

    if(BIO_write(bio, write_buf, strlen(write_buf)) <= 0)
    {
        //  Handle failed writes here
        if(!BIO_should_retry(bio))
        {
        }

        printf("Failed write\n");
    }

    // Variable declared to read the response from the server
    int size;
    char * buf = calloc(1,sizeof(char)*1024);

    //  Read the response message and store it in the string we declared above
    for(;;)
    {
        size = BIO_read(bio, buf, 1023);

        // terminate if there is no more data to read
        if(size <= 0)
        {
            break;
        }

        buf[size] = 0;
    }

    // Clean memory exc.
    free(write_buf);
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return buf;
} 