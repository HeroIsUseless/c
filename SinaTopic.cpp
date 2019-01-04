#include "iostream"
#include "vector"
#include "string"
#include "regex"
#include "set"
#include "map"
using namespace std;
string Process(string cs){
    string mod = "!@#$^&*()+-={}[];:,.<>?";
    for(auto var : mod){//删除多余符号
        cs.erase(std::remove(cs.begin(), cs.end(), var), cs.end());
    }      
    for(int j=0; j<cs.size(); j++){//所有字母小写
        if(cs[j]>='A' && cs[j]<='Z')
            cs[j] = cs[j] - 'A' + 'a';
    }
    cs[0] =cs[0]-'a'+'A';//首字母大写
    return cs;
}
int main(){
    int n; cin >> n; cin.ignore();
    std::map<string, int> topic;
    std::set<string> word;
    std::string s;
    for(int i=0; i<n; i++){//对于每一句话
    //cout << i <<endl;
        getline(cin, s);
        word.clear();
        string w = "";
        bool flag = false;
        for(int k=0; k<s.size(); k++){//对于每个字符
            if(s[k] == '#'){
                if(k == s.size()-1) break;//容错处理
                k++;
                w = "";
                while(s[k] != '#'){
                    w += s[k];
                    k++;
                }
                w = Process(w);
                //cout << "--------" << w << "--------------" <<endl;
                word.insert(w);
                if(k != s.size()-1) k++;
            }
        }
        for(auto var : word){//对每个出现一次的单词进行计数
            topic[var]++;
        }
    }
    string res;
    int max = 0;
    int count = 1;
    for(auto it = topic.begin(); it!=topic.end(); it++){//进行判断
        //cout << it->first <<" "<< it->second << endl;
        if(max < it->second){
            max = it->second;
            res = it->first;
            count = 0;
        }else if(max = it->second){
            if(it->first < res)
                res = it->first;
            count++;
        }
    }
    cout << res << endl;
    cout << max << endl;
    if(count != 0){
        cout << "And " << count << " more ...";
    }
    
    return 0;
}