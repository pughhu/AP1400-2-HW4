#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template<typename T>
class UniquePtr{
public:
    UniquePtr(T* _p):_p(_p){

    }

    UniquePtr():_p(nullptr){

    }

    ~UniquePtr(){
        delete _p;
        _p = nullptr;
    }

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept: _p(other._p){
        other._p = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept{
        delete _p;
        _p = other._p;
        other._p = nullptr;
        return *this;
    }

    T* get(){
        return _p;
    }

    T operator*(){
        return *_p;
    }

    T* operator->(){
        return _p;
    }

    void reset(){
        delete _p;
        _p = nullptr;
    }

    void reset(T* new_p){
        if(_p == new_p) return;
        delete _p;
        _p = new_p;
    }

    T* release(){
        auto tmp = _p;
        _p = nullptr;
        return tmp;
    }

    operator bool()const{
        return (_p != nullptr);
    }

private:
    T* _p;
};

template<typename T>
UniquePtr<T> make_unique(T t){
    return UniquePtr<T>(new T(t));
}

#endif //UNIQUE_PTR