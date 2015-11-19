#ifndef	IOSYSTEM_H
#define IOSYSTEM_H

#include <time.h>

struct FCBBlock
{
  char fileName[8];						// 用于保存文件名
  char extended[3];						// 用于保存扩展名
  int fileAttr;							// 文件属性
  int backup;							// 备用0---idle, 1---occupied
  time_t crtTime;						// 创建时间
  time_t updTime;						// 更新时间
  int firstDiskBlockNum;				// 第一个盘块号
  int fileDiskBlockNum;					// 盘块数
};

class IOSystem
{
 public:
  IOSystem();
  ~IOSystem();

  int getNUmOfDiskBlock() const { return numOfDiskBlock_; }
  int getSizeOfDiskBlock() const { return sizeofDiskBlock_; }

  void formatDisk();

  void saveIntoImageFile();
  void loadFromImageFile();

  bool createFile(char* fileName);
  bool deleteFile(int fd);
  bool appendFile(int fd, char* context);

  int fileExisted(char* fileName) const;

  void outputDisk() const;

  void showFile(int fd) const;
  bool renameFile(int fd, char* newName);

  void readBlock(int i, char* p) const;

  void updateTime(int fd);

  FCBBlock* getDirArea(int &dirAreaSize);

 private:
  int findIdleFCB() const;
  bool addContent(int fd, char* cursor, int contentLen, int last);

  const static int MAX_NUM_OF_FILES_IN_DIR = 16*14;
  const static int NUM_OF_ELEMENTS_IN_FAT = 128*9;
  const static int NUM_OF_DISK_BLOCKS_IN_DATA = 2879 - 33 + 1;
  const static int SIZE_OF_DISK_BLOCK = 512;
  const static int TIME_MAX = 32;
  const static int alreadyUsed = 33;

  int sizeofDiskBlock_;	// 盘块大小

  // Reserved area
  int numOfDiskBlock_;		// 盘块个数
  int nRsvDiskBlock_;		// 保留区盘块数
  int nFATDiskBlock_;		// FAT表区盘块数
  int nDirDiskBlock_;		// 目录区盘块数

  int currNumOfFiles_;		// 当前系统包含的文件个数

  // FAT area
  int fat1[NUM_OF_ELEMENTS_IN_FAT];			// FAT1表
  int fat2[NUM_OF_ELEMENTS_IN_FAT];			// FAT2表

  // Directory area 
  FCBBlock dirArea[MAX_NUM_OF_FILES_IN_DIR];	// 目录区，FCB数组

  // Data area
  char dataArea[NUM_OF_DISK_BLOCKS_IN_DATA][SIZE_OF_DISK_BLOCK];	
  // 数据区，char类型二维数组
};

#endif	// IOSYSTEM_H
