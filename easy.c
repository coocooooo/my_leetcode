/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    int center;
    struct TreeNode *root;
    
    if (numsSize == 0)
        return NULL;

    root = malloc(sizeof(*root));

    if (numsSize & 0x1) // odd
        center = numsSize/2;
    else //even
        center = numsSize/2 - 1;
    root->val = nums[center];
    root->left = sortedArrayToBST(&nums[0], center);
    root->right = sortedArrayToBST(&nums[center + 1], numsSize - center - 1);
    
    return root;
}

char* addStrings(char* num1, char* num2) {
    int i, j;
    char *sum = calloc(5100, sizeof(char));
    int index = 0;
    int c;
    int v;
    
    c = 0;
    i = strlen(num1) - 1;
    j = strlen(num2) - 1;
    while (i >= 0 || j >= 0 || c == 1) {
        int a, b;
        
        if (i >= 0)
            a = num1[i] - '0';
        else
            a = 0;
            
        if (j >= 0)
            b = num2[j] - '0';
        else
            b = 0;
        
        v = a + b + c;
        if (v >= 10) {
            c = 1;
            v -= 10;
        } else
            c = 0;
        sum[index++] = v + '0';
        i--, j--;
    }

    for (i = 0; i < index/2; i++) {
        char t = sum[i];
        sum[i] = sum[index - i - 1];
        sum[index - i - 1] = t;
    }
    return sum;
}

int missingNumber(int* nums, int numsSize) {
    int sum = (numsSize * (numsSize + 1)) / 2;
    int lacksum = 0;
    int i;
    for (i = 0; i < numsSize; i++)
        lacksum += nums[i];
    return sum - lacksum;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *prev, *cur, *next;

    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;

    
    prev = head;
    cur = head->next;
    head->next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

/**
 * Old version is return *(int *)a - *(int *)b
 * but it's buggy because it cannot sort -2147483648 (-2147483648 - 1 = 2147483647)
 */
static int cmpint(const void *a, const void *b)
{
	int vala = *(int *)a;
	int valb = *(int *)b;
	if (vala > valb)
		return 1;
	else if (vala < valb)
		return -1;
	else
		return 0;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int i, j;
    int *buf;
    int index;
    int *ret;
    
    qsort(nums1, nums1Size, sizeof(int), cmpint);
    qsort(nums2, nums2Size, sizeof(int), cmpint);
    
    buf = calloc(nums2Size, sizeof(int));
    index = 0;
    
    i = j = 0;
    while (i < nums1Size && j < nums2Size) {
        if (nums1[i] < nums2[j])
            i++;
        else if (nums1[i] > nums2[j])
            j++;
        else {
            buf[index++] = nums1[i];
            i++, j++;
        }
    }

    *returnSize = index;
    return buf;
}

int numtobit(int num)
{
        int table[16] = {0, //0
                    1, //1
                    1, //2
                    2, //3
                    1, //4
                    2, //5
                    2, //6
                    3, //7
                    1, //8 -  1000
                    2, //9 -  1001
                    2, //10 - 1010
                    3, //11 - 1011
                    2, //12 - 1100
                    3, //13 - 1101
                    3, //14 - 1110
                    4}; //15 - 1111
                    
    return table[num/16] + table[num%16];
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** readBinaryWatch(int num, int* returnSize) {
    int count = 0;
    char *tmp[1000];
    char **ret;
    int i, j;
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 60; j++) {
            if (numtobit(i) + numtobit(j) == num) {
                char *t = calloc(6, sizeof(char));
                sprintf(t, "%d:%.2d", i, j);
                tmp[count++] = t;
            }
        }
    }
    ret = calloc(count, sizeof(char *));
    for (i = 0; i < count; i++) {
        ret[i] = tmp[i];
    }
    *returnSize = count;
    return ret;
}

bool containsDuplicate(int* nums, int numsSize) {
    int i;
    
    qsort(nums, numsSize, sizeof(int), numcmp);
    for (i = 0; i < numsSize - 1; i++)
        if (nums[i] == nums[i+1])
            break;
    if (i < numsSize - 1)
        return 1;
    return 0;
}

int longestPalindrome(char* s) {
    int counter[128] = {0,};
    int i;
    int len = strlen(s);
    int sum = 0;
    
    for (i = 0; i < len; i++) {
            counter[s[i]]++;
            if (0 == (counter[s[i]] & 0x1)) /* every second */
                sum++;
    }
    sum <<= 1;
    return sum == len ? sum : sum+1;
}

int hammingDistance(int x, int y) {
    int mask = (1 << 30);
    int distance = 0;
    
    do {
        if ((x & mask) ^ (y & mask))
            distance++;
        mask >>= 1;
    } while (mask);

    return distance;
}

