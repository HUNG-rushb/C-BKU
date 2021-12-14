#include <iostream>
#include <algorithm>

#define FOR(i, a, b) for (int i = (a), _b = (b); i < _b; i++)
#define FOR_(i, a, b) for (int i = (a), _b = (b); i <= _b; i++)
#define _FOR(i, a, b) for (int i = (a), _b = (b); i >= _b; i--)

#define LL long long
#define NM 100001

using namespace std;

struct Pizza
{
    LL t, l;
} p[NM];

int n;
LL wait, t;
int nH, heap[NM], pos[NM];

bool compare(Pizza x, Pizza y)
{
    return x.t < y.t;
}

void UpHeap(int i)
{
    int parent, child = pos[i];
    while (child > 1)
    {
        parent = child / 2;
        if (p[i].l < p[heap[parent]].l)
        {
            heap[child] = heap[parent];
            pos[heap[child]] = child;
            child = parent;
        }
        else
            break;
    }
    heap[child] = i;
    pos[i] = child;
}

void DownHeap(int i)
{
    int child, parent = pos[i];
    while (parent * 2 <= nH)
    {
        child = parent * 2;
        if (child < nH && p[heap[child + 1]].l < p[heap[child]].l)
            child++;
        if (p[i].l > p[heap[child]].l)
        {
            heap[parent] = heap[child];
            pos[heap[parent]] = parent;
            parent = child;
        }
        else
            break;
    }
    heap[parent] = i;
    pos[i] = parent;
}

void Insert(int i)
{
    heap[++nH] = i;
    pos[i] = nH;
    UpHeap(i);
}

void Delete()
{
    pos[heap[1]] = 0;
    heap[1] = heap[nH--];
    pos[heap[1]] = 1;
    DownHeap(heap[1]);
}

int minWaitingTime(int n, int arrivalTime[], int completeTime[])
{
    //cout << n << endl;

    for (int i = 0; i < n; i++)
    {
        p[i].t = arrivalTime[i];
        p[i].l = completeTime[i];
        //cout << p[i].t << " " << p[i].l << endl;
    }

    ios::sync_with_stdio(0);
    sort(p, p + n, compare);
    p[n].t = (LL)1000000000 * 1000000000;

    int current = 0;
    wait = 0;
    t = 0;

    while (1)
    {
        while (p[current].t <= t)
        {
            Insert(current++);
        }

        if (nH == 0)
        {
            if (current == n)
                break;
            t = p[current].t;
        }
        else
        {
            t += p[heap[1]].l;
            wait += t - p[heap[1]].t;
            Delete();
        }
    }

    return wait;
}

int main()
{

    int n = 3;
    int arrvalTime[] = {0, 1, 2};
    int completeTime[] = {3, 9, 6};

    cout << minWaitingTime(n, arrvalTime, completeTime);
    return 0;
}
