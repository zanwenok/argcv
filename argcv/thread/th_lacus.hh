#ifndef ARGCV_THREAD_TH_LACUS_HH
#define ARGCV_THREAD_TH_LACUS_HH

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <pthread.h>
#include <unistd.h>

namespace argcv {
namespace thread {

enum class THREAD_STATUS : unsigned char {
    THREAD_READY,
    THREAD_DATA_PREPARE,
    THREAD_DATA_PROCESS,
    THREAD_CLOSE
};

template <typename T>
class thread_lacus {
public:
    typedef void (*data_process)(T*);

private:
    class thread_lacus_node {
    public:
        T* _data;
        THREAD_STATUS status;
        int64_t clue;
        size_t _id;
        thread_lacus* _env;
    };

    void back(int64_t idx) {
        pthread_mutex_lock(&_m);
        nodes[idx].clue = clue;
        clue = idx;
        nodes[idx].status = THREAD_STATUS::THREAD_READY;
        sz_in_use--;
        pthread_mutex_unlock(&_m);
    }

    int64_t alloc() {
        pthread_mutex_lock(&_m);
        int rt = clue;
        if (clue != -1) {
            sz_in_use++;
            clue = nodes[clue].clue;
            nodes[rt].status = THREAD_STATUS::THREAD_DATA_PREPARE;
        }
        pthread_mutex_unlock(&_m);
        return rt;
    }

    static void* thread_handler(void* _cnode) {
        thread_lacus_node* _v = (thread_lacus_node*)_cnode;
        size_t us_cur_sleep = _v->_env->us_min_sleep;
        for (;;) {
            while (_v->status != THREAD_STATUS::THREAD_DATA_PROCESS) {
                if (_v->status == THREAD_STATUS::THREAD_CLOSE) {
                    return NULL;
                }
                us_cur_sleep *= 2;
                if (us_cur_sleep > _v->_env->us_max_sleep) us_cur_sleep = _v->_env->us_max_sleep;
                usleep(us_cur_sleep);
            }
            _v->_env->_d_proc(_v->_data);
            //_v->status = THREAD_STATUS::THREAD_COMPLETED;
            us_cur_sleep = _v->_env->us_min_sleep;
            _v->_env->back(_v->_id);
        }
    }

public:
    thread_lacus(data_process _d_proc, size_t sz = 3, size_t us_min_sleep = 100, size_t us_max_sleep = 300000)
        : _d_proc(_d_proc), sz_lacus(sz), us_min_sleep(us_min_sleep), us_max_sleep(us_max_sleep) {
        pthread_mutex_init(&_m, NULL);
        nodes = new thread_lacus_node[sz];
        _pt = new pthread_t[sz_lacus];
        for (size_t i = 0; i < sz; i++) {
            nodes[i].status = THREAD_STATUS::THREAD_READY;
            nodes[i].clue = (int64_t)i + 1;
            nodes[i]._id = i;
            nodes[i]._env = this;
            int ret = pthread_create(&(_pt[i]), NULL, thread_handler, &(nodes[i]));
            if (ret != 0) {
                // fprintf(stderr, "crate thread  %d failed .. \n", i);
                _e_no = -1;
            }
        }
        nodes[sz - 1].clue = -1;
        sz_in_use = 0;
        clue = 0;
        _e_no = 0;
    }
    ~thread_lacus() {
        for (int i = 0; i < sz_lacus; i++) {
            nodes[i].status = THREAD_STATUS::THREAD_CLOSE;
        }
        for (size_t i = 0; i < sz_lacus; i++) {
            pthread_join(_pt[i], NULL);
        }
        delete[] nodes;
        delete[] _pt;
    }

    // template <typename T>
    int try_enqueue(T* _d) {
        int64_t idx = alloc();
        if (idx != -1) {
            nodes[idx]._data = _d;
            nodes[idx].status = THREAD_STATUS::THREAD_DATA_PROCESS;
            return 0;
        } else {
            return -1;
        }
    }

    int enqueue(T* _d) {
        while (try_enqueue(_d) == -1) {
            usleep(us_max_sleep);
        }
        return 0;
    }

    int error_no() { return _e_no; }

    void join() {
        while (sz_in_use > 0) {
            usleep(us_max_sleep);
        }
    }

private:
    data_process _d_proc;
    size_t sz_lacus;
    size_t us_min_sleep;
    size_t us_max_sleep;
    pthread_mutex_t _m;
    size_t sz_in_use;
    int64_t clue;
    thread_lacus_node* nodes;
    pthread_t* _pt;
    int _e_no;
};
}
}  // argcv::thread

#endif  //  ARGCV_THREAD_TH_LACUS_HH