int findComplement(int num) {
    int mask = (1 << 30);
    int i;
    
    while (!(num & mask))
        mask >>= 1;
        
    while (mask > 0) {
        num ^= mask;
        mask >>= 1;
    }
    return num;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) {
    char **pp = calloc(n, sizeof(char *));
    char buf[10] = {0,};
    int i;
    
    for (i = 1; i <= n; i++) {
        if ((i % 3) != 0 && (i % 5) != 0)
            sprintf(buf, "%d", i);
        if ((i % 3) == 0)
            sprintf(buf, "Fizz");
        if ((i % 5) == 0)
            strcat(buf, "Buzz");
        pp[i - 1] = calloc(strlen(buf) + 1, sizeof(char));
        strcpy(pp[i - 1], buf);
        memset(buf, 0, 10);
    }
    *returnSize = i - 1;
    return pp;
}

char* reverseString(char* s) {
    int len = strlen(s);
    int i;
    char temp;
    for (i = 0; i < len/2; i++) {
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    return s;
}

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int count = 0;
    int i;
    int max = 0;
    
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != 0 && i != 0)
            nums[i] = nums[i] + nums[i - 1];
        else if (nums[i] != 0 && i == 0)
            nums[i] = 1;
        else
            nums[i] = 0;
    }
    for (i = 0; i < numsSize; i++) {
        if (nums[i] > max)
            max = nums[i];
    }
    return max;
}

int islandPerimeter(int** grid, int gridRowSize, int gridColSize) {
    int r, c;
    int ret = 0;
    for (r = 0; r < gridRowSize; r++) {
        for (c = 0; c < gridColSize; c++) {
            if (grid[r][c] == 1) {
                if (c - 1 < 0)
                    ret++;
                else if (grid[r][c-1] == 0)
                    ret++;
                
                if (c + 1 >= gridColSize)
                    ret++;
                else if (grid[r][c+1] == 0)
                    ret++;
                
                if (r - 1 < 0)
                    ret++;
                else if (grid[r - 1][c] == 0)
                    ret++;
                    
                if (r + 1 >= gridRowSize)
                    ret++;
                else if (grid[r + 1][c] == 0)
                    ret++;
            }
        }
    }
    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int i;
    int count = 0;
    int *ret;
    int index;
#define MASK (1 << 31)

    for (i = 0; i < numsSize; i++) {
        index = nums[i] & ~MASK;
        nums[index - 1] |= MASK;
    }
    
    /*for (i = 0; i < numsSize; i++)
        if (!(nums[i] & MASK))
            count++;*/
            
    ret = calloc(/*count*/numsSize, sizeof(int));
    count = 0;
    for (i = 0; i < numsSize; i++) {
        if (!(nums[i] & MASK))
            ret[count++] = i + 1;
    }
    *returnSize = count;
    return ret;
}

int singleNumber(int* nums, int numsSize) {
    int ret = 0;
    int i;
    for (i = 0; i < numsSize; i++) {
        ret ^= nums[i];
    }
    return ret;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructRectangle(int area, int* returnSize) {
    int width = (int)sqrt(area);
    int length;
    int *ret;
    
    for (;width > 0; width--) {
        if ((area % width) == 0) {
            length = area / width;
            break;
        }
    }
    ret = malloc(sizeof(int) * 2);
    ret[0] = length;
    ret[1] = width;
    *returnSize = 2;
    return ret;
}

int getSum(int a, int b) {
    int c, b1, b2;
    int result = 0;
    unsigned int mask;
    
    c = 0;
    for (mask = 1; mask > 0; mask <<= 1) {
	    b1 = a & mask;
	    b2 = b & mask;
	    if (c)
		    c = mask;
	    else
		    c = 0;
        
        result |= (c ^ b1 ^ b2);
        
        if (c != 0 && (b1 || b2))
            c = 1;
        else if (c == 0 && (b1 && b2))
            c = 1;
        else 
            c = 0;
    }
    return result;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    int left, right;
    if (root == NULL)
        return 0;

    left = maxDepth(root->left);
    right = maxDepth(root->right);
    if (left < right)
        return right+1;
    else
        return left+1;
}

char findTheDifference(char* s, char* t) {
    int i;
    char result = 0;
    int sl = strlen(s);
    int tl = strlen(t);
    
    for (i = 0; i < tl - 1; i++) {
        result ^= s[i];
        result ^= t[i];
    }
    
    return result ^ t[i];
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    struct TreeNode *t;
    
    if (!root)
        return NULL;

    t = root->left;
    root->left = root->right;
    root->right = t;

    invertTree(root->left);
    invertTree(root->right);
    return root;
}

void moveZeroes(int* nums, int numsSize) {
    int i;
    int j;
    int last = -1;
    
    for (i = 0; i < numsSize - 1; i++) {
        if (nums[i] == 0) {
            if (last < 0)
                last = i + 1;
            for (j = last; j < numsSize; j++) {
                if (nums[j] != 0)
                    break;
            }
            if (j >= numsSize)
                break;
            nums[i] = nums[j];
            nums[j] = 0;
            last = j;
        }
    }
}

int numcmp(const void *pa, const void *pb)
{
    return *(int *)pa - *(int *)pb;
}

int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int i;
    int ret = 0;
    int j;
    
    qsort(g, gSize, sizeof(int), numcmp);
    qsort(s, sSize, sizeof(int), numcmp);
    
    for (i = 0; i < sSize; i++) {
        if (s[i] >= g[0])
            break;
    }
    
    for (; i < sSize; i++) {
        if (g[ret] <= s[i])
            ret++;
        if (ret >= gSize)
            break;
    }
    return ret;
}

