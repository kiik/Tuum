#include <ctime>
#include "SmackTalk.hpp"

using namespace std;

int main(){
  printf("Soundtest\n");
  tuum::Smacktalk::init();

  bool running = true;
  while(running) {
    usleep(1000000);
    printf("Calling goalHit!");
    clock_t begin = clock();
    tuum::Smacktalk::goalHit();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f\n\n\n", elapsed_secs);
  }

  return 0;
}
