#include "Vose.h"

using namespace RNG31;

Vose::Vose(AbstractRNGCore *rng, const double *itemWeights, int itemCount) :
    m_urng(rng)
{
    m_itemCount = itemCount;
    m_probabilities = new double[itemCount];
    m_aliases = new int[itemCount];

    double itemProbabilities[itemCount];
    double sum = 0.0;
    for(int index = 0; index < m_itemCount; ++index)
        sum += itemWeights[index];

    for(int index = 0; index < m_itemCount; ++index)
        itemProbabilities[index] = (m_itemCount * itemWeights[index] / sum);

    std::queue<int> small;
    std::queue<int> large;
    for(int index = 0; index < m_itemCount; ++index)
        if(itemProbabilities[index] < 1.0)
            small.emplace(index);
        else
            large.emplace(index);

    for(uint32_t index = 0; index < small.size(); ++index) {
        small.emplace(small.front());
        small.pop();
    }
    for(uint32_t index = 0; index < large.size(); ++index) {
        large.emplace(large.front());
        large.pop();
    }

    while((!small.empty()) && (!large.empty())) {
        int less = small.front(); small.pop();
        int more = large.front(); large.pop();

        m_probabilities[less] = itemProbabilities[less];
        m_aliases[less] = more;

        // Compute remainder of large
        itemProbabilities[more] += itemProbabilities[less] - 1.0;
        if(itemProbabilities[more] < 1.0)
            small.emplace(more);
        else
            large.emplace(more);
    }

    for(uint32_t index = 0; index < small.size(); ++index) {
        small.emplace(small.front());
        small.pop();
    }
    for(uint32_t index = 0; index < large.size(); ++index) {
        large.emplace(large.front());
        large.pop();
    }

    while(!large.empty()) {
        m_probabilities[large.front()] = 1.0;
        large.pop();
    }
    while(!small.empty())
    {
        m_probabilities[small.front()] = 1.0;
        small.pop();
    }
}

Vose::~Vose()
{
    delete[] m_probabilities;
    m_probabilities = nullptr;

    delete[] m_aliases;
    m_aliases = nullptr;

    m_itemCount = 0;
}

int Vose::next()
{
    int index = m_urng.next(m_itemCount);
    if(m_urng.nextFloat() >= m_probabilities[index])
        index = m_aliases[index];
    return index;
}
