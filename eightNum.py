#coding=utf-8
import copy

chess_final = [1,2,3,8,0,4,7,6,5]

class Node:
    chess = []
    pos0 = 0
    f = 0
    g = 0
    def __init__(self, chess, g):
        self.chess = chess # 棋盘
        self.pos0 = chess.index(0) # 空格的位置
        self.g = g # 层数
        h = 0
        i = 0
        for i, k in enumerate(chess_final): # 求出f值
            if self.chess[i] != k:
                h += 1
        self.f = h + g

    def swap0(self, i): # 空格的移动
        chesres = copy.deepcopy(self.chess)
        chesres[i], chesres[self.pos0] = chesres[self.pos0], chesres[i]
        return chesres

changable = [[-1,-1,3,1],[0,2,4,-1],[-1,1,5,-1],
			 [ 4,6,0,-1],[3,1,5, 7],[ 2,4,8,-1],
			 [3,-1,-1,7],[6,4,8,-1],[5,7,-1,-1]]

def getMinF(open_table): # 获取里面的最小项
    f_tmp = open_table[0].f # inf
    ind_tmp = 0
    for i,node in enumerate(open_table): # 下面开始循环求解，弹出最小评价节点
        if f_tmp > node.f:
            f_tmp = node.f
            ind_tmp = i # 在这里找到最小值的坐标  
    return ind_tmp

def getNewState(node, i):
    if changable[node.pos0][i] != -1: # 如果可以运动
        return node.swap0(changable[node.pos0][i])   
    else:
        return [0,0,0,0,0,0,0,0,0]
        
def solve(open_table, flag):
    while len(open_table) != 0: 
        node_tmp = open_table.pop(getMinF(open_table)) # 找到f最小的点并pop出
        for i in range(0, 4): # 扩展新状态，空方格的上下左右运动判断
            chess_tmp = getNewState(node_tmp, i) # 获取一个新移动状态
            if str(chess_tmp) in flag: # 如果在里面那么什么也不干
                pass
            else: #  如果不在，进行添加
                open_table.append(Node(chess_tmp, node_tmp.g+1))
                flag.add(str(chess_tmp))
                print(str(chess_tmp))       
            if chess_tmp == chess_final: # 判断一下是否成功了
                return node_tmp.g + 1
    else:
        return 0 # open表不可能为空的，空表示错误没有输出
#[2,8,3,1,6,4,7,0,5]
if __name__ == "__main__":
    node = Node([2,8,3,1,6,4,7,0,5], 0) # 初始化棋盘
    open_table = []
    open_table.append(node)
    flag = set(str([0,0,0,0,0,0,0,0,0]))
    flag.add(str(node.chess)) # 最初标志位初始化
    k = solve(open_table, flag) # 进行解决
    print(k)
