#include <iostream>

using namespace std;

#define PORTAUDIO 100

int main(int argc, char *argv[])
{
#ifdef PORTAUDIO
    std::cout << "hello" << std::endl;
    // 停止编译
// #error "No audio input provided"
#else
    // #error "No audio input provided"
    std::cout << "else" << std::endl;
#endif

    std::cout << "return" << std::endl;
    std::cout << PORTAUDIO << std::endl;
    return 0;
}