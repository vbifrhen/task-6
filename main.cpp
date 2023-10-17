#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>


int main(int argc, char* argv[]) {
    std::fstream inFile(argv[1]); // Open the input file
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file" << argv[1];
        return 1;   // Return with error
    }
    int N, a, b;
    inFile >> N >> a >> b;
    std::vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        inFile >> numbers[i];
    }
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [a, b](int n) { return n < a || n > b; }), numbers.end());    

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    auto max_it = std::max_element(numbers.begin(), numbers.end());

    auto even_it = std::find_if(max_it + 1, numbers.end(), [](int n) { return n % 2 == 0; });
    
    int erased_position = -1;
    int erased_value;

    if (even_it != numbers.end()) {
        erased_position = std::distance(numbers.begin(), even_it);
        erased_value = *even_it;
        numbers.erase(even_it);
    }    

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    if (erased_position != -1) {
        std::cout << erased_position << " " << erased_value << "\n";
    }

    std::cout << std::count_if(numbers.begin(), numbers.end(), [](int n) { return n > 0; }) << "\n";
    std::cout << std::count_if(numbers.begin(), numbers.end(), [](int n) { return n < 0; });

    return 0;
}