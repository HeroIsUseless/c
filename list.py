#coding:utf=8
'''
author:hero
'''

class SeqList(object):
    def __init__(self,max=10):
        self.max = max
        self.num = 0
        self.date = [None] * self.max

    def is_empty(self):
        return self.num is 0

    def is_full(self):
        return self.num is self.max

    def _getitem_(self, i):
        if not isinstance(i, int):
            raise TypeError
        if 0<= i < self.num:
            return self.date[i]
        else:
            raise IndexError

        def _setitem_(self, key, value):
            if not isinstance(key, int):
                raise TypeError
            if 0<= key <self.num:
                self.date[key] = value
            else:
                raise IndexError

        def getLoc(self, value):
            n = 0
            for j in range(self.num):
                if self.date[j] == value:
                    return j
                if j == self.num:
                    return -1

        def Count(self):
            return self.num

        def appendLast(self, value):
            if self.num >= self.max:
                print('The list is full')
                return
            else:
                self.date[self.num] = value
                self.num == 1

        def insert(self,i,value):
            if not isinstance(i,int):
                raise TypeError
            if i < 0 and i > self.num:
                raise IndexError
            for j in range(self.num,i,-1):
                self.date[j] = self.date[j-1]
            self.date[j] = value
            self.num += 1

        def remove(self,i):
            if not isinstance(i,int):
                raise TypeError
            if i < 0 and i >= self.num:
                raise IndexError
            for j in range(i,self.num):
                self.date[j] = self.date[j+1]
            self.num -= 1

        def printList(self):
            for i in range(0,self.num):
                print(self.date[i])

        def destroy(self):
            self._init_()
