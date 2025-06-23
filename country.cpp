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

TEST(CountryTest, CapitalUpdate) {
    Country c("Examplestan", 3000000, 75000, "Old Capital");
    c.setCapital("New Capital");
    ASSERT_EQ(c.getCapital(), "New Capital");
    return true;
}

TEST(CountryTest, AreaChangeAffectsDensity) {
    Country c("Densityland", 2000000, 40000, "Density City");
    double oldDensity = c.populationDensity();
    c.setArea(50000);
    ASSERT_TRUE(c.populationDensity() < oldDensity);
    return true;
}

TEST(CountryTest, PopulationUpdate) {
    Country c("Popland", 1000000, 50000, "Pop City");
    c.setPopulation(2000000);
    ASSERT_EQ(c.getPopulation(), 2000000);
    return true;
}

TEST(CountryTest, ZeroAreaDensity) {
    Country c("Flatland", 100000, 0, "Flat City");
    ASSERT_EQ(c.populationDensity(), 0);
    return true;
}

TEST(CountryTest, NameAccess) {
    Country c("Testonia", 4000000, 60000, "Test City");
    ASSERT_EQ(c.getName(), "Testonia");
    return true;
}

int main() {
    RUN_TEST(CountryTest, DensityCalculation);
    RUN_TEST(CountryTest, CapitalUpdate);
    RUN_TEST(CountryTest, AreaChangeAffectsDensity);
    RUN_TEST(CountryTest, PopulationUpdate);
    RUN_TEST(CountryTest, ZeroAreaDensity);
    RUN_TEST(CountryTest, NameAccess);
    return 0;
}
