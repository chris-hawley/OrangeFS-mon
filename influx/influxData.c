#include "influx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <curl/curl.h>

#define BUFFSIZE 4096

void addEntry(dataEntry* data, char* address)
{
    CURL *curl;
    CURLcode res;
    char* buffer = calloc(1,BUFFSIZE);

 
    /* In windows, this will init the winsock stuff */ 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, address);

        uint64_t timestamp = (uint64_t)data->timestamp; //convert ms to ns

        //construct query 
        buffer[0] = '\0';
        sprintf(buffer, "orangefs,server=%s "
                        "dataread=%f,"
                        "datawrite=%f,"
                        "metaread=%llu,"
                        "metawrite=%llu,"
                        "dspaceops=%llu,"
                        "keyvalops=%llu,"
                        "scheduled=%llu,"
                        "requests=%llu,"
                        "smallreads=%llu,"
                        "smallwrites=%llu,"
                        "flowreads=%llu,"
                        "flowwrites=%llu,"
                        "creates=%llu,"
                        "removes=%llu,"
                        "mkdirs=%llu,"
                        "rmdirs=%llu,"
                        "getattrs=%llu,"
                        "setattrs=%llu ",
                        //"%lu\n",
                        data->addr,
                        data->dataRead,
                        data->dataWrite,
                        data->metaRead,
                        data->metaWrite,
                        data->dSpaceOps,
                        data->keyValOps,
                        data->scheduled,
                        data->requests,
                        data->smallReads,
                        data->smallWrites,
                        data->flowReads,
                        data->flowWrites,
                        data->creates,
                        data->removes,
                        data->mkdirs,
                        data->rmdirs,
                        data->getattrs,
                        data->setattrs
                        //timestamp
                        );
        //printf("%s\n", buffer);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }   

    free(buffer);
}