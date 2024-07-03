#ifndef SHARED_PTR
#define SHARED_PTR

#include <map>
template<typename T>
class SharedPtr{
public:
    SharedPtr(): _p(nullptr){
    }

    SharedPtr(T* _p): _p(_p){
        if(_p){
            Map[_p] = 1;
        }
    }

    ~SharedPtr(){
        if(_p){
            Map[_p] = Map[_p]-1;
            if(Map[_p] == 0){
                Map.erase(_p);
                delete _p;
                _p = nullptr; //这里需要赋值空指针，否则test15会fail
            }
        }
    }

    SharedPtr(SharedPtr& other): _p(other._p){
        if(_p){
            Map[_p] = Map[_p]+1;
        }
    }

    SharedPtr& operator=(const SharedPtr& other){
        if(this == &other)  
            return *this;
        if(_p){
            Map[_p] = Map[_p]-1;
            if(Map[_p] == 0){
                Map.erase(_p);
                delete _p;
            }
        }
        _p = other._p;
        Map[_p] = Map[_p]+1;
        return *this;
    }

    SharedPtr(SharedPtr&& other): _p{other._p}{
        other._p = nullptr;
    }
    SharedPtr& operator=(SharedPtr&& other){
        if(this == &other)   return *this;
        if(_p){
            Map[_p] = Map[_p]-1;
            if(Map[_p]==0){
                Map.erase(_p);
                delete _p;
            }
        }
        _p = other._p;
        other._p = nullptr;
    }

    T* get(){
        return _p;
    }

    int use_count(){
        if(_p)
            return Map[_p];
        else{
            return 0;
        }
    }

    T operator*(){
        return *_p;
    }

    T* operator->(){
        return _p;
    }

    void reset(){
        if(_p){
            Map[_p] = Map[_p]-1;
            if(Map[_p]==0){
                Map.erase(_p);
                delete _p;
            }
        }
        // 指针_p在delete后，指针的值还在，所以要赋值为nullptr.
        _p = nullptr;
    }

    void reset(T* other_p){
        if(_p == other_p) return;
        reset();
        _p = other_p;
        if(_p){
            Map[_p] = 1 + Map[_p];
        }
    }

    operator bool(){
        return _p != nullptr;
    }

private:
    T* _p;
    static std::map<T*,int> Map;
};

template<typename T>
std::map<T*, int> SharedPtr<T>::Map{};

template<typename T>
SharedPtr<T> make_shared(T t){
    return SharedPtr<T>(new T(t));
}

#endif //SHARED_PTR