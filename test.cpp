/*
 * 这题给了200ms的时间  n<=100 所以这题即使每排序一趟与中间序列进行比较  时间复杂度也仅为O(n^2) 完全可以
 * 还有个O(n)的算法：
  1. 插入排序特点为  前面均为有序序列  没排序的与原序列相同  
  2. 归并排序进行了几趟归并  可通过len=2 到 n/2 进行枚举  直到不满足每一组归并序列都有序的条件时  即可得到当前
  进行了几次归并

  另外 这题题目好像有点问题  比如 1 2 4 3 中间序列为 1 2 4 3 你根本不知道是进行了2趟还是3趟插入排序@—-@。 
*/
#include "iostream"
#include "algorithm"
using namespace std;
void merge(int a[], int temp[], int left, int right, int rightEnd) { /* 合并2个有序的子序列 */
    int l = left;
    int leftEnd = right - 1;
    int len = rightEnd - left + 1;
    while (left <= leftEnd && right <= rightEnd) {
        if (a[left] <= a[right]) {
            temp[l] = a[left];
            left++;
        }
        else {
            temp[l] = a[right];
            right++;
        }
        l++;
    }
    while (left <= leftEnd)
        temp[l++] = a[left++];
    while (right <= rightEnd)
        temp[l++] = a[right++];
}
/* 一趟2路归并 */
void MergePass(int a[], int temp[], int n, int length) { /* length:当前有序子列的长度 */
    int i;
    for (i = 0; i <= n - 2 * length; i += 2 * length) {
        merge(a, temp, i, i + length, i + 2 * length - 1);
    }
    if (i + length < n)
        merge(a, temp, i, i + length, n - 1);
    else
        for (int j = i; j < n; j++)
            temp[j] = a[j];
}
int getLen(int b[], int n) {   /* 进行一趟归并排序 */
    for (int len = 2; len <= n / 2; len *= 2) {     
        int i;
        for (i = 0; i <= n - 2 * len; i += 2 * len)
            if (!is_sorted(b + i, b + i + 2 * len)) return len;
        if (!is_sorted(b + i, b + n)) return len;
    }
}
bool judge(int a[],int b[],int n) { /* 判断是不是插入排序 */
    int len = 1;
    int i;
    for ( i = 0; i < n - 1; i++)
        if (b[i] > b[i + 1]) {
            len = i + 1;
            break;
        }
    for (i=len; i < n; i++) {
        if (a[i] != b[i])
            return false;
    }
    sort(b, b + len + 1);
    return true;
}
void print(int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0)
            cout << a[i];
        else
            cout << " " << a[i];
    }
    cout << endl;
}
int main() {
    int a[101], b[101];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    if (judge(a, b, n)) {
        cout << "Insertion Sort" << endl;
        print(b, n);
    }
    else {
        cout << "Merge Sort" << endl;
        int* temp = (int *)malloc(n * sizeof(int));
        if (temp != NULL) {
            MergePass(b, temp, n, getLen(b, n));
            print(temp,n);
            free(temp);
        }
    }
}