
class EventBarrier{
public:
    EventBarrier();
    ~EventBarrier();
    void Wait(); // 阻塞线程
    void Signal(); // 更像是一个广播
    void Complete();
    int Waiters(); // 返回阻塞中的线程     
};

class Alarm{
public:
    Alarm();
    ~Alarm();
    void Pause(int howLong);
    void Awaken();
    List *queue;
    int num;
};