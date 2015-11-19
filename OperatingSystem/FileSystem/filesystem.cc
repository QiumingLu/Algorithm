#include "filesystem.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "iosystem.h"

FileSystem::FileSystem()
: iosystem_(new IOSystem())
{
  iosystem_->loadFromImageFile();
}

FileSystem::~FileSystem()
{
  iosystem_->saveIntoImageFile();
  delete iosystem_;
}

void FileSystem::formatDisk()
{
  printf("All the previous data will be deleted permanently.\n");
  printf("Are you sure to format the disk? (Y/N): ");
  char ans;

  fflush(stdin);
  scanf("%c", &ans);

  if (ans == 'Y')
  {
    iosystem_->formatDisk();
  }

  openSet_.clear();
}

void FileSystem::createFile()
{
  printf("Enter a name for the file to be created: ");
  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  if (iosystem_->fileExisted(fileName) != -1)
  {
    printf("Please rename the file to be created.\n");
    return;
  }

  if (iosystem_->createFile(fileName))
  {
    printf("A file named %s has been created successfully.\n", fileName);
  }
  else
  {
    printf("File creation failed.\n");
  }
}

void FileSystem::deleteFile()
{
  printf("Enter the file name to be deleted: ");
  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);

  if (fd == -1)
  {
    printf("No such a file in existence.\n");
    return;
  }

  if (openSetContains(fd))
  {
    printf("The file remains open. Please close it.\n");
    return;
  }

  iosystem_->deleteFile(fd);
  printf("Deletion successful.\n");
}

void FileSystem::openFile()
{
  printf("Enter a file name: ");

  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);

  if (fd == -1)
  {
    printf("No such a file in existence.\n");
    return;
  }

  if (openSetContains(fd))
  {
    printf("The file cannot be opened twice.\n");
    return;
  }

  openSet_.insert(fd);
  printf("File open successful!\n");
}

void FileSystem::closeFile()
{
  printf("Enter a file name: ");

  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);

  if (fd == -1)
  {
    printf("No such a file in existence.\n");
    return;
  }

  if (openSetContains(fd))
  {
    openSet_.erase(fd);
    printf("File closed successfully.\n");
  }
  else
  {
    printf("File has already been closed.\n");
  }
}

bool FileSystem::openSetContains(int fd) const
{
  std::set<int>::iterator it = openSet_.find(fd);
  if (it != openSet_.end())
  {
    return true;
  }
  else
  {
    return false;
  }
}

void FileSystem::addContentIntoFile()
{
  printf("Enter the file name to add contents: ");

  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);

  if (fd == -1)
  {
    printf("No such file in existence.\n");
    return;
  }

  if (!openSetContains(fd))
  {
    printf("The file must be opened before this operation.\n");
    return;
  }

  printf("Enter the additional contents: \n");

  char content[BUFFER_SIZE];
  memset(content, 0, BUFFER_SIZE);

  fflush(stdin);

  char c;
  int i = 0;
  while ((c = getchar()) != '\n')
  {
    content[i++] = c;
    if (i == BUFFER_SIZE - 1)
      break;
  }

  if (!iosystem_->appendFile(fd, content))
  {
    printf("Appending failed.\n");
  }
  else
  {
    iosystem_->updateTime(fd);
    printf("Appending successful.\n");
  }
}

void FileSystem::outputCurrDiskState() const
{
  iosystem_->outputDisk();
}

void FileSystem::showFile() const
{
  printf("Enter a file name: ");
  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);
  if (fd == -1)
  {
    printf("No such a file in existence.\n");
    return;
  }

  if (!openSetContains(fd))
  {
    printf("The file remains closed. Please open it.\n");
    return;
  }

  iosystem_->showFile(fd);
  printf("\n");
}


void FileSystem::renameFile() 
{
  printf("Enter a file name to be renamed: ");
  char fileName[12];
  fflush(stdin);
  scanf("%s", fileName);

  int fd = iosystem_->fileExisted(fileName);
  if (fd == -1)
  {
    printf("No such a file in existence.\n");
    return;
  }

  if (openSetContains(fd))
  {
    printf("The file remains open. Please close it.\n");
    return;
  }

  printf("Enter a new name for the file: ");
  char newName[12];
  fflush(stdin);
  scanf("%s", newName);

  if (strlen(newName) > 12)
  {
    printf("New Name Invalid.\n");
    return;
  }

  iosystem_->renameFile(fd, newName);
  printf("File Renaming Successful.\n");
}

void FileSystem::showAllFileInDir() const
{
  printf("..Root\n");
  int dirAreaSize;
  FCBBlock* dirArea = iosystem_->getDirArea(dirAreaSize);

  for (int i = 0; i < dirAreaSize; ++i)
  {
    if (dirArea[i].backup == 1)
    {
      struct tm *ctime, *utime;
      ctime = localtime(&dirArea[i].crtTime);
      utime = localtime(&dirArea[i].updTime);


      printf("\t%s\n\t\tCreate Time: %s\t\tUpdate Time: %s\t\t
          First Disk Block Number: %d\n\t\tNumber of Disk Blocks: %d\n",
          dirArea[i].fileName,
          asctime(ctime),
          asctime(utime),
          dirArea[i].firstDiskBlockNum,
          dirArea[i].fileDiskBlockNum);
    }
  }
}


