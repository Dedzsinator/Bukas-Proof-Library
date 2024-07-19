#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <ctime>

class Individual {
public:
    std::vector<int> genes;
    double fitness_value;

    Individual(std::vector<int> genes) : genes(genes), fitness_value(0) {}

    double fitness(std::function<double(const std::vector<int>&)> fitness_function) {
        return fitness_function(genes);
    }
};

class Population {
public:
    std::vector<Individual> individuals;

    Population(int size, std::function<std::vector<int>()> individual_generator) {
        for (int i = 0; i < size; ++i) {
            individuals.emplace_back(individual_generator());
        }
    }

    void evaluate_fitness(std::function<double(const std::vector<int>&)> fitness_function) {
        for (auto& individual : individuals) {
            individual.fitness_value = individual.fitness(fitness_function);
        }
    }

    std::pair<Individual, Individual> select_parents(std::function<double(const std::vector<int>&)> fitness_function) {
        std::vector<double> weights;
        for (const auto& individual : individuals) {
            weights.push_back(individual.fitness(fitness_function));
        }

        std::discrete_distribution<int> distribution(weights.begin(), weights.end());
        std::random_device rd;
        std::mt19937 gen(rd());

        int parent1_index = distribution(gen);
        int parent2_index = distribution(gen);

        return {individuals[parent1_index], individuals[parent2_index]};
    }
};

class GeneticAlgorithm {
public:
    int population_size;
    double mutation_rate;
    double crossover_rate;
    std::function<double(const std::vector<int>&)> fitness_function;
    std::function<std::vector<int>()> individual_generator;
    std::function<std::pair<std::vector<int>, std::vector<int>>(const std::vector<int>&, const std::vector<int>&)> crossover_function;
    std::function<std::vector<int>(std::vector<int>)> mutation_function;
    std::function<bool(const GeneticAlgorithm&)> termination_condition;
    Population population;
    int generation;

    GeneticAlgorithm(int population_size, double mutation_rate, double crossover_rate,
                     std::function<double(const std::vector<int>&)> fitness_function,
                     std::function<std::vector<int>()> individual_generator,
                     std::function<std::pair<std::vector<int>, std::vector<int>>(const std::vector<int>&, const std::vector<int>&)> crossover_function,
                     std::function<std::vector<int>(std::vector<int>)> mutation_function,
                     std::function<bool(const GeneticAlgorithm&)> termination_condition)
        : population_size(population_size), mutation_rate(mutation_rate), crossover_rate(crossover_rate),
          fitness_function(fitness_function), individual_generator(individual_generator),
          crossover_function(crossover_function), mutation_function(mutation_function),
          termination_condition(termination_condition), population(population_size, individual_generator), generation(0) {}

    void run() {
        while (!termination_condition(*this)) {
            ++generation;
            population.evaluate_fitness(fitness_function);
            std::sort(population.individuals.begin(), population.individuals.end(),
                      [this](const Individual& a, const Individual& b) {
                          return a.fitness(fitness_function) > b.fitness(fitness_function);
                      });

            std::vector<Individual> new_population(population.individuals.begin(), population.individuals.begin() + 2); // Elitism

            while (new_population.size() < population_size) {
                auto [parent1, parent2] = population.select_parents(fitness_function);
                std::vector<int> offspring1_genes, offspring2_genes;

                if (static_cast<double>(rand()) / RAND_MAX < crossover_rate) {
                    std::tie(offspring1_genes, offspring2_genes) = crossover_function(parent1.genes, parent2.genes);
                } else {
                    offspring1_genes = parent1.genes;
                    offspring2_genes = parent2.genes;
                }

                if (static_cast<double>(rand()) / RAND_MAX < mutation_rate) {
                    offspring1_genes = mutation_function(offspring1_genes);
                }
                if (static_cast<double>(rand()) / RAND_MAX < mutation_rate) {
                    offspring2_genes = mutation_function(offspring2_genes);
                }

                new_population.emplace_back(offspring1_genes);
                new_population.emplace_back(offspring2_genes);
            }

            population.individuals = new_population;
        }
    }
};

// Example usage:
std::vector<int> example_individual_generator() {
    std::vector<int> genes(10);
    for (int& gene : genes) {
        gene = rand() % 2;
    }
    return genes;
}

double example_fitness_function(const std::vector<int>& genes) {
    return std::accumulate(genes.begin(), genes.end(), 0); // Simple fitness: sum of bits
}

std::pair<std::vector<int>, std::vector<int>> example_crossover_function(const std::vector<int>& parent1_genes, const std::vector<int>& parent2_genes) {
    int point = rand() % (parent1_genes.size() - 1) + 1;
    std::vector<int> offspring1_genes(parent1_genes.begin(), parent1_genes.begin() + point);
    offspring1_genes.insert(offspring1_genes.end(), parent2_genes.begin() + point, parent2_genes.end());

    std::vector<int> offspring2_genes(parent2_genes.begin(), parent2_genes.begin() + point);
    offspring2_genes.insert(offspring2_genes.end(), parent1_genes.begin() + point, parent1_genes.end());

    return {offspring1_genes, offspring2_genes};
}

std::vector<int> example_mutation_function(std::vector<int> genes) {
    int point = rand() % genes.size();
    genes[point] = 1 - genes[point];
    return genes;
}

bool example_termination_condition(const GeneticAlgorithm& ga) {
    return ga.generation >= 100 || std::max_element(ga.population.individuals.begin(), ga.population.individuals.end(),
                                                    [&ga](const Individual& a, const Individual& b) {
                                                        return a.fitness(ga.fitness_function) < b.fitness(ga.fitness_function);
                                                    })->fitness(ga.fitness_function) == 10;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    GeneticAlgorithm ga(
        20,
        0.01,
        0.7,
        example_fitness_function,
        example_individual_generator,
        example_crossover_function,
        example_mutation_function,
        example_termination_condition
    );

    ga.run();

    auto best_individual = *std::max_element(ga.population.individuals.begin(), ga.population.individuals.end(),
                                             [&ga](const Individual& a, const Individual& b) {
                                                 return a.fitness(ga.fitness_function) < b.fitness(ga.fitness_function);
                                             });

    std::cout << "Best individual: ";
    for (int gene : best_individual.genes) {
        std::cout << gene << " ";
    }
    std::cout << "with fitness " << best_individual.fitness(ga.fitness_function) << std::endl;

    return 0;
}