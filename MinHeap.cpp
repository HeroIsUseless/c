#include <vector>
#include <iostream>
 
using namespace std;

void Insert(vector<int>& minHeap, int element);
void Read(vector<int>& minHeap, int dataNum);
void Print(vector<int>& minHeap, int routeNum);
 
int main()
{
	vector<int> minHeap;//利用vector进行存储，最小堆实际上是一棵元素逐层增大的完全二叉树，根节点为元素最小值。
	minHeap.push_back(-10001);//这里有个小技巧是在vector的第一个元素设置哨兵（元素值为min），方便后期进行循环。
 
	int dataNum;
	int routeNum;
	cin >> dataNum >> routeNum;
 
	Read(minHeap, dataNum);
	Print(minHeap, routeNum);
	
	system("pause");
    return 0;
}
//将当前index（注意不包含新加入结点）的父节点（index/2）与插入元素的元素值进行大小比较，
//从后往前依次循环比较，若当前结点比其父节点小，则交换位置，直到根节点位置。
void Insert(vector<int>& minHeap, int element) {//一直是引用，其实我一直没有用到过
	if (minHeap.size() >= 1001)return;//容错处理
	//从后往前循环比较,每次比较当前结点与父节点的大小，若当前结点比父节点小，则交换；
	int index = minHeap.size();//不，是插入的那个
	minHeap.push_back(element);//插入进去了
	while (minHeap[index/2] > element) {//说index/2是它的父节点，如果这个节点比较大的话
		minHeap[index] = minHeap[index / 2];//element的信息就不要了？
		index /= 2;//而且每次都是跟一个固定值相比
	}
	minHeap[index] = element;//其实是把element向前进行移位的操作
}//但为什么index/2会是它的父节点呢？是由插入的定义进行决定的
 //这是一种神奇的插入方式，index/2会是它的父节点
void Read(vector<int>& minHeap, int dataNum) {//今后多用用按照引用传递的方式，尤其是指针
	int element;
	for (int i = 0; i < dataNum; i++) {
		cin >> element;
		Insert(minHeap, element);//仅仅是读入，插入在insert里
	}
}
 
void Print(vector<int>& minHeap, int routeNum) {//按照引用的一个vector
	int index;
	for (int i = 0; i < routeNum; i++) {
		cin >> index;
		cout << minHeap[index];
		while (index > 1) {
			index /= 2;
			cout << " " << minHeap[index];
		}
		cout << endl;
 	}
}