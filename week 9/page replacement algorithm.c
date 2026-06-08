#include <stdio.h>
#include <stdlib.h>

int findOptimal(int pages[], int n, int frame[], int frameCount, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; // Not found in future
    }
    return (pos == -1) ? 0 : pos;
}

int findLRU(int time[], int frameCount) {
    int min = time[0], pos = 0;
    for (int i = 1; i < frameCount; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void FIFO(int pages[], int n, int frameCount) {
    int frame[frameCount], count = 0, faults = 0;
    for (int i = 0; i < frameCount; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frame[j] == pages[i]) { found = 1; break; }
        }
        if (!found) {
            frame[count] = pages[i];
            count = (count + 1) % frameCount;
            faults++;
        }
    }
    printf("FIFO Page Faults: %d\n", faults);
}

void LRU(int pages[], int n, int frameCount) {
    int frame[frameCount], time[frameCount], faults = 0, counter = 0;
    for (int i = 0; i < frameCount; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }
        if (!found) {
            int pos = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frame[j] == -1) { pos = j; break; }
            }
            if (pos == -1) pos = findLRU(time, frameCount);
            frame[pos] = pages[i];
            counter++;
            time[pos] = counter;
            faults++;
        }
    }
    printf("LRU Page Faults: %d\n", faults);
}

void Optimal(int pages[], int n, int frameCount) {
    int frame[frameCount], faults = 0;
    for (int i = 0; i < frameCount; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameCount; j++) {
            if (frame[j] == pages[i]) { found = 1; break; }
        }
        if (!found) {
            int pos = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frame[j] == -1) { pos = j; break; }
            }
            if (pos == -1) pos = findOptimal(pages, n, frame, frameCount, i+1);
            frame[pos] = pages[i];
            faults++;
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int n, frameCount;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    FIFO(pages, n, frameCount);
    LRU(pages, n, frameCount);
    Optimal(pages, n, frameCount);

    return 0;
}
