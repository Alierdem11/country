#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "test1.h"

class CountryAction {
public:
    virtual void apply(class Country& c) = 0;
    virtual std::string description() const = 0;
    virtual ~CountryAction() {}
};

class PopulationChange : public CountryAction {
    double newPopulation;
public:
    PopulationChange(double p) : newPopulation(p) {}
    void apply(Country& c) override;
    std::string description() const override { return "Set population"; }
};

class AreaChange : public CountryAction {
    double newArea;
public:
    AreaChange(double a) : newArea(a) {}
    void apply(Country& c) override;
    std::string description() const override { return "Set area"; }
};

class CapitalChange : public CountryAction {
    std::string newCapital;
public:
    CapitalChange(const std::string& cap) : newCapital(cap) {}
    void apply(Country& c) override;
    std::string description() const override { return "Set capital"; }
};

class Country {
    std::string name;
    double population;
    double area;
    std::string capital;
    std::vector<CountryAction*> actions;

public:
    Country(const std::string& n, double pop, double a, const std::string& cap,
            const std::vector<CountryAction*>& plan = {})
        : name(n), population(pop), area(a), capital(cap), actions(plan) {}

    std::string getName() const { return name; }
    double getPopulation() const { return population; }
    double getArea() const { return area; }
    std::string getCapital() const { return capital; }

    void setPopulation(double pop) { population = pop; }
    void setArea(double a) { area = a; }
    void setCapital(const std::string& cap) { capital = cap; }

    double populationDensity() const {
        if (area == 0) return 0;
        return population / area;
    }

    void execute() {
        for (auto* act : actions)
            act->apply(*this);
    }

    void print() const {
        std::cout << "Country: " << name
                  << "\nPopulation: " << population
                  << "\nArea: " << area << " km^2"
                  << "\nCapital: " << capital << "\n";
    }

    ~Country() {
        for (auto* act : actions)
            delete act;
    }

    Country(const Country&) = delete;
    Country& operator=(const Country&) = delete;
};

void PopulationChange::apply(Country& c) { c.setPopulation(newPopulation); }
void AreaChange::apply(Country& c) { c.setArea(newArea); }
void CapitalChange::apply(Country& c) { c.setCapital(newCapital); }

TEST(CountryTest, DensityCalculation) {
    std::vector<CountryAction*> plan;
    Country c("Sampleland", 5000000, 100000, "Sample City", plan);
    ASSERT_EQ(c.populationDensity(), 50);
    return true;
}

TEST(CountryTest, CapitalUpdateViaAction) {
    std::vector<CountryAction*> plan = { new CapitalChange("New Capital") };
    Country c("Examplestan", 3000000, 75000, "Old Capital", plan);
    c.execute();
    ASSERT_EQ(c.getCapital(), "New Capital");
    return true;
}

TEST(CountryTest, AreaChangeAffectsDensityViaAction) {
    std::vector<CountryAction*> plan = { new AreaChange(50000) };
    Country c("Densityland", 2000000, 40000, "Density City", plan);
    double oldDensity = c.populationDensity();
    c.execute();
    ASSERT_TRUE(c.populationDensity() < oldDensity);
    return true;
}

TEST(CountryTest, DirectPopulationUpdate) {
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

TEST(CountryTest, PopulationDensityWithLargeValues) {
    Country c("Gigantica", 1e9, 5e6, "Mega City");
    ASSERT_TRUE(std::abs(c.populationDensity() - (1e9 / 5e6)) < 1e-6);
    return true;
}

TEST(CountryTest, MultipleActions) {
    std::vector<CountryAction*> plan = {
        new PopulationChange(1500000),
        new AreaChange(250000),
        new CapitalChange("New Capital")
    };
    Country c("OldCountry", 1000000, 200000, "Old Capital", plan);
    c.execute();
    ASSERT_EQ(c.getPopulation(), 1500000);
    ASSERT_EQ(c.getArea(), 250000);
    ASSERT_EQ(c.getCapital(), "New Capital");
    return true;
}

TEST(CountryTest, PopulationDensityZeroPopulation) {
    Country c("EmptyLand", 0, 100000, "No City");
    ASSERT_EQ(c.populationDensity(), 0);
    return true;
}

int main() {
    RUN_TEST(CountryTest, DensityCalculation);
    RUN_TEST(CountryTest, CapitalUpdateViaAction);
    RUN_TEST(CountryTest, AreaChangeAffectsDensityViaAction);
    RUN_TEST(CountryTest, DirectPopulationUpdate);
    RUN_TEST(CountryTest, ZeroAreaDensity);
    RUN_TEST(CountryTest, NameAccess);
    RUN_TEST(CountryTest, PopulationDensityWithLargeValues);
    RUN_TEST(CountryTest, MultipleActions);
    RUN_TEST(CountryTest, PopulationDensityZeroPopulation);
    return 0;
}
