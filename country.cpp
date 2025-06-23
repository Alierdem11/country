#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "test1.h"

class Country {
    std::string name;
    double population;
    double area;
    std::string capital;

public:
    Country(const std::string &n, double pop, double a, const std::string &cap)
        : name(n), population(pop), area(a), capital(cap) {}

    std::string getName() const { return name; }
    double getPopulation() const { return population; }
    double getArea() const { return area; }
    std::string getCapital() const { return capital; }

    void setPopulation(double pop) { population = pop; }
    void setArea(double a) { area = a; }
    void setCapital(const std::string &cap) { capital = cap; }

    double populationDensity() const {
        if (area == 0) return 0;
        return population / area;
    }

    void print() const {
        std::cout << "Country: " << name << "\nPopulation: " << population
                  << "\nArea: " << area << " km^2\nCapital: " << capital << "\n";
    }
};

TEST(CountryTest, DensityCalculation) {
    Country c("Sampleland", 5000000, 100000, "Sample City");
    ASSERT_EQ(c.populationDensity(), 50);
    return true;
}

int main() {
    RUN_TEST(CountryTest, DensityCalculation);
    return 0;
}
