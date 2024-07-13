#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>

template <typename T>
void printMatrix(std::vector<std::vector<T>> arr)
{
    for (auto& row : arr)
    {
        for (auto& cell : row)
        {
            std::cout << cell << " ";
        }

        std::cout << std::endl;
    }
}

void zad1()
{
    char s[1000000];
    scanf("%s", &s);
    int len = strlen(s);

    std::vector<int> a(26, 0);

    for (int i = 0; i < len; i++)
    {
        a[s[i] - (int)'a']++;
    }

    std::vector<char> pal;

    int midChar = -1;
    bool isOdd = len % 2 == 1;
    for (int i = 0; i < 52; ++i)
    {
        int charInd = i < 26 ? i : 52 - i - 1;
        int totalCount = a[charInd];

        if (totalCount == 0) continue;

        if (totalCount % 2 == 1)
        {
            if (!isOdd || midChar != -1)
            {
                printf("%s", "IMPOSSIBLE");
                return;
            }
            midChar = i + (int)'a';
        }

        int newTotalPlaced = pal.size() + totalCount / 2 + (totalCount % 2 == 1 ? 1 : 0);

        if (newTotalPlaced > (len / 2) && pal.size() <= (len / 2) && isOdd)
        {
            int beforeMid = len / 2 - pal.size();
            int afterMid = a[charInd] / 2 - beforeMid;

            for (int y = 0; y < beforeMid; y++)
            {
                pal.push_back(charInd + (int)'a');
            }

            pal.push_back(midChar);
            a[midChar - (int)'a']--;

            for (int y = 0; y < afterMid; y++)
            {
                pal.push_back(charInd + (int)'a');
            }
        }
        else
        {
            for (int y = 0; y < totalCount / 2; y++)
            {
                pal.push_back(charInd + (int)'a');
            }
        }
    }

    for (int i = 0; i < pal.size(); i++)
    {
        printf("%c", pal[i]);
    }

    return;
}

void bazinga()
{
    char t[1000];
    int countSort[6] = { 0, 0, 0, 0, 0, 0 };

    std::cin.getline(t, 1000);

    int len = strlen(t);
    
    for (int i = 0; i < len; i++)
    {
        if (t[i] == 'B' || t[i] == 'b') countSort[1]++;
        else if (t[i] == 'A' || t[i] == 'a') countSort[0]++;
        else if (t[i] == 'Z' || t[i] == 'z') countSort[2]++;
        else if (t[i] == 'I' || t[i] == 'i') countSort[3]++;
        else if (t[i] == 'N' || t[i] == 'n') countSort[4]++;
        else if (t[i] == 'G' || t[i] == 'g') countSort[5]++;
    }

    int min = countSort[0] / 2;

    for (int i = 1; i < 6; i++)
    {
        if (min > countSort[i]) min = countSort[i];
    }

    printf("%d", min);
}

template <typename T>
void bubbleSort(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int y = 0; y < arr.size() - i - 1; y++)
        {
            bool shouldSwap = !comparer(arr[y], arr[y + 1]);

            if (shouldSwap)
            {
                T copy = arr[y];
                arr[y] = arr[y + 1];
                arr[y + 1] = copy;
            }
        }
    }
}

template <typename T>
void selectionSort(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    for (int i = 0; i < arr.size(); i++)
    {
        int min = i;
        for (int y = i; y < arr.size(); y++)
        {
            bool isNewMin = comparer(arr[y], arr[min]);

            if (isNewMin)
            {
                min = y;
            }
        }

        if (min != i)
        {
            T copy = arr[i];
            arr[i] = arr[min];
            arr[min] = copy;
        }
    }
}

template <typename T>
void insertionSort(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    for (int i = 1; i < arr.size(); i++)
    {
        auto curCopy = arr[i];
        int lastY = 0;
        for (int y = i - 1; y >= 0; y--)
        {
            bool isBefore = comparer(curCopy, arr[y]);

            if (isBefore)
            {
                arr[y + 1] = arr[y];
            }
            else
            {
                lastY = y + 1;
                break;
            }
        }

        arr[lastY] = curCopy;
    }
}