int minMoves(int* nums, int numsSize) {
    int sum = 0;
    int min = nums[0];
    int i;
    for (i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (nums[i] < min)
            min = nums[i];
    }
    return sum - min * numsSize;
}

bool canConstruct(char* ransomNote, char* magazine) {
    int counter['z'-'a'+1] = {0,};
    int i;
    int msize = strlen(magazine);
    int rsize = strlen(ransomNote);
    
    for (i = 0; i < msize; i++) {
        counter[magazine[i] - 'a']++;
    }
    for (i = 0; i < rsize; i++) {
        counter[ransomNote[i] - 'a']--;
        if (counter[ransomNote[i] - 'a'] < 0)
            return 0;
    }
    return 1;
}

static int cmpint(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int i;
    int *buf;
    int index;
    int *ret;
    
    qsort(nums1, nums1Size, sizeof(int), cmpint);
    qsort(nums2, nums2Size, sizeof(int), cmpint);
    
    buf = calloc(nums2Size, sizeof(int));
    index = 0;
    for (i = 0; i < nums2Size; i++) {
        ret = bsearch(&nums2[i], nums1, nums1Size, sizeof(int), cmpint);
        if (ret) {
            if (index == 0)
                buf[index++] = nums2[i];
            else if (buf[index-1] != nums2[i])
                buf[index++] = nums2[i];
        }
    }
    *returnSize = index;
    return buf;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumOfLeftLeaves(struct TreeNode* root) {
    int left = 0;

    if (root == NULL)
        return 0;
    if (root->left != NULL) {
        if (root->left->right == NULL && root->left->left == NULL)
            left = root->left->val;
        else
            left = sumOfLeftLeaves(root->left);
    }
    return left + sumOfLeftLeaves(root->right);
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void deleteNode(struct ListNode* node) {
    struct ListNode *tmp = node->next;
    
    *node = *node->next;
    free(tmp);
}

int firstUniqChar(char* s) {
    int i;
    //int counter['z'-'a'+1];

    int *counter = calloc('z'-'a'+1, sizeof(int));
    int size = strlen(s);
    for (i = 0; i < 'z'-'a'+1; i++)
        counter[i] = 0;
    for (i = 0; i < size; i++) {
        counter[s[i] - 'a']++;
    }
    for (i = 0; i < size; i++) {
        if (counter[s[i] - 'a'] == 1) {
            free(counter);
            return i;
        }
    }
    free(counter);
    return -1;
}

int titleToNumber(char* s) {
    int num = 0;
    while (1) {
        num += *s - 'A' + 1;
        s++;
        if (*s) {
            num *= 26;
            continue;
        } else
            break;
    }
    return num;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == q)
        return 1;
    else if (p && q)
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else
        return 0;

    /*
     *
     * oneline version
     *return (p == q) || (p && q && (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
     */
}

bool isAnagram(char* s, char* t) {
    int counter_s['z' - 'a' + 1] = {0,};
    int counter_t['z' - 'a' + 1] = {0,};
    char sum = 0;
    int i;
    int len_s = strlen(s);
    int len_t = strlen(t);
    
    if (len_s != len_t)
        return 0;
        
    for (i = 0; i < len_s; i++) {
        counter_s[s[i] - 'a']++;
        counter_t[t[i] - 'a']++;
    }
    return !memcmp(counter_s, counter_t, sizeof(int) * ('z'-'a'+1));
}

#if 0
/*
Boyer-Moore Majority Vote Algorithm
http://www.cs.utexas.edu/~moore/best-ideas/mjrty/
*/
int majorityElement(int* nums, int numsSize) {
    int major = nums[0];
    int count = 1;
    int i;
    
    for (i = 1; i < numsSize; i++) {
        if (nums[i] == major) {
            count++;
        } else if (count == 0) {
            major = nums[i];
            count++;
        } else {
            count--;
        }
    }
    return major;
}
#endif

int majorityElement(int* nums, int numsSize) {
    int major = (numsSize >> 1);
    int i;
    
    qsort(nums, numsSize, sizeof(int), numcmp);
	/* for (i = 0; i < numsSize; i++) */
	/* 	printf("%d\n", nums[i]); */

    
    /*for (i = 0; i < numsSize; i++) {
	    if (nums[i] == nums[i + major])
		    break;
    }
    return nums[i];*/
    return nums[numsSize/2];
}


