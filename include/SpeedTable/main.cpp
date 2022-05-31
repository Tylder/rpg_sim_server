#include <iostream>
#include "SpeedTable/SpeedTable.h"

using namespace speedTable;

int main() {
  std::cout << "Hello, SpeedTable!" << std::endl;

  countVec entityCounts = {10, 100, 1000, 10000, 100000, 1000000};
  countVec iterationCounts = {10, 100, 1000, 10000, 100000, 1000000};
  countVec threadCounts = {1, 2, 6, 12, 16};

  auto configs = SpeedTable::makeConfigs(entityCounts, iterationCounts, threadCounts);

//  std::vector<Config> configsToRun{configs[0], configs[20]};

  auto durations = SpeedTable::runConfigs(configs, "test.csv");
  std::cout << "End, SpeedTable!" << std::endl;
}