template <typename T>
void mergeInPlace1(std::vector<T>& arr, int left, int right, int rightEnd,
    std::function<bool(T&, T&)> comparer)
{
    std::vector<T> sorted;
    sorted.resize(rightEnd - left + 1);
    // sorted.reserve(rightEnd - left + 1);

    int sortedInd = 0;
    int leftInd = left;
    int rightInd = right;

    while (leftInd < right && rightInd <= rightEnd)
    {
        bool isLeft = comparer(arr[leftInd], arr[rightInd]);

        if (isLeft)
        {
            sorted[sortedInd++] = arr[leftInd++];
        }
        else
        {
            sorted[sortedInd++] = arr[rightInd++];
        }
    }

    while (leftInd < right)
    {
        sorted[sortedInd++] = arr[leftInd++];
    }

    while (rightInd <= rightEnd)
    {
        sorted[sortedInd++] = arr[rightInd++];
    }

    for (int i = 0; i < sorted.size(); i++)
    {
        arr[left + i] = sorted[i];
    }
}

template <typename T>
void mergeSortFromTo1(std::vector<T>& arr, int begin, int end,
    std::function<bool(T&, T&)> comparer)
{
    if (begin == end)
    {
        return;
    }
    mergeSortFromTo1(arr, begin, (end + begin) / 2, comparer);
    mergeSortFromTo1(arr, (end + begin) / 2 + 1, end, comparer);
    return mergeInPlace1(arr, begin, (end + begin) / 2 + 1, end, comparer);
}

template <typename T>
void mergeSort1(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    mergeSortFromTo1(arr, 0, arr.size() - 1, comparer);
}

template <typename T>
std::vector<T> merge2(std::vector<T>& left, std::vector<T>& right,
    std::function<bool(T&, T&)> comparer)
{
    std::vector<T> sorted;
    sorted.resize(left.size() + right.size());
    // sorted.reserve(rightEnd - left + 1);

    int sortedInd = 0;
    int leftInd = 0;
    int rightInd = 0;

    while (leftInd < left.size() && rightInd < right.size())
    {
        bool isLeft = comparer(left[leftInd], right[rightInd]);

        if (isLeft)
        {
            sorted[sortedInd++] = left[leftInd++];
        }
        else
        {
            sorted[sortedInd++] = right[rightInd++];
        }
    }

    while (leftInd < left.size())
    {
        sorted[sortedInd++] = left[leftInd++];
    }

    while (rightInd < right.size())
    {
        sorted[sortedInd++] = right[rightInd++];
    }

    return sorted;
}

template <typename T>
std::vector<T> mergeSortFromTo2(std::vector<T>& arr, int begin, int end,
    std::function<bool(T&, T&)> comparer)
{
    if (begin == end)
    {
        return std::vector<T> { arr[begin] };
    }
    auto left = mergeSortFromTo2(arr, begin, (end + begin) / 2, comparer);
    auto right = mergeSortFromTo2(arr, (end + begin) / 2 + 1, end, comparer);
    return merge2(left, right, comparer);
}

template <typename T>
std::vector<T> mergeSort2(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    return mergeSortFromTo2(arr, 0, arr.size() - 1, comparer);
}

template <typename T>
void quickSortFromTo2(std::vector<T>& arr, int left, int right,
    std::function<bool(T&, T&)> comparer)
{
    if (left == arr.size() || right < 0 || left >= right)
    {
        return;
    }

    int pivotInd = (left + right) / 2;
    int lastBeforePivotInd = left;

    for (int i = left; i <= right; i++)
    {
        if (pivotInd == i) continue;

        bool isBeforePivot = comparer(arr[i], arr[pivotInd]);
        if (isBeforePivot)
        {
            std::swap(arr[lastBeforePivotInd], arr[i]);
            if (lastBeforePivotInd == pivotInd)
            {
                pivotInd = i;
            }

            lastBeforePivotInd++;
        }
    }

    std::swap(arr[lastBeforePivotInd], arr[pivotInd]);

    quickSortFromTo2(arr, left, lastBeforePivotInd - 1, comparer);
    quickSortFromTo2(arr, lastBeforePivotInd + 1, right, comparer);
}

template <typename T>
void quickSort2(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    quickSortFromTo2(arr, 0, arr.size() - 1, comparer);
}

