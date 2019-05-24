typedef struct 
{
    char* addr;
    float dataRead, dataWrite;
    unsigned long long 
        metaRead,
        metaWrite,
        dSpaceOps,
        keyValOps,
        scheduled,
        requests,
        smallReads,
        smallWrites,
        flowReads,
        flowWrites,
        creates,
        removes,
        mkdirs,
        rmdirs,
        getattrs,
        setattrs,
        timestamp;
} dataEntry;

void addEntry(dataEntry* data, char* address);