#include "iosystem.h"

#include <stdio.h>
#include <string.h>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

IOSystem::IOSystem()
: sizeofDiskBlock_(512),
  numOfDiskBlock_(2880),
  nRsvDiskBlock_(1),
  nFATDiskBlock_(18),
  nDirDiskBlock_(14),
  currNumOfFiles_(0)
{
  for (int i = 0; i < alreadyUsed; ++i)
  {
    fat1[i] = 1;
  }

  memset(&fat1[alreadyUsed], 0, sizeof(int)*(NUM_OF_ELEMENTS_IN_FAT - alreadyUsed));
  memset(fat2, 0, sizeof(int)*NUM_OF_ELEMENTS_IN_FAT);
}

IOSystem::~IOSystem()
{
}

void IOSystem::formatDisk()
{
  memset(&fat1[alreadyUsed], 0, sizeof(int)*(NUM_OF_ELEMENTS_IN_FAT - alreadyUsed));
  currNumOfFiles_ = 0;

  for (int i = 0; i < MAX_NUM_OF_FILES_IN_DIR; ++i)
  {
    dirArea[i].backup = 0;
  }

  memset(&dataArea, '\0', NUM_OF_DISK_BLOCKS_IN_DATA * SIZE_OF_DISK_BLOCK);

  saveIntoImageFile();
}

void IOSystem::saveIntoImageFile()
{
  int imageFileHandle = (open("ImageFile.bat", O_WRONLY | O_CREAT));
  if (imageFileHandle == -1)
  {
    printf("Cann't open the image file.\n");
    return;
  }

  write(imageFileHandle, &numOfDiskBlock_, sizeof(int));
  write(imageFileHandle, &nRsvDiskBlock_, sizeof(int));
  write(imageFileHandle, &nFATDiskBlock_, sizeof(int));
  write(imageFileHandle, &nDirDiskBlock_, sizeof(int));
  write(imageFileHandle, &currNumOfFiles_, sizeof(int));

  write(imageFileHandle, fat1, NUM_OF_ELEMENTS_IN_FAT * sizeof(int));
  write(imageFileHandle, fat2, NUM_OF_ELEMENTS_IN_FAT * sizeof(int));

  write(imageFileHandle, dirArea, MAX_NUM_OF_FILES_IN_DIR * sizeof(FCBBlock));
  write(imageFileHandle, (char*)&dataArea, NUM_OF_DISK_BLOCKS_IN_DATA * SIZE_OF_DISK_BLOCK);

  close(imageFileHandle);
}

void IOSystem::loadFromImageFile()
{
  int imageFileHandle = (open("ImageFile.bat", O_RDONLY));
  if (imageFileHandle == -1)
  {
    printf("Unable to open the image file.\n");
    return;
  }

  read(imageFileHandle, &numOfDiskBlock_, sizeof(int));
  read(imageFileHandle, &nRsvDiskBlock_, sizeof(int));
  read(imageFileHandle, &nFATDiskBlock_, sizeof(int));
  read(imageFileHandle, &nDirDiskBlock_, sizeof(int));
  read(imageFileHandle, &currNumOfFiles_, sizeof(int));

  read(imageFileHandle, fat1, NUM_OF_ELEMENTS_IN_FAT * sizeof(int));
  read(imageFileHandle, fat2, NUM_OF_ELEMENTS_IN_FAT * sizeof(int));

  read(imageFileHandle, dirArea, MAX_NUM_OF_FILES_IN_DIR * sizeof(FCBBlock));
  read(imageFileHandle, (char*)&dataArea, NUM_OF_DISK_BLOCKS_IN_DATA * SIZE_OF_DISK_BLOCK);

  close(imageFileHandle);

  printf("Number of Disk Block is %d\n", numOfDiskBlock_);
  printf("Number of Reserved Disk Block is %d\n", nRsvDiskBlock_);
  printf("Number of FAT Disk Block is %d\n", nFATDiskBlock_);
  printf("Number of Directory Disk Block is %d\n", nDirDiskBlock_);
  printf("Current Number of Files is %d\n", currNumOfFiles_);
}

