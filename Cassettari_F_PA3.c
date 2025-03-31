#include <stdio.h>
#include <stdlib.h>

//node
typedef struct _sampleNode {
    int ID;
    double value;
    struct _sampleNode *next; //pointer to the next node
} SampleNode;

//data set
typedef struct _dataSet {
    SampleNode *samples; //pointer to head of LL
    int nSamples;
    double minSample;
    double maxSample;
} DataSet;

int isEmpty(DataSet set) {
    if (set.nSamples == 0) { return 1;}
    else { return 0; }
}

int size(DataSet set) {
    return set.nSamples;
}

void updateMax(DataSet *set) {
    if (!set->samples) 
    { //there is no head
        set->maxSample = 0;
        return;
    }
    SampleNode *current = set->samples;
    set->maxSample = current->value;
    while (current) {
        if (current->value > set->maxSample) 
        {
            set->maxSample = current->value; 
        }
        current = current->next;
    }
}

void updateMin(DataSet *set) {
    if (!set->samples) { //if there is nothing in the dataset
        set->minSample = 0;
        return;
    }
    SampleNode *current = set->samples;
    set->minSample = current->value;
    while (current) {
        if (current->value < set->minSample)
        { 
            set->minSample = current->value; 
        }
        current = current->next;
    }
}


int addSample(DataSet *set, int SampleID, double value) {
    SampleNode *current = set->samples;
    while (current) {
        if (current->ID == SampleID) return -1; //sampleID is already present in the list
        current = current->next;
    }
    
    SampleNode *newNode = (SampleNode*) malloc(sizeof(SampleNode));
    if (!newNode) return -1;
    newNode->ID = SampleID;
    newNode->value = value;
    newNode->next = set->samples;
    set->samples = newNode;
    set->nSamples++;
    
    updateMax(set);
    updateMin(set);
    return 0;
}

SampleNode* findSample(DataSet set, int sampleID, int *location) {
    SampleNode *current = set.samples;
    int i = 0;
    while (current) {
        if (current->ID == sampleID) {
            *location = i;
            return current;
        }
        current = current->next;
        i++;
    }
    *location = -1;
    return NULL;
}


int removeSample(DataSet *set) {
    if (!set->samples) return -1;//base case, the samples don't exist
    SampleNode *temp = set->samples;
    set->samples = temp->next;
    free(temp);
    set->nSamples--;
    updateMax(set);
    updateMin(set);
    return 0;
}

void deleteSet(DataSet *set) {
    SampleNode *current = set->samples;
    while (current) {
        SampleNode *temp = current;
        current = current->next;
        free(temp);
    }
    set->samples = NULL;
    set->minSample = 0;
    set->maxSample = 0;
    set->nSamples = 0;
    
}

void printSamples(DataSet *set) {
    SampleNode *current = set->samples;
    while (current) {
        printf("Address: %p, ID: %d, Value: %f\n", (void*)current, current->ID, current->value);
        current = current->next;
    }
}

int main() {
    return 0;
}
