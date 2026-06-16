#include"ffthread.h"


FFThread::FFThread()
    :m_stop(true)
{

}

FFThread::~FFThread()
{
    if(m_thread.joinable()){
        m_thread.join();
    }
}

void FFThread::stop()
{
    m_stop = true;
}

void FFThread::wait()
{
    if(m_thread.joinable()){
        m_thread.join();
        std::cerr<<"thread id:"<<std::this_thread::get_id()<<" join!"<<std::endl;
    }
}

void FFThread::start()
{
    m_stop = false;
    if(!m_stop){
        m_thread = std::thread(&FFThread::run, this);
    }
}