int IOSystem::findIdleFCB() const
{
  for (int i = 0; i < MAX_NUM_OF_FILES_IN_DIR; ++i)
  {
    if (dirArea[i].backup == 0)
    {
      return i;
    }
  }

  return -1;
}

bool IOSystem::createFile(char* fileName)
{
  /// If there is no space, return false.
  if (currNumOfFiles_ == MAX_NUM_OF_FILES_IN_DIR - 1)
  {
    return false;
  }

  /// If the file has existed, return false.
  if (fileExisted(fileName) != -1)
  {
    return false;
  }

  int fd = findIdleFCB();
  strcpy(dirArea[fd].fileName, fileName);
  dirArea[fd].firstDiskBlockNum = -1;
  dirArea[fd].fileDiskBlockNum = 0;
  dirArea[fd].backup = 1;

  time_t crtTime;
  time(&crtTime);
  dirArea[fd].crtTime = crtTime;
  dirArea[fd].updTime = crtTime;

  ++currNumOfFiles_;

  return true;
}

bool IOSystem::deleteFile(int fd)
{
  dirArea[fd].backup = 0;

  if (dirArea[fd].fileDiskBlockNum == 0)
  {
    --currNumOfFiles_;
    return true;
  }

  int itr = dirArea[fd].firstDiskBlockNum;
  while (itr != -1)
  {
    memset(dataArea[itr - alreadyUsed], 0, SIZE_OF_DISK_BLOCK);

    int temp = fat1[itr];
    fat1[itr] = 0;
    itr = temp;
  }

  --currNumOfFiles_;
  return true;
}

bool IOSystem::appendFile(int fd, char* content)
{
  int last = -1;
  int contentLen = strlen(content);
  char* cursor = content;

  // Not empty file, but in existence
  if (dirArea[fd].fileDiskBlockNum != 0)
  {
    // Find the last block
    last = dirArea[fd].firstDiskBlockNum;
    while (fat1[last] != -1)
    {
      last = fat1[last];
    }

    int j = 0;
    for ( ; j <SIZE_OF_DISK_BLOCK; ++j)
    {
      if (dataArea[last - alreadyUsed][j] == '\0')
      {
        break;
      }
    }

    if (j != SIZE_OF_DISK_BLOCK)	// 不是完整块
    {
      // 添加内容长度小于等于该块的剩余区域
      if (contentLen <= SIZE_OF_DISK_BLOCK - j)
      {
        memcpy(&dataArea[last - alreadyUsed][j], content, contentLen);
      }
      //添加的内容长度大于该块的剩余区域
      else
      {
        memcpy(&dataArea[last - alreadyUsed][j], content, SIZE_OF_DISK_BLOCK - j);

        cursor = content;
        cursor += SIZE_OF_DISK_BLOCK - j;

        contentLen -= SIZE_OF_DISK_BLOCK - j;
      }
    }
  }
  return addContent(fd, cursor, contentLen, last);
}

