#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int Elem;
typedef enum bool{false, true} bool;
typedef struct DynamicArray
{
    size_t capacity;   // 数组的容量，初始值和最小值均为16u
    size_t size;       // 数组中元素的个数
    Elem* data;     // 用于保存数组中元素的内存空间
} DynamicArray;
/*
 * ┏┓　　　┏┓
 * ┏┛┻━━━┛┻┓
 * ┃　　　　　　　┃ 　
 * ┃　　　━　　　┃
 * ┃　┳┛　┗┳　┃
 * ┃　　　　　　　┃
 * ┃　　　┻　　　┃
 * ┃　　　　　　　┃
 * ┗━┓　　　┏━┛
 *  ┃　　　┃   神兽保佑　　　　　　　　　
 *  ┃　　　┃   代码无BUG！
 *  ┃　　　┗━━━┓
 *  ┃　　　　　　　        ┣┓
 *  ┃　　　　　　　        ┏┛
 *  ┗┓┓┏━┳┓┏┛
 *    ┃┫┫　┃┫┫
 *    ┗┻┛　┗┻┛
 *
 */
DynamicArray* DynamicArray_new(){
    DynamicArray *da = (DynamicArray*)malloc(sizeof(DynamicArray));
    da->capacity = 16;
    da->size = 0;
    da->data = (Elem*)malloc(sizeof(Elem) * 16);
    return da;
}
void DynamicArray_insert(DynamicArray* this, size_t pos, const Elem* v){
    int i;
    if(pos >= this->size) return;
    while(this->size >= this->capacity)
        DynamicArray_recapacity(this, this->capacity * 2);
    for(i=this->size; i>pos; i--)
        this->data[i] = this->data[i-1];
    this->data[pos] = *v; this->size++;
}
Elem DynamicArray_erase(DynamicArray* this, size_t pos){
    int i, res;
    if(pos >= this->size) return 0;
    res = this->data[pos];
    for(i=pos; i<this->size-1; i++)
        this->data[i] = this->data[i+1];
    this->size--;
    while((float)this->size/(float)this->capacity < 0.25 && this->capacity >16)
        DynamicArray_recapacity(this, this->capacity / 2);
        return res;
}
Elem DynamicArray_get(const DynamicArray* this, size_t pos){
    if(pos >= this->size) return 0;
    return this->data[pos];
}
void DynamicArray_set(DynamicArray* this, size_t pos, const Elem* v){
    if(pos >= this->size) return;
    this->data[pos] = *v;
}
size_t DynamicArray_capacity(const DynamicArray* this){
    return this->capacity;
}
size_t DynamicArray_size(const DynamicArray* this){
    return this->size;
}
bool DynamicArray_empty(const DynamicArray* this){
    if(this->size) return false;
    else return true;
}
void DynamicArray_recapacity(DynamicArray* this, size_t new_capacity){
    int i, n;
    Elem *pe;
    if(this->capacity >= new_capacity) n = new_capacity;
    else n = this->capacity;
    pe = (Elem*)malloc(sizeof(Elem) * new_capacity);
        for(i=0; i<n; i++)
            pe[i] = this->data[i];
        this->capacity = new_capacity;
        free(this->data);
        this->data = pe;
}
void DynamicArray_resize(DynamicArray* this, size_t new_size){
    if(this->size >= new_size){
        this->size = new_size;
        while((float)this->size/(float)this->capacity < 0.25 && this->capacity>16)
            DynamicArray_recapacity(this, this->capacity / 2);
    }else{
        while(this->capacity < new_size)
            DynamicArray_recapacity(this, this->capacity * 2);
        this->size = new_size;
    }
}
void DynamicArray_delete(DynamicArray* this){
    free(this->data);
    free(this);
}
int main()
{
    char line[100];
    DynamicArray* arr = NULL;
    size_t size;
    size_t pos;
    Elem v;

    return 0;
}

