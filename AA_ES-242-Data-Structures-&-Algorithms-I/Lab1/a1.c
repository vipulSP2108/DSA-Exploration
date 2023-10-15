#include "test.h"
#include <string.h> // for testing generate_splits()

void printArray(int a[], int n) {
}

/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
// ----------------------------------------------------------PART 1(NIDHI)------------------------------------------------- 

//part1

void generate_selections(int a[], int n, int k, int l, int i, int b[], void *data, void (*process_selection)(int *b, int k, void *data)) {
  if (l == k) {
    if (process_selection != NULL) {
      process_selection(b, k, data);
    }
    return;
  }

  if (i < n) {
    b[l] = a[i];
    generate_selections(a, n, k, l + 1, i + 1, b, data, process_selection);
    generate_selections(a, n, k, l, i + 1, b, data, process_selection);
  }
}


//part2

void process_selection(int *b, int k, void *data) {
    printArray(b, k);
}

void process_split(char *buf, void *data) {
    printf("%s\n", buf);
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char *buf, int index, int source_index, void *data, void (*process_split)(char *buf, void *data)) {
  if (source[source_index] == '\0') {
    buf[index] = '\0';
    process_split(buf, data);
    return;
  }

  for (int i = 0; i < nwords; i++) {
    const char *word = dictionary[i];
    int word_length = strlen(word);

    if (strncmp(source, word, word_length) == 0) {
      strcpy(buf, word);
      generate_splits(source + word_length, dictionary, nwords, buf + word_length, index + word_length, source_index + word_length, data, process_split);
    }
  }

  buf[index] = source[source_index];
  generate_splits(source, dictionary, nwords, buf + 1, index + 1, source_index + 1, data, process_split);
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

int findLargestSmaller(int arr[], int start, int end, int target) {
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
        swap(&arr[start], &arr[end]);
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
        int j = findLargestSmaller(a, i + 1, n - 1, a[i]);

        swap(&a[i], &a[j]);
        reverse(a, i + 1, n - 1);
    }
}



// -------------------------------------------------------------------------------------------------------------------------------------------------
/* Write your tests here. Use the previous assignment for reference. */


typedef struct {
    int index;
    int err;
} state_t;


static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    s->err = 0;
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

BEGIN_TEST(generate_selections) {
    // TEST 1
    int a[] = { 2, 1, 6, 5 };
    int b[2];
    state_t s2165 = { .index = 0, .err = 1 };
    generate_selections(a, 4, 2, 0, 0, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");




} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    s->err = 0;
    switch (s->index) {
    case 0:
        if (!strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (!strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
}

BEGIN_TEST(generate_splits) {
    //TEST 1
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    state_t s = { .index = 0, .err = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf,0,0, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    //TEST 1
    int a[] = { 1, 6, 5, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 6, 4, 5, 3, 2);
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
