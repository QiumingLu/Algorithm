#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <set>

class IOSystem;
class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	void formatDisk();
	
	void createFile();
	void deleteFile();

	void openFile();
	void closeFile();

	void addContentIntoFile();

	void outputCurrDiskState() const;

	void showFile() const;
	void renameFile();
	void showAllFileInDir() const;

private:
	bool openSetContains(int fd) const;

private:
	IOSystem* iosystem_;
	std::set<int> openSet_;
	const static int BUFFER_SIZE = 1024;
};

#endif	// FILESYSTEM_H
