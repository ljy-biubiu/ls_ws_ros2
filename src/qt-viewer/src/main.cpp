#include "maindeal.h"

int main(int argc, char *argv[])
{
  auto m = std::make_shared<Maindeal>(argc, argv);
  return m->getApp()->exec();
}