template <typename T>
int partition(std::vector<T>& arr, int left, int right,
    std::function<bool(T&, T&)> comparer)
{
    int pivotInd = (left + right) / 2;
    int lastBeforePivotInd = left;

    for (int i = left; i <= right; i++)
    {
        if (pivotInd == i) continue;

        bool isBeforePivot = comparer(arr[i], arr[pivotInd]);
        if (isBeforePivot)
        {
            std::swap(arr[lastBeforePivotInd], arr[i]);
            if (lastBeforePivotInd == pivotInd)
            {
                pivotInd = i;
            }

            lastBeforePivotInd++;
        }
    }

    std::swap(arr[lastBeforePivotInd], arr[pivotInd]);

    return lastBeforePivotInd;
}

template <typename T>
void quickSortFromTo(std::vector<T>& arr, int left, int right,
    std::function<bool(T&, T&)> comparer)
{
    if (left == arr.size() || right < 0 || left >= right)
    {
        return;
    }

    int pivotInd = partition(arr, left, right, comparer);

    quickSortFromTo(arr, left, pivotInd - 1, comparer);
    quickSortFromTo(arr, pivotInd + 1, right, comparer);
}

template <typename T>
void quickSort(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    quickSortFromTo(arr, 0, arr.size() - 1, comparer);
}

template <typename T>
int partitionRight(std::vector<T>& arr, int left, int right,
    std::function<bool(T&, T&)> comparer)
{
    int pivotInd = right;
    int lastBeforePivotInd = left;

    for (int i = left; i < right; i++)
    {
        bool isBeforePivot = comparer(arr[i], arr[pivotInd]);
        if (isBeforePivot)
        {
            std::swap(arr[lastBeforePivotInd], arr[i]);
            lastBeforePivotInd++;
        }
    }

    std::swap(arr[lastBeforePivotInd], arr[pivotInd]);

    return lastBeforePivotInd;
}

template <typename T>
void quickSortRightFromTo(std::vector<T>& arr, int left, int right,
    std::function<bool(T&, T&)> comparer)
{
    if (left == arr.size() || right < 0 || left >= right)
    {
        return;
    }

    int pivotInd = partitionRight(arr, left, right, comparer);

    quickSortRightFromTo(arr, left, pivotInd - 1, comparer);
    quickSortRightFromTo(arr, pivotInd + 1, right, comparer);
}

template <typename T>
void quickSortRight(std::vector<T>& arr,
    std::function<bool(T&, T&)> comparer)
{
    quickSortRightFromTo(arr, 0, arr.size() - 1, comparer);
}

template <typename T>
std::vector<T> sortTheStudents(std::vector<T>& score, int k) {
    bubbleSort(score, [k](T& s1, T& s2) {
        return s1[k] > s2[k];
        });

    return score;
}

void evil()
{
    int n, m;
    scanf("%d %d\n", &n, &m);

    std::vector<std::pair<int, int>> lepenki;
    lepenki.resize(m);

    for (unsigned i = 0; i < m; i++)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        lepenki[i].first = start;
        lepenki[i].second = end;
    }

    quickSortRight<std::pair<int, int>>(lepenki,
        [](std::pair<int, int>& left, std::pair<int, int>& right) {
            return left.first < right.first;
        }
    );

    int curStart = lepenki[0].first,
        curEnd = lepenki[0].second;

    int totalCovered = 0;

    for (int i = 1; i < m; i++)
    {
        int nextStart = lepenki[i].first,
            nextEnd = lepenki[i].second;

        if (nextStart > curEnd)
        {
            totalCovered += curEnd - curStart + 1;
            curStart = nextStart;
            curEnd = nextEnd;
        }
        else
        {
            curEnd = std::max(nextEnd, curEnd);
        }
    }

    totalCovered += curEnd - curStart + 1;

    printf("%lld", totalCovered);
}
/*
114, 120, 334, 402, 564, 578, 720, 758, 1112, 1424, 1427, 1436, 1534, 1538, 1604, 1702, 1792
2, 216, 244, 464, 644, 678, 892, 1104, 1134, 1150, 1156, 1178, 1392, 1608, 1670, 1799, 1828
*/

int main()
{
    //bazinga();
    /*auto kur = std::vector<std::vector<int>>{ {10, 6, 9, 1}, {7, 5, 11, 2}, {4, 8, 3, 15} };
    quickSortRight<std::vector<int>>(kur, [](std::vector<int>& left, std::vector<int>& right) {
        return left[2] > right[2];
    });

    printMatrix(kur);*/

    evil();

    return 0;
}
