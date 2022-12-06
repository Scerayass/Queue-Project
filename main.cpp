#include <iostream>
#include "ReadAndWriteFile.h"

int main(int argc,char *argv[]) {
    ReadAndWriteFile file; // all Files are reads , do whatever needs and write them output
    file.execute(argv[1],argv[2]);
    return 0;
}
