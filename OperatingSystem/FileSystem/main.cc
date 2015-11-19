#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include "filesystem.h"

int main()
{
  std::shared_ptr<FileSystem> fileSystem(new FileSystem());
  int nSelec = 0;
  while(1)
  {
    printf("\n---------------------------------------------\n\tFILE SYSTEM\n\t"
        "Author: Ming\n\tEmail:cming_cs@163.com\n\tALL RIGHTS RESERVED\n"
        "---------------------------------------------\n"
        "Selection Menu:\n\t1. Formatting"
        "\n\t2. Create a file\n\t3. Add contents into a file\n\t4. Delete a file"
        "\n\t5. Rename a file\n\t6. Show a file"
        "\n\t7. Show all files in directory"
        "\n\t8. Open a file"
        "\n\t9. Close a file"
        "\n\t10.OutputCurrDiskState"
        "\n\t0. Exit\nYour selection is [ ]\b\b");

    fflush(stdin);
    scanf("%d", &nSelec);

    switch (nSelec)
    {
      case 1:
        fileSystem->formatDisk();
        break;
      case 2:
        fileSystem->createFile();
        break;
      case 3:
        fileSystem->addContentIntoFile();
        break;
      case 4:
        fileSystem->deleteFile();
        break;
      case 5:
        fileSystem->renameFile();
        break;
      case 6:
        fileSystem->showFile();
        break;
      case 7:
        fileSystem->showAllFileInDir();
        break;
      case 8:
        fileSystem->openFile();
        break;
      case 9:
        fileSystem->closeFile();
        break;
      case 10:
        fileSystem->outputCurrDiskState();
        break;
      case 0:
        exit(0);
      default:
        break;
    }

    printf("Press Enter to continue...");
    fflush(stdin);
    getchar();
  }
  return 0;
}
