#include <iterator>

template <typename T>
concept IsContainer = requires(T container) {
    container.begin();
    container.end();
    requires std::derived_from<typename T::const_iterator::iterator_category, std::forward_iterator_tag>;
};

struct KeysViewParam {};
struct ValuesViewParam {};
struct ReverseViewParam {};

template<typename FunctionType>
struct TransformViewParam {
    TransformViewParam(FunctionType function): function(function) {}
    FunctionType function;
};

template<typename ConditionType>
struct FilterViewParam {
    FilterViewParam(ConditionType function): condition(function) {}
    ConditionType condition;
};

struct TakeViewParam {
    TakeViewParam(size_t n): n(n) {}
    size_t n;
};

struct DropViewParam {
    DropViewParam(size_t n): n(n) {}
    size_t n;
};



template <typename AssociativeContainer>
class KeysView {
public:
    static_assert(IsContainer<AssociativeContainer>);

    explicit KeysView(AssociativeContainer& container): container_(container) {}

    class iterator {
    public:
        using iterator_category = AssociativeContainer::const_iterator::iterator_category;

        explicit iterator(AssociativeContainer::const_iterator it): iterator_(it) {}

        auto operator*() const {
            return (*iterator_).first;
        }

        iterator& operator++() {
            ++iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        AssociativeContainer::const_iterator iterator_;
    };

    iterator begin() const {
        return iterator(container_.begin());
    }

    iterator end() const {
        return iterator(container_.end());
    }

private:
    AssociativeContainer& container_;

public:
    using const_iterator = iterator;
};

template <typename AssociativeContainer>
KeysView<AssociativeContainer> keys(AssociativeContainer& container) {
    return KeysView<AssociativeContainer>(container);
}

KeysViewParam keys() {
    return {};
}

template <typename Container>
auto operator|(Container&& container, KeysViewParam keys_view_param) {
    return KeysView<std::remove_reference_t<Container>>(container);
}



template <typename AssociativeContainer>
class ValueView {
public:
    static_assert(IsContainer<AssociativeContainer>);

    explicit ValueView(AssociativeContainer& container): container_(container) {    }

    class iterator {
    public:
        using iterator_category = AssociativeContainer::const_iterator::iterator_category;

        explicit iterator(AssociativeContainer::const_iterator it): iterator_(it) {}

        auto operator*() const {
            return (*iterator_).second;
        }

        iterator& operator++() {
            ++iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        AssociativeContainer::const_iterator iterator_;
    };

    iterator begin() const {
        return iterator(container_.begin());
    }

    iterator end() const {
        return iterator(container_.end());
    }

private:
    AssociativeContainer& container_;

public:
    using const_iterator = iterator;
};

template <typename AssociativeContainer>
ValueView<AssociativeContainer> values(AssociativeContainer& container) {
    return ValueView<AssociativeContainer>(container);
}

ValuesViewParam values() {
    return {};
}

template <typename Container>
auto operator|(Container&& container, ValuesViewParam keys_view_param) {
    return ValueView<std::remove_reference_t<Container>>(container);
}



template <typename Container>
class TakeView {
public:
    static_assert(IsContainer<Container>);

    explicit TakeView(Container& container, size_t to_take_n): container_(container), to_take_n_(to_take_n) {}

    class iterator {
    public:
        using iterator_category = Container::const_iterator::iterator_category;

        explicit iterator(Container::const_iterator it, size_t to_take_n, Container::const_iterator begin_iterator,
                          Container::const_iterator end_iterator):
                            iterator_(it), end_iterator_(end_iterator)  {
            typename Container::const_iterator new_end = begin_iterator;
            for (size_t i = 0; i < to_take_n; ++i) {
                if (new_end == end_iterator) {
                    break;
                }
                ++new_end;
            }

            if (it == end_iterator) {
                iterator_ = new_end;
            }
            end_iterator_ = new_end;

            if (to_take_n == 0) {
                iterator_ = end_iterator_;
            }
        }

        auto operator*() const {
            return *iterator_;
        }

        iterator& operator++() {
            ++iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Container::const_iterator iterator_;
        Container::const_iterator end_iterator_;
    };

    iterator begin() const {
        return iterator(container_.begin(), to_take_n_, container_.begin(), container_.end());
    }

    iterator end() const {
        return iterator(container_.end(), to_take_n_, container_.begin(), container_.end());
    }

private:
    Container& container_;
    const size_t to_take_n_;

public:
    using const_iterator = iterator;
};

template <typename Container>
TakeView<Container> take(Container& container, size_t to_take_n) {
    return TakeView<Container>(container, to_take_n);
}

TakeViewParam take(size_t n) {
    return {n};
}

template<typename Container>
auto operator|(Container&& container, TakeViewParam take_view_param) {
    return TakeView<std::remove_reference_t<Container>>(container, take_view_param.n);
}




template <typename Container>
class DropView {
public:
    static_assert(IsContainer<Container>);

    explicit DropView(Container& container, size_t n): container_(container), to_drop_n_(n) {}

    class iterator {
    public:
        using iterator_category = Container::const_iterator::iterator_category;

        explicit iterator(Container::const_iterator it, size_t to_drop_n, Container::const_iterator end_iterator):
                            iterator_(it) {
            for (size_t i = 0; i < to_drop_n; ++i) {
                if (iterator_ == end_iterator) {
                    break;
                }
                ++iterator_;
            }
        }

