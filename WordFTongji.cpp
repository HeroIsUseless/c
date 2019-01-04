#include "iostream"
#include "string"
#include "map"
#include "algorithm"
#include "vector"
using namespace std;
//首先，是如何输入这些字符
//然后，找到那个#，分割成单词
//对单词进行缩减
//然后统计出最大值排序出来，按照字典序输出
typedef struct Words{
    string str;
    int count;
} Words;
void CopyM_To_V(map<string, int> &cm, vector<Words> &cv){//信息转入vector中
	for (auto it = cm.begin(); it != cm.end(); it++) {
		if (it->first.length()>0) {
            Words w; w.str = it->first; w.count = it->second;
			cv.push_back(w);
		}
	}
}
bool cmp(Words cw1, Words cw2) {//比较函数
	if (cw1.count > cw2.count) {
		return true;
	}
	if (cw1.count == cw2.count) {
		return cw1.str < cw2.str;
	}
	return false;
}

int main(){
    char c;
    c = getchar();
    string s;
    std::map<string, int> m;
    while(c != '#'){
        if(c>='A'&&c<='Z' || c>='a'&&c<='z' ||
            c>='0'&&c<='9' || c=='_') { 
            if(c>='A'&&c<='Z'){
                if(c>='A' && c<='Z') c += 32;
            }
            if(s.size() < 15) s += c;
        }else{//代表分隔符部分
            if(s.size()) m[s]++;
            s.clear();
        }
        c = getchar();
    }
    if(s.size() != 0){//处理最后一个
        m[s]++;
        s.clear();
    }//信息全部处理完成，存入了map中
    //下面进行输出
    cout << m.size() <<endl;//输出总词数
	vector<Words> v;
    CopyM_To_V(m, v);
	sort(v.begin(), v.end(), cmp);//对vector进行排序
	int count = v.size()*0.1;//前10%
	for (int i = 0; i < count; i++) {
		cout << v[i].count << ":" << v[i].str << endl;
	}
    return 0;
}