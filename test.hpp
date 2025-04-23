

class a 
{
public:
    a(){}
    ~a(){}

    int met1(int p1, float p2);
    virtual int met2(char ch);

    int m_1;

protected:
    virtual int met3(double db) { return 1;};
    virtual void met4(int p1, int p2) = 0;

    int m_2;

private:
    double m_3;
};


class b : public a
{
public:
    b(){m_1 = 5; m_2 = met3(3.14); }
    ~b(){}

    int met3(double db) override
    {
        return 5;
    }

    void met4(int p1, int p2) override
    {
        m_2 = p1 + p2;
    }
};

class c
{
    c(){ a* pa= new b()}
};


// definit in fisierul I_Mine.h
class I_Mine
{
public:
    virtual void met1() = 0;
    virtual void met2() = 0;
    virtual void met3() = 0;
    virtual void met4() = 0;
    virtual ~I_Mine(){};
};


// definit in fisierul MyImplementation.h
class MyImplementation : public I_Mine
{
public:
    void met1() override { /* Implement met1 */ }
    void met2() override { /* Implement met2 */ }
    void met3() override { /* Implement met3 */ }
    void met4() override { /* Implement met4 */ }
};


// intr-un header al tau, numit de ex MyThread.h
#include <thread>
class MyThreadBase : public std::thread
{
public:
    MyThread() : std::thread(&MyThread::run, this) { m_Exit = false; }
    ~MyThread() { join(); } // Wait for the thread to finish

    virtual bool OnFrameUpdate(float dt) = 0; // Pure virtual function

private:

    void run()
    {
        // Thread code goes here
        while (!m_Exit)
        {
            // Do something
            m_Exit = OnFrameUpdate(0.016f); // Call the pure virtual function

            // call your sleep for a fixed time step
            mySleep(0.016f); // Sleep for 16ms (60 FPS)
        }
    }

    void mySleep(float seconds)
    {
        #if defined(Win32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
            Sleep(seconds * 1000); // Sleep for the specified number of seconds
        #else
            std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
        #endif
    }

    bool m_Exit;
};

// in header-ul clasei GamePanel.h
#include "MyThread.h"
//....
class MyThread : public MyThread
{
// definitiile tale raman neschimbate
public:
    std::thread* GetThreadObject() {return this; } // Return the thread object

// adaugi implementarea metodei OnFrameUpdate
    bool OnFrameUpdate(float dt) override
    {
        // Implement your frame update logic here
        return false; // Return true to exit the thread, false to continue
    }
};

}    
