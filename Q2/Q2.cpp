// C++ program to print largest contiguous array sum
#include <bits/stdc++.h>
using namespace std;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int max(int a, int b, int c)
{
    return max(max(a, b), c);
}

int maxCrossingSum(int arr[], int l, int m, int h)
{
    // Include elements on left of mid.
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        sum = sum + arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    // Include elements on right of mid
    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m; i <= h; i++)
    {
        sum = sum + arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }

    // Return sum of elements on left and right of mid

    return max(left_sum + right_sum - arr[m], left_sum, right_sum);
}

int maxSubArraySum(int arr[], int l, int h)
{

    if (l > h)
        return INT_MIN;
    // Base Case: Only one element
    if (l == h)
        return arr[l];

    int m = (l + h) / 2;

    /* Return maximum of following three possible cases
            a) Maximum subarray sum in left half
            b) Maximum subarray sum in right half
            c) Maximum subarray sum such that the subarray
    crosses the midpoint */
    return max(maxSubArraySum(arr, l, m - 1),
               maxSubArraySum(arr, m + 1, h),
               maxCrossingSum(arr, l, m, h));
}
// timecomplexity: O(nlogn)  using divide and conquer approach

// time complexity : O(n) as we are traversing the whole array once (kadane's algo)
// int maxSubArraySum1(int a[], int size)
// {
//     int max_so_far = INT_MIN, max_ending_here = 0;

//     for (int i = 0; i < size; i++){
//         max_ending_here = max_ending_here + a[i];
//         if (max_so_far < max_ending_here)
//             max_so_far = max_ending_here;

//         if (max_ending_here < 0)
//             max_ending_here = 0;
//     }
//     return max_so_far;
// }

int main()
{
    const int n = 1000;
    ofstream inputfile("input2.txt");
    inputfile << n << endl;
    int A[n];
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 100 - 50;
        inputfile << num << " ";
    }
    inputfile << endl;
    inputfile.close();

    ifstream inputFile("input2.txt");
    for (int i = 0; i < n; i++)
    {
        inputFile >> A[i];
    }
    inputFile.close();

    int max_sum = maxSubArraySum(A, 0, n - 1);
    ofstream outputfile("output2.txt");
    outputfile << "Maximum contiguous sum is " << max_sum;
    return 0;
}
