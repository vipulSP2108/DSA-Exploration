#include "/Users/aai/Desktop/test.h"
#include <stdio.h>
#include <string.h> // for testing generate_splits()


/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */


//part1

// void generate_selections(int a[], int n, int k, int l, int i, int b[], void *data, void (*process_selection)(int *b, int k, void *data)) {
//   if (l == k) {
//     if (process_selection != NULL) {
//       process_selection(b, k, data);
//     }
//     return;
//   }

//   if (i < n) {
//     b[l] = a[i];
//     generate_selections(a, n, k, l + 1, i + 1, b, data, process_selection);
//     generate_selections(a, n, k, l, i + 1, b, data, process_selection);
//   }
// }

// void process_selection(int *b, int k, void *data) {
//     printArray(b, k);
// }

void temp_selections(int a[], int n, int k, int b[], int l, int start, void *data, void (*process_selection)(int *b, int k, void *data))
{
    if (l == k){
        process_selection(b, k, data);
        return;
    }

    for (int i = start; i < n; i++){
        b[l] = a[i];
        temp_selections(a, n, k, b, l + 1, i + 1, data, process_selection);
    }
}

void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data)){
    temp_selections(a, n, k, b, 0, 0, data, process_selection);
}

void process_selection(int *b, int k, void *data)
{
    
    for (int i = 0; i < k; i++)
    {
        printf("%d", b[i]);
        if (i < k - 1)
            printf(" ");
    }
    printf("\n");  
}

// part2

/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */



void process(char *split, void *info) {
    printf("%s\n", split);
}

// void process_split(char *buf, void *data) {
//     printf("%s\n", buf);
// }

void generate_splits(const char *input, const char *dict[], int nwords, char *buf, int id, int source_index, void *data, void (*process)(char *, void *)) {
    if (input[source_index] == '\0') {
        buf[id] = '\0';
        // process_split(buf, data);
        process(buf, data);
        return;
    }


    for (int i = 0; i < nwords; i++) {
        const char *word = dict[i];
        int len = strlen(word);
        if (strncmp(input, word, len) == 0) {
            strcpy(buf, word);
            generate_splits(input + len, dict, nwords, buf + len, id + len, source_index + len, data, process);
            return;
        }
    }

    buf[id] = input[source_index];
    generate_splits(input, dict, nwords, buf + 1, id + 1, source_index + 1, data, process);
}



/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */


//part3

 void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int find_greatestless(int arr[], int start, int end, int target) {
    int index = -1;
    for (int i = start; i <= end; i++) {
        if (arr[i] < target && (index == -1 || arr[i] > arr[index])) {
            index = i;
        }
    }
    return index;
}

void reverse(int arr[], int start, int end) {
    while (start < end) {
        // swap(&arr[start], &arr[end]);
        int temp  = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void previous_permutation(int a[], int n) {
    int i = n - 2;

    while (i >= 0 && a[i] <= a[i + 1]) {
        i--;
    }

    if (i >= 0) {
        int j ;
        j = find_greatestless(a, i + 1, n - 1, a[i]);
        int temp  = a[i];
        a[i] = a[j];
        a[j] = temp;  
        // swap(&a[i], &a[j]);
        reverse(a, i + 1, n - 1);
    }
}




/* Write your tests here. Use the previous assignment for reference. */


typedef struct {
    int index;
    int err;
    int first;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_selections(int b[], int k, void *data)
{
    int *d = (int*)data;
    ++*d;
}

typedef struct {
    int b[100];
} selection_t;

void last_selection(int b[], int k, void *data)
{
    selection_t *s = (selection_t*)data;
    for (int i = 0; i < k; ++i) {
        s->b[i] = b[i];
    }
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int aa[] = { 1, 5, 3, 0, 1, 12, 4, 3, 6, 6 };
    int bb[24];
    for (int i = 0; i < 24; ++i) {
        bb[i] = i;
    }
    int b[12];
    int c = 0;

    state_t s2165 = { .index = 0, .err = 1, .first = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");

    generate_selections(aa, 10, 5, b, &c, count_selections);
    ASSERT_EQ(c, 252, "Failed on 10C5.");

    selection_t s;
    generate_selections(aa, 10, 5, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 5, "Failed on last of 10C5.", 12, 4, 3, 6, 6);

    c = 0;
    generate_selections(bb, 24, 12, b, &c, count_selections);
    ASSERT_EQ(c, 2704156, "Failed on 24C12");

    generate_selections(bb, 24, 12, b, &s, last_selection);
    ASSERT_ARRAY_VALUES_EQ(s.b, 12, "Failed on last of 24C12", 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23);
} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    if (s->first) {
        s->err = 0;
        s->first = 0;
    }
    switch (s->index) {
    case 0:
        if (strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

void count_splits(char buf[], void *data)
{
    int *c = (int *)data;
    ++(*c);
}

BEGIN_TEST(generate_splits) {
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    const char *dict_a[] = {
        "a",
        "aa",
        "aaa",
        "aaaa",
        "aaaaa",
        "aaaaaa",
        "aaaaaaa",
        "aaaaaaaa",
        "aaaaaaaaa",
        "aaaaaaaaaa"
    };
    state_t s = { .index = 0, .err = 1, .first = 1 };
    char buf[34000];
    char long_source[16000 + 1];
    for (int i = 0; i < 16000; ++i) {
        long_source[i] = 'a';
    }
    long_source[16000] = 0;
    int c;

    //generate_splits("artistoil", dict, 5, buf,0,0, &s, test_splits_art);
    //ASSERT(!s.err, "Failed on \'artistoil\'.");

    c = 0;
    generate_splits("aaaaaaaaaa", dict_a, 1, buf,0,0, &c, count_splits);
    ASSERT_EQ(c, 1, "Failed on \'aaaaaaaaaa\' with one split.");

    c = 0;
    //generate_splits("aaaaaaaaaa", dict_a, 10, buf,0,0, &c, count_splits);
    //ASSERT_EQ(c, 512, "Failed on \'aaaaaaaaaa\' with binary splits.");

    c = 0;
    generate_splits(long_source, dict_a, 1, buf,0,0, &c, count_splits);
    ASSERT_EQ(c, 1, "Failed on long source.");

    c = 0;
    //generate_splits("aaaaaaaaaa", dict_a, 2, buf,0,0, &c, count_splits);
    //ASSERT_EQ(c, 89, "Failed on Fibonacci split.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);

    int aa[] = { 1, 2, 3, 5, 4, 6 };
    previous_permutation(aa, 3); // 3 is correct.
    ASSERT_ARRAY_VALUES_EQ(aa, 3, "Failed on 1 2 3.", 1, 2, 3);

    previous_permutation(aa, 1);
    ASSERT_ARRAY_VALUES_EQ(aa, 6, "Failed on aa, 1.", 1, 2, 3, 5, 4, 6);

    int bb[] = { 1, 1, 1, 1 };
    previous_permutation(bb, 4);
    ASSERT_ARRAY_VALUES_EQ(bb, 4, "Failed on 4 1s.", 1, 1, 1, 1);

    previous_permutation(aa+3, 3);
    ASSERT_ARRAY_VALUES_EQ(aa, 6, "Failed on last part of aa.", 1, 2, 3, 4, 6, 5);
} END_TEST

int main()
{
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(generate_splits),
            TEST(previous_permutation),
            0
        });
    return 0;
}
