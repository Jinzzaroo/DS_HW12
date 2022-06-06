/* sorting-hashing.c */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 13
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

// array 관련 함수
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

// 정렬 함수
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);

// 해싱 관련 함수
int hashCode(int key);
int hashing(int *a, int **ht);
int search(int *ht, int key);

int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    // key, index : -1로 초기화
    int key = -1;
    int index = -1;

    srand(time(NULL));

    printf("\n[----- [JinYeongKim] [2019038030] -----]\n");
    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            initialize(&array);
            break;
        case 'q':
        case 'Q':
            freeArray(array);
            break;
        case 's':
        case 'S':
            selectionSort(array);
            break;
        case 'i':
        case 'I':
            insertionSort(array);
            break;
        case 'b':
        case 'B':
            bubbleSort(array);
            break;
        case 'l':
        case 'L':
            shellSort(array);
            break;
        case 'k':
        case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h':
        case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e':
        case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p':
        case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

// array 메모리 할당
int initialize(int **a)
{
    // array에 메모리 할당해주기 위한 temp
    int *temp = NULL;

    // array가 NULL일 때
    if (*a == NULL)
    {
        temp = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp; // array에 메모리 할당
                   // main 함수에서 array 사용할 수 있게끔 하기 위해 temp를 이용한 메모리 할당 방식 사용

        // array가 NULL이 아니면 기존 array 재사용
    }
    else
        temp = *a;

    // temp를 이용해 array를 참조하여 0~12 범위의 랜덤값 할당
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}

// array 메모리 해제
int freeArray(int *a)
{
    if (a != NULL)
        free(a);
    return 0;
}

// array 출력
void printArray(int *a)
{
    // array가 NULL일 때
    if (a == NULL)
    {
        printf("nothing to print.\n");
        return;
    }

    // array index 출력
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("a[%02d] ", i);
    printf("\n");

    // array key 출력
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}

// 선택 정렬
int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i; //기준 위치 설정
        min = a[i];   //기준 위치의 값을 일단 min으로 설정

        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
        {
            //기준 위치 바로 다음부터 배열 끝까지 조사하여 기준 위치의 값과 비교했을 때 더 작은 값이 있으면
            if (min > a[j])
            {
                min = a[j];   // 그 값을 최솟값으로 select
                minindex = j; // 그 위치를 minindex로 select
            }
        }
        //기준 위치와 방금 찾은 최솟값의 위치 교환
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}

// 삽입 정렬
int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i]; // t에 정렬 대상 원소 저장
        j = i;    // 정렬 대상 원소의 인덱스를 j에 저장

        //이미 정렬된 마지막 원소 a[j-1]부터 역순으로 정렬 대상 원소 t와 비교하여 a[j-1] < t < a[j]인 j 찾을 때까지 반복
        while (a[j - 1] > t && j > 0)
        {
            a[j] = a[j - 1];
            j--;
        }
        // 찾은 자리에 insert
        a[j] = t;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

// 버블 정렬
int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {
            //인접한 두 원소끼리 비교하여 정렬
            if (a[j - 1] > a[j])
            {
                // a[j-1]과 a[j] 위치 변경
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

// 셸 정렬
int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    // 간격(interval)을 원소 개수의 1/2로 설정하고 한 단계 끝날때 마다 반으로 감소
    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
    {
        for (i = 0; i < h; i++)
        {
            // interval만큼 떨어져 있는 원소들을 선택
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];
                k = j;
                // 선택한 원소들을 대상으로 삽입 정렬 수행
                while (k > h - 1 && a[k - h] > v)
                {
                    a[k] = a[k - h];
                    k -= h;
                }
                a[k] = v;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);

    return 0;
}

// 퀵 정렬
int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n - 1]; //마지막 원소를 피봇으로 설정
        i = -1;
        j = n - 1;

        while (1)
        {
            while (a[++i] < v) // 피봇보다 큰 a[L] 찾을 때까지 i++
                ;
            while (a[--j] > v) // 피봇보다 작은 a[R] 찾을 때까지 j--
                ;

            // 퀵 정렬이 끝나는 조건
            if (i >= j)
                break;

            // a[L](a[i])와 a[R](a[j])를 서로 교환
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
        // 마지막 단계 : 피봇과 a[L] 서로 교환
        t = a[i];
        a[i] = a[n - 1];
        a[n - 1] = t;

        quickSort(a, i);                 // 피봇의 왼쪽 부분집합에 대한 퀵 정렬
        quickSort(a + i + 1, n - i - 1); // 피봇의 오른쪽 부분집합에 대한 퀵 정렬
    }

    return 0;
}

// 해시 함수(by Division)
int hashCode(int key)
{
    return key % MAX_HASH_TABLE_SIZE;   //키값을 테이블 크기로 나눈 나머지를 해시 주소로 사용
}

int hashing(int *a, int **ht)   //**ht 사용하여 main에서 *ht control 가능케 한다
{
    int *hashtable = NULL;

    //해시 테이블이 NULL일 때
    if (*ht == NULL)
    {
        //*ht에 메모리 할당
        hashtable = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;
    }
    else
    {
        //NULL이 아니면 *ht 재활용
        hashtable = *ht;
    }

    //해시 테이블의 값 -1로 초기화 (-1이면 비어있다는 뜻)
    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);       // 키값을 해시 함수 이용하여 해시 주소로 변경

        // 해시 테이블 속 버킷 주소가 비어있으면 키값 넣어줌
        if (hashtable[hashcode] == -1)
        {
            hashtable[hashcode] = key;
        }

        // 해시 테이블 속 버킷 주소에 키값이 이미 존재하면 (충돌 발생 -> 오버로드)
        // 하나씩 index를 증가시켜 비어 있는 버킷 주소 index 를 찾아서 그 index에 key 넣어줌
        else
        {

            index = hashcode;

            while (hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;    //마지막 index에서 다음 index는 0
            }
            hashtable[index] = key;
        }
    }

    return 0;
}

int search(int *ht, int key)
{
    int index = hashCode(key);

    if (ht[index] == key)
        return index;

    while (ht[++index] != key)
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;
}