bool IOSystem::addContent(int fd, char* cursor, int contentLen, int last)
{		
  int div = contentLen  / SIZE_OF_DISK_BLOCK;
  int mod = contentLen % SIZE_OF_DISK_BLOCK;

  // Find (div + 1) avaiable elements in FAT
  std::vector<int> idxVector;
  for (int j = alreadyUsed; j < NUM_OF_ELEMENTS_IN_FAT; ++j)
  {
    if (fat1[j] == 0)
    {
      idxVector.push_back(j);
    }

    if (idxVector.size() == div + 1)
    {
      break;
    }
  }

  if (idxVector.size() < div + 1)	// No enough room
  {
    return false;
  }

  // Update FAT
  if (last != -1) {
    fat1[last] = idxVector.at(0);
  } else {
    dirArea[fd].firstDiskBlockNum = idxVector.at(0);
  }

  int j = 0;
  for ( ; j < idxVector.size() - 1; ++j)
  {
    int index = idxVector.at(j);
    fat1[index] = idxVector.at(j + 1);
  }
  fat1[idxVector.at(idxVector.size() -1)] = -1;

  // update data size
  int i = 0;
  for (; i < div; ++i)
  {
    int idx = idxVector.at(i);
    memcpy(dataArea[idx - alreadyUsed], cursor, SIZE_OF_DISK_BLOCK);
    cursor += SIZE_OF_DISK_BLOCK;
  }

  memcpy(dataArea[idxVector.at(i) - alreadyUsed], cursor, mod);

  dirArea[fd].fileDiskBlockNum += idxVector.size();

  return true;
}

/// If the file with the given fileName exists, return its position in Directory Area
/// Otherwise, return -1
int IOSystem::fileExisted(char* fileName) const
{
  for (int i = 0; i < MAX_NUM_OF_FILES_IN_DIR; ++i)
  {
    if (dirArea[i].backup == 1 && strcmp(dirArea[i].fileName, fileName) == 0)
    {
      return i;
    }
  }

  return -1;
}

void IOSystem::outputDisk() const
{
  printf("Reserved Area: \n");
  printf("%d %d %d %d %d\n", numOfDiskBlock_, nRsvDiskBlock_,
      nFATDiskBlock_, nDirDiskBlock_, currNumOfFiles_);

  printf("\nFAT: \n");
  for (int i = 0; i < NUM_OF_ELEMENTS_IN_FAT; ++i)
  {
    printf("%d ", fat1[i]);
  }
  printf("\n");

  printf("\nDirectory Area: \n");
  for (int i = 0; i < MAX_NUM_OF_FILES_IN_DIR; ++i)
  {
    if (dirArea[i].backup == 1)
    {
      printf("File Name: %s\tFirst Disk Block: %d\t Total Block: %d\n",
          dirArea[i].fileName,
          dirArea[i].firstDiskBlockNum,
          dirArea[i].fileDiskBlockNum);
    }
  }
  printf("\n");

  char judge;
  printf("Would you like to show the Data Area? (Y/N):");
  fflush(stdin);
  scanf("%c", &judge);

  if (judge != 'Y' && judge != 'y')
  {
    return;
  }

  int lower, upper;
  printf("Enter the range: ");
  fflush(stdin);
  scanf("%d%d", &lower, &upper);

  printf("Data Area from %d to %d\n", lower, upper);
  for (int i = lower; i <= upper; ++i)
  {
    for (int j = 0; j < SIZE_OF_DISK_BLOCK; ++j)
    {
      printf("%c ", dataArea[i][j]);
    }
    printf("\n");
  }
}

void IOSystem::showFile(int fd) const
{
  char* p = new char[SIZE_OF_DISK_BLOCK + 1];

  int indexCur = dirArea[fd].firstDiskBlockNum;

  do 
  {
    memset(p, 0, SIZE_OF_DISK_BLOCK+1);
    readBlock(indexCur, p);
    printf("%s\n", p);
    indexCur = fat1[indexCur];

  } while(indexCur != -1);

  delete []p;
}

bool IOSystem::renameFile(int fd, char* newName)
{
  strcpy(dirArea[fd].fileName, newName);
  updateTime(fd);
  return true;
}

void IOSystem::readBlock(int i, char* p) const
{
  memcpy(p, dataArea[i - alreadyUsed], SIZE_OF_DISK_BLOCK);
}

void IOSystem::updateTime(int fd)
{
  time_t updTime;
  time(&updTime);
  dirArea[fd].updTime = updTime;
}

FCBBlock* IOSystem::getDirArea(int &dirAreaSize)
{
  dirAreaSize = MAX_NUM_OF_FILES_IN_DIR;
  return dirArea;
}
