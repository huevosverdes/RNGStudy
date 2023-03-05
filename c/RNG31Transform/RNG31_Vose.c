#include "RNG31_Vose.h"

typedef struct {
    int *buffer;
    int capacity;
    int count;
    int offset;
} RNG31_VoseQueue;
void rng31Vose_queue_init(RNG31_VoseQueue *queue, int capacity);
void rng31Vose_queue_release(RNG31_VoseQueue *queue);
void rng31Vose_queue_enqueue(RNG31_VoseQueue *queue, int value);
int rng31Vose_queue_dequeue(RNG31_VoseQueue *queue);

void rng31Vose_init(RNG31_Vose *vrng, AbstractRNG31Core *rng, const double *itemWeights, int itemCount)
{
    rng31Uniform_init(&(vrng->urng), rng);
    vrng->itemCount = itemCount;
    vrng->probabilities = (double*)malloc(itemCount * sizeof(double));
    vrng->aliases = (int*)malloc(itemCount * sizeof(int));

    double *itemProbabilities = (double*)malloc(sizeof(double) * itemCount);

    double sum = 0.0;
    for(int index = 0; index < itemCount; ++index)
        sum += itemWeights[index];
    for(int index = 0; index < itemCount; ++index)
        itemProbabilities[index] = (itemCount * itemWeights[index] / sum);

    int queueCapacity = itemCount * 2;
    RNG31_VoseQueue small, large;
    rng31Vose_queue_init(&small, queueCapacity);
    rng31Vose_queue_init(&large, queueCapacity);

    for(int index = 0; index < itemCount; ++index)
        if(itemProbabilities[index] < 1.0)
            rng31Vose_queue_enqueue(&small, index);
        else
            rng31Vose_queue_enqueue(&large, index);

    while(small.count > 0 && large.count > 0)
    {
        int less = rng31Vose_queue_dequeue(&small);
        int more = rng31Vose_queue_dequeue(&large);

        vrng->probabilities[less] = itemProbabilities[less];
        vrng->aliases[less] = more;

        itemProbabilities[more] += itemProbabilities[less] - 1.0;
        if(itemProbabilities[more] < 1.0)
            rng31Vose_queue_enqueue(&small, more);
        else
            rng31Vose_queue_enqueue(&large, more);
    }

    while(large.count > 0)
        vrng->probabilities[rng31Vose_queue_dequeue(&large)] = 1.0;
    while(small.count > 0)
        vrng->probabilities[rng31Vose_queue_dequeue(&small)] = 1.0;
    rng31Vose_queue_release(&small);
    rng31Vose_queue_release(&large);

    free(itemProbabilities);
}

void rng31Vose_release(RNG31_Vose *vrng)
{
    free(vrng->probabilities);
    free(vrng->aliases);

    vrng->itemCount = 0;
    vrng->probabilities = NULL;
    vrng->aliases = NULL;
}

int32_t rng31Vose_next(RNG31_Vose *vrng)
{
    int index = rng31Uniform_next(&(vrng->urng), 0, vrng->itemCount);
    if(rng31Uniform_nextFloat(&(vrng->urng), 0.0, 1.0) >= vrng->probabilities[index])
        index = vrng->aliases[index];
    return index;
}

/* Not exposed in header */
void rng31Vose_queue_init(RNG31_VoseQueue *queue, int capacity)
{
    queue->buffer = (int*)malloc(sizeof(int) * capacity);
    queue->count = 0;
    queue->offset = 0;
    queue->capacity = capacity;
}

void rng31Vose_queue_release(RNG31_VoseQueue *queue)
{
    free(queue->buffer);
    queue->buffer = NULL;
    queue->capacity = 0;
    queue->offset = 0;
    queue->count = 0;
}

void rng31Vose_queue_enqueue(RNG31_VoseQueue *queue, int value)
{
    assert(queue->count < queue->capacity);
    queue->buffer[(queue->offset + queue->count++) % queue->capacity] = value;
}

int rng31Vose_queue_dequeue(RNG31_VoseQueue *queue)
{
    assert(queue->count > 0);
    int result = queue->buffer[queue->offset];
    if(--(queue->count) == 0)
        queue->offset = 0;
    else
        queue->offset = (queue->offset + 1) % queue->capacity;
    return result;
}