        auto operator*() const {
            return *iterator_;
        }

        iterator& operator++() {
            ++iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }


        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Container::const_iterator iterator_;
    };

    iterator begin() const {
        return iterator(container_.begin(), to_drop_n_, container_.end());
    }

    iterator end() const {
        return iterator(container_.end(), to_drop_n_, container_.end());
    }

private:
    Container& container_;
    const size_t to_drop_n_;

public:
    using const_iterator = iterator;
};

template <typename Container>
DropView<Container> drop(Container& container, size_t to_drop_n) {
    return DropView<Container>(container, to_drop_n);
}

DropViewParam drop(size_t n) {
    return {n};
}

template<typename Container>
auto operator|(Container&& container, DropViewParam take_view_param) {
    return DropView<std::remove_reference_t<Container>>(container, take_view_param.n);
}



template <typename Container, typename Condition>
class FilterView {
public:
    static_assert(IsContainer<Container>);

    explicit FilterView(Container& container, Condition condition): container_(container), condition_(condition) {}

    class iterator {
    public:
        using iterator_category = Container::const_iterator::iterator_category;

        explicit iterator(Container::const_iterator it, Condition condition, Container::const_iterator end_iterator):
                iterator_(it), condition_(condition), end_iterator_(end_iterator) {}

        auto operator*() const {
            return *iterator_;
        }

        iterator& operator++() {
            do {
                ++iterator_;
            }
            while ((iterator_ != end_iterator_) && (!condition_(*iterator_)));

            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            do {
                --iterator_;
            }
            while ((iterator_ != end_iterator_) && (!condition_(*iterator_)));

            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Container::const_iterator iterator_;
        Container::const_iterator end_iterator_;
        Condition condition_;
    };

    iterator begin() const {
        auto iterator_ = container_.begin();
        while ((iterator_ != container_.end()) && (!condition_(*iterator_))) {
            ++iterator_;
        }
        return iterator(iterator_, condition_, container_.end());
    }

    iterator end() const {
        return iterator(container_.end(), condition_, container_.end());
    }

private:
    Container& container_;
    Condition condition_;

public:
    using const_iterator = iterator;
};

template <typename Container, typename Condition>
FilterView<Container, Condition> filter(Container& container, Condition condition) {
    return FilterView<Container, Condition>(container, condition);
}

template <typename FunctionType>
FilterViewParam<FunctionType> filter(FunctionType function) {
    return {function};
}

template<typename Container, typename FunctionType>
auto operator|(Container&& container, FilterViewParam<FunctionType> take_view_param) {
    return FilterView<std::remove_reference_t<Container>, FunctionType>(container, take_view_param.condition);
}


template <typename Container, typename Transform>
class TransformView {
public:
    static_assert(IsContainer<Container>);

    explicit TransformView(Container& container, Transform transform): container_(container), transform_(transform) {}

    class iterator {
    public:
        using iterator_category = Container::const_iterator::iterator_category;

        explicit iterator(Container::const_iterator it, Transform transform): iterator_(it), transform_(transform) {}

        auto operator*() const {
            return transform_(*iterator_);
        }

        iterator& operator++() {
            ++iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Container::const_iterator iterator_;
        Transform transform_;
    };

    iterator begin() const {
        return iterator(container_.begin(), transform_);
    }

    iterator end() const {
        return iterator(container_.end(), transform_);
    }

private:
    Container& container_;
    Transform transform_;

public:
    using const_iterator = iterator;

};

template <typename Container, typename Transform>
TransformView<Container, Transform> transform(Container& container, Transform transform) {
    return TransformView<Container, Transform>(container, transform);
}

template <typename FunctionType>
TransformViewParam<FunctionType> transform(FunctionType function) {
    return {function};
}

template<typename Container, typename FunctionType>
auto operator|(Container&& container, TransformViewParam<FunctionType> take_view_param) {
    return TransformView<std::remove_reference_t<Container>, FunctionType>(container, take_view_param.function);
}



template <typename Container>
class ReverseView {
public:
    static_assert(IsContainer<Container>);
    static_assert(std::derived_from<typename Container::const_iterator::iterator_category, std::bidirectional_iterator_tag>);

    explicit ReverseView(Container& container): container_(container) {}

    class iterator {
    public:
        using iterator_category = Container::const_iterator::iterator_category;

        explicit iterator(Container::const_iterator it, Container::const_iterator begin_it, Container::const_iterator end_it):
                        iterator_(it), begin_iterator_(begin_it), end_iterator_(end_it) {}

        auto operator*() const {
            auto temp = iterator_;
            --temp;
            return *temp;
        }

        iterator& operator++() {
            --iterator_;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            ++iterator_;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return iterator_ == other.iterator_;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

    private:
        Container::const_iterator iterator_;
        Container::const_iterator begin_iterator_;
        Container::const_iterator end_iterator_;
    };

    iterator begin() const {
        return iterator(container_.end(), container_.begin(), container_.end());
    }

    iterator end() const {
        return iterator(container_.begin(), container_.begin(), container_.end());
    }

private:
    Container& container_;

public:
    using const_iterator = iterator;
};

template <typename Container>
ReverseView<Container> reverse(Container& container) {
    return ReverseView<Container>(container);
}

ReverseViewParam reverse() {
    return {};
}

template <typename Container>
auto operator|(Container&& container, ReverseViewParam keys_view_param) {
    return ReverseView<std::remove_reference_t<Container>>(container);
}




