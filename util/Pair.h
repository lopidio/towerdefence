#ifndef PAIR_H
#define PAIR_H

namespace util
{
        template<typename t1, typename t2>
        class Pair
        {

                public:

                        Pair(const t1& first_, const t2& second_):first(first_), second(second_){}
                        bool operator==(const Pair& rhs)
                        {
                                return (first == rhs.first && second == rhs.second);
                        }
                private:
                        t1 first;
                        t2 second;

                public:
                        struct LessComparator
                        {
                                bool operator()(const Pair& lhs, const Pair& rhs)
                                {
                                        if (lhs.first == rhs.first)
                                                return lhs.second < rhs.second;
                                        return lhs.first < rhs.first;
                                }
                        };


        };
}

#endif // PAIR_H

