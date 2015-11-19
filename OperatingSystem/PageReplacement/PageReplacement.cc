#include "PageReplacement.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>

PageReplacement::PageReplacement()
: mem(3, -1)
{
  this->run();
}

PageReplacement::~PageReplacement()
{
}

void PageReplacement::run()
{
  std::cout << "请输入虚拟内存尺寸P：";
  std::cin >> pages;
  std::cout << "请输入工作面的起始位置p：";
  std::cin >> firstPageFramePos;
  std::cout << "请输入工作面中包含的页数e：";
  std::cin >> pageFrames;
  std::cout << "请输入工作面移动率m：";
  std::cin >> rateM;
  std::cout << "请输入在0和1之间的值t：";
  std::cin >> t;

  for (int i = 0; i < rateM; ++i)
  {
    int randomNum = (rand() % pageFrames) + firstPageFramePos;
    seqVec.push_back(randomNum);
  }

  std::cout << "序列号：";
  for (int i = 0; i < seqVec.size(); ++i)
  {
    std::cout << seqVec.at(i) << " ";
  }

  std::cout << std::endl;

  double r = rand()%11 / 10;
  if (r < t)
  {
    firstPageFramePos = rand()%(pages - pageFrames);
  }
  else
  {
    firstPageFramePos = (firstPageFramePos + 1) % pages;
  }
}

void PageReplacement::optimal()
{
  int nLack = 0;						// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();		// 总访问页面数

  while(!seqList.empty())				// 页面访问队列不为空
  {
    int head = *seqList.begin();	// 取队头页面
    seqList.pop_front();
    bool equal = false;				// 标识是否内存中是否有与队头相等的页面
    int vacant = -1;				// 标识内存块中是否有空闲位
    for (int i = 0; i < mem.size(); ++i)
    {
      if (mem.at(i) == head)		// 如果找到相等的页面
      {
        this->addInfo();		//显示内存情况
        equal = true;
        break;
      }
      else if (mem.at(i) == -1 && vacant == -1)
      {
        vacant = i;				// 找到空闲位
      }
    }

    if(equal)						// 找到相等的页面，进行下一个页面访问
    {
      continue;
    }

    ++nLack;

    if (vacant != -1)				// 找到空闲位，即avcant
    {
      mem[vacant] = head;	
      this->addInfo();
      continue;
    }
    else
    {
      std::vector<int> dist(mem.size());

      // 计算距离向量
      for (int i = 0; i < mem.size(); ++i)
      {
        int j = 0;
        std::list<int>::iterator it = seqList.begin();
        while (j < seqList.size())
        {
          if (mem.at(i) == *it)
          {
            break;
          }
          else
          {
            ++j;
            ++it;
          }
        }

        if (j <= seqList.size())
        {
          dist[i] = j;
        }
      }

      // 比较出距离分量最大的内存块
      int max = dist[0];
      int sub = 0;
      for (int i = 0; i < dist.size(); ++i)
      {
        if (dist[i] > max)
        {
          max = dist[i];
          sub = i;
        }
      }

      mem[sub] = head;	// 置换内存块
      addInfo();			// 显示内存块

    }
  }

  std::cout << "缺页率：" << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);
}

void PageReplacement::random()
{
  int nLack = 0;		// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();

  while (!seqList.empty())		// 页面访问队列不为空
  {
    int head = *seqList.begin();	//去队头的页面
    seqList.pop_front();			//剔除掉
    bool equal = false;				// 标识内存中是否有与队头相等的页面
    int vacant = -1;				// 标识内存中是否有空闲位

    for (int i = 0; i < mem.size(); ++i)
    {
      if (head == mem.at(i))		// 如果找到相等的页面
      {
        this->addInfo();
        equal = true;
        break;
      }

      else if (mem.at(i) == -1 && vacant == -1)	// 找到空闲位
      {
        vacant = i;
      }		
    }

    if (equal)						// 找到相等页面，进行下一个页面的访问
    {
      continue;
    }

    ++nLack;

    if (vacant != -1)				// 找到空闲位
    {
      mem.at(vacant) = head;
      this->addInfo();
      continue;
    }

    else
    {
      // 随机算出一个内存块作为被置换页面
      int r = rand() % (mem.size());
      mem.at(r) = head;

      this->addInfo();		// 显示内存情况
    }
  }

  std::cout << "缺页率：" << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);
}

