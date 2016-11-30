//
// Created by WT on 2016/11/24.
//

#ifndef _WT_UNION_FIND_HPP_
#define _WT_UNION_FIND_HPP_

namespace wt {

class union_find {
public:
    union_find(int n);

    void    connect(int id1, int id2);
    int     find(int id);
    int     size() const;           //  connected components number
    int     size(int id) const;     //  elements in current connected component
    bool    is_connected(int id1, int id2);

private:
    int                 count_;
    wt::vector<int>     id_;
    wt::vector<int>     size_;
};

union_find::union_find(int n)
: count_(n), id_(n), size_(n, 1)
{
    for(int i = 0; i < n; ++i)
        id_[i] = i;
}

void union_find::connect(int id1, int id2)
{
    int owner1 = this->find(id1);
    int owner2 = this->find(id2);
    if(owner1 != owner2)
    {
        if(size_[owner1] < size_[owner2])
        {
            id_[owner1] = owner2;
            size_[owner2] += size_[owner1];
        }
        else
        {
            id_[owner2] = owner1;
            size_[owner1] += size_[owner2];
        }
        --count_;
    }
}

int union_find::find(int id)
{
    while(id != id_[id])
        id = id_[id];
    return id;
}

int union_find::size() const
{
    return count_;
}

int union_find::size(int id) const
{
    while(id != id_[id])
        id = id_[id];
    return size_[id];
}

bool union_find::is_connected(int id1, int id2)
{
    return this->find(id1) == this->find(id2);
}

} // namespace wt

#endif //TEST_WT_UNION_FIND_HPP
