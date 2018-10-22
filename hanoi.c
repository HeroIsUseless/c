//从下往上递归
void hanoi(int n, char x, char y, char z)//从x柱搬到z柱，完全搬掉
{
    if(n == 1)
    {
        move(x, 1, z);
    }
    else
    {
        hanoi(n-1, x, z, y);
        move(x, n, z);
        hanoi(n-1, y, x, z);
    }
}
void move()
{

}