void PageReplacement::FIFO()
{
  int nLack = 0;		// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();

  int queueHead = 0;				// 内存块队列队头指针
  while (!seqList.empty())		// 页面访问队列不为空
  {
    int head = *seqList.begin();	//去队头的页面
    seqList.pop_front();			
    bool equal = false;				// 标识内存中是否有与队头相等的页面
    int vacant = -1;				// 标识内存中是否有空闲位

    for (int i = 0; i < mem.size(); ++i)
    {
      if (head == mem.at(i))		// 如果找到相等的页面
      {
        this->addInfo();
        equal = true;
        break;
      }

      else if (mem.at(i) == -1 && vacant == -1)	// 找到空闲位
      {
        vacant = i;
      }		
    }

    if (equal)						// 找到相等页面，进行下一个页面的访问
    {
      continue;
    }

    ++nLack;

    if (vacant != -1)				// 找到空闲位
    {
      mem.at(vacant) = head;
      this->addInfo();
      continue;
    }

    else
    {
      mem.at(queueHead) = head;
      queueHead = (queueHead + 1) % mem.size();

      this->addInfo();		// 显示内存情况
    }
  }

  std::cout << "缺页率：" << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);

}

void PageReplacement::LRU()
{
  int nLack = 0;							// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();

  std::vector<int> timer(mem.size(), 0);		// 每个内存块对应的时钟

  while (!seqList.empty())
  {
    int head = *seqList.begin();			// 去队头的页面
    seqList.pop_front();
    bool equal = false;						// 标识内存中是否有与队头相等的页面
    int vacant = -1;						// 标识内存中是否有空闲页面

    for (int i = 0; i < mem.size(); ++i)
    {
      if (mem.at(i) == head)				// 如果找到相等的页面
      {
        equal = true;
        this->addInfo();				// 显示内存块

        timer.at(i) = -1;				// 相等的时钟清零，其他的时钟加1
        for (int j = 0; j < timer.size(); ++j)
        {
          ++timer[j];
        }

        break;
      }

      else if (mem.at(i) == -1 && vacant == -1)		// 如果找到空闲位
      {
        vacant = i;
      }
    }

    if (equal)					// 如果找到相等的页面，则进行下一个查找
    {
      continue;
    }

    ++nLack;

    if (vacant !=  -1)
    {
      mem[vacant] = head;			// 把队头的放入到空闲位中
      this->addInfo();

      timer[vacant] = -1;			// 空闲位时钟清零，其他时钟加1
      for (int j = 0; j < timer.size(); ++j)
      {
        ++timer[j];
      }

      continue;
    }

    else
    {
      int max = timer[0];
      int subIndex = 0;
      for (int p = 0; p < timer.size(); ++p)
      {
        if (timer.at(p) > max)
        {
          max = timer.at(p);		// 找到最近最久没有被使用的内存块
          subIndex = p;
        }
      }

      mem[subIndex] = head;			// 把队头的放入到最近最久未被使用的内存块中
      this->addInfo();

      timer[subIndex] = -1;
      for (int j = 0; j < timer.size(); ++j)
      {
        ++timer[j];
      }

    }

  }

  std::cout << "缺页率： " << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);
}

