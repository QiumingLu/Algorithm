#ifndef PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H

#include <vector>

class PageReplacement
{
public:
	PageReplacement();
	~PageReplacement();
	void run();
	void optimal();
	void random();
	void FIFO();
	void LRU();
	void clock();
	void clockBetter();

private:
	void addInfo() const;
	void addInfo(const std::vector<int>& modified) const;

private:
	int pages;					// 虚拟内存的尺寸P
	int firstPageFramePos;		// 工作面的起始位置p
	int pageFrames;				// 工作面中包含的页数e
	int rateM;					// 工作面移动率m
	double t;					// 范围在0和1之间的值t
	std::vector<int> seqVec;	// 序列号
	std::vector<int> mem;		// 内存块
};

#endif	// PAGEREPLACEMENT_H
