#include <iostream>
#include <vector>

template <typename T>
class SubSeq
{
public:
    class Index
    {
    public:
        Index(size_t seq_size, size_t subseq_size) : ss(seq_size), s(subseq_size), data()
        {
            data.reserve(s + 1);
            for (size_t i = 0; i < s; ++i)
                data.push_back(i);
            data.push_back(ss);
        }
        bool next() { return next(s-1); }
        bool next(size_t i) {
            data[i]++;
            for (size_t j = i + 1; j < s; ++j) data[j] = data[j - 1] + 1;
            if (data[s - 1] >= data[s]) {
                if (i > 0) return next(i-1);
                else       return false;
            } else {
                return true;
            }
        }
        size_t operator[] (size_t i) { return data[i]; }
    private:
        size_t              ss, s;
        std::vector<size_t> data;
    };

    SubSeq(const std::vector<T>& data, size_t subseq_size)
            : seq_size(data.size()), subseq_size(subseq_size),
              data(data), index(data.size(), subseq_size),
              ended(subseq_size > data.size() || subseq_size == 0)
    {}
    std::vector<T> next() {
        std::vector<T> v;
        v.reserve(subseq_size);
        for (size_t i = 0; i < subseq_size; ++i)
            v.push_back(data[index[i]]);
        ended = !index.next();
        return v;
    }
    bool end() { return ended; }
    void start() {
        index = Index(seq_size, subseq_size);
        ended = subseq_size > seq_size || subseq_size == 0;
    }

private:
    size_t seq_size, subseq_size;
    std::vector<T> data;
    Index  index;
    bool   ended;
};

template <typename T>
std::vector<std::vector <T>> getSubsets(std::vector<T>& v, size_t k){
    SubSeq<T> ss(v, k);
    std::vector<std::vector <T>> subsets;
    while (! ss.end()) {
        std::vector<T> s = ss.next();
        subsets.push_back(s);
    }
    return subsets;
}
//пример использования функции
/*int main(){
    const int k = 3;
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<std::vector<int>> subsets(10);
    subsets = getSubsets(v, k);

    for(int i = 0; i < subsets.size(); ++i){
        for(int j = 0; j < k; j++)
            std::cout << subsets.at(i).at(j) << " ";
        std::cout << "\n";
    }
    std::cout << subsets.size() << std::endl;
    return 0;
}*/