void PageReplacement::clock()
{
  int nLack = 0;			// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();

  std::vector<int> timer(mem.size(), 0);
  int cursor = 0;			// 当前的时钟指针

  while (!seqList.empty())
  {
    int head = *seqList.begin();		// 去掉队头的页面
    seqList.pop_front();

    int p = 0;

    // 遍历内存块，找到与队头页面相等的内存块
    for(p ; p < mem.size(); ++p)
    {
      if (mem.at(p) == head)		// 如果找到，将其时钟访问位置1，时钟指针往下移
      {
        timer[p] = 1;
        cursor = p;
        cursor = (cursor + 1) % timer.size();

        this->addInfo();
        break;
      }
    }

    if (p == mem.size())	// 如果没有找到
    {
      // 循环移动clock指针，知道找到访问位不为1的第一个内存块
      while (timer[cursor] == 1)
      {
        timer[cursor] = 0;
        cursor = (cursor + 1) % timer.size();
      }

      ++nLack;

      mem[cursor] = head;
      timer[cursor] = 1;
      cursor = (cursor + 1) % timer.size();
      this->addInfo();
    }
  }

  std::cout << "缺页率： " << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);
}

void PageReplacement::clockBetter()
{
  int nLack = 0;		// 缺页数
  std::list<int> seqList(seqVec.begin(), seqVec.end());
  int nTotal = seqList.size();

  std::vector<int> visited(mem.size(), 0);
  std::vector<int> modified(mem.size(), 0);

  int cursor = 0;		// 时钟指针

  while (!seqList.empty())
  {
    int head = *seqList.begin();		// 取队头页面
    seqList.pop_front();

    int p;

    // 遍历内存块，找与队头页面相等的内存块
    for (p = 0; p < mem.size(); ++p)
    {
      if (mem.at(p) == head)		// 如果找到， 将其访问位置置1，clock指针循环下移，修改位可能同时被改动
      {
        visited[p] = 1;
        modified[p] = rand() % 2;
        cursor = p;
        cursor = (cursor + 1) % visited.size();
        this->addInfo(modified);
        break;
      }
    }

    if (p == mem.size())			// 如果没有找到相等的内存块
    {
      bool loop = false;			// 标识是否继续找被置换的页面

      ++nLack;					// 缺页率加1

      // 先找第一类页面，即访问位和修改位都为0
      do
      {
        bool firstClass = false;

        for (int i = 0; i < mem.size(); ++i)
        {
          if (visited[i] == 0 && modified[i] == 0)
          {
            mem[i] = head;		// 置换页面
            visited[i] = 1;

            cursor = i;
            modified[cursor] = rand() % 2;	// 修改位可能同时被改动

            cursor = (cursor + 1) % visited.size();	// clock 指针循环下移

            firstClass = true;
            break;
          }
        }

        if (firstClass)			//找到了第一类页面
        {
          this->addInfo(modified);
          break;
        }

        bool secondClass = false;		// 如果没找到第一类页面
        // 开始找第二类页面，即访问位为0， 修改位为1
        for (int i = 0; i < mem.size(); ++i)
        {
          mem[i] = head;		// 置换页面
          visited[i] = 1;

          cursor = i;
          modified[cursor] = rand() % 2;

          cursor = (cursor + 1) % visited.size();		// clock 指针循环下移

          secondClass = true;
          break;
        }

        if (secondClass)		// 找到第二页面
        {
          this->addInfo(modified);
          break;
        }

        loop = true;			// 两类都没找到，重新找第一类
      }while (loop);
    }
  }

  // 显示缺页率
  std::cout << "缺页率： " << (double)nLack/nTotal * 100 << "%" << std::endl;
  mem.clear();
  mem.assign(3, -1);
}

void PageReplacement::addInfo() const
{ 
  std::cout << mem.at(0) << "    " <<  mem.at(1) << "    "  << mem.at(2) << std::endl;
}

void PageReplacement::addInfo(const std::vector<int>& modified) const
{
  for (int i = 0; i < modified.size(); ++i)
  {
    if (modified.at(i) == 1)
    { 
      std::cout << mem.at(i) << "@    ";
    }
    else
    { 	
      std::cout << mem.at(i) << "    ";
    }
  }

  std::cout << std::endl;
}
