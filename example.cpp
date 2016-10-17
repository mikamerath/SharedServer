// Boost Includes
#include <boost/algorithm/string.hpp>

// Standard Includes
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::string line("Test\tOtherTest\tAnotherTest");
  std::vector<std::string> stringVector;
  boost::split(stringVector, line, boost::is_any_of("\t"));

  std::cout << "The size of the vector is: " << stringVector.size()
            << std::endl;
  for (std::string s : stringVector)
  {
    std::cout << s << std::endl;
  }

  std::cin.get();
  return 0;
}