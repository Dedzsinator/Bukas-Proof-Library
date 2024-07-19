import numpy as np
import matplotlib.pyplot as plt
import random

# Parameters
num_cities = 20
population_size = 100
mutation_rate = 0.01
num_generations = 500

# Generate random cities
cities = np.random.rand(num_cities, 2)

# Distance matrix
def calculate_distance_matrix(cities):
    num_cities = len(cities)
    distance_matrix = np.zeros((num_cities, num_cities))
    for i in range(num_cities):
        for j in range(i + 1, num_cities):
            distance = np.linalg.norm(cities[i] - cities[j])
            distance_matrix[i, j] = distance
            distance_matrix[j, i] = distance
    return distance_matrix

distance_matrix = calculate_distance_matrix(cities)

# Fitness function
def calculate_fitness(route):
    return 1 / np.sum([distance_matrix[route[i], route[i + 1]] for i in range(len(route) - 1)])

# Create initial population
def create_initial_population(population_size, num_cities):
    population = []
    for _ in range(population_size):
        route = np.random.permutation(num_cities)
        population.append(route)
    return population

# Selection
def selection(population, fitnesses):
    idx = np.random.choice(len(population), size=2, p=fitnesses / np.sum(fitnesses))
    return population[idx[0]], population[idx[1]]

# Crossover
def crossover(parent1, parent2):
    size = len(parent1)
    start, end = sorted(random.sample(range(size), 2))
    child = [None] * size
    child[start:end] = parent1[start:end]
    pointer = 0
    for i in range(size):
        if parent2[i] not in child:
            while child[pointer] is not None:
                pointer += 1
            child[pointer] = parent2[i]
    return child

# Mutation
def mutate(route, mutation_rate):
    for i in range(len(route)):
        if random.random() < mutation_rate:
            j = random.randint(0, len(route) - 1)
            route[i], route[j] = route[j], route[i]
    return route

# Genetic Algorithm
def genetic_algorithm(cities, population_size, mutation_rate, num_generations):
    population = create_initial_population(population_size, len(cities))
    best_route = None
    best_fitness = 0
    fitness_history = []

    for generation in range(num_generations):
        fitnesses = np.array([calculate_fitness(route) for route in population])
        best_idx = np.argmax(fitnesses)
        if fitnesses[best_idx] > best_fitness:
            best_fitness = fitnesses[best_idx]
            best_route = population[best_idx]

        fitness_history.append(best_fitness)

        new_population = []
        for _ in range(population_size):
            parent1, parent2 = selection(population, fitnesses)
            child = crossover(parent1, parent2)
            child = mutate(child, mutation_rate)
            new_population.append(child)
        population = new_population

        # Visualization
        if generation % 10 == 0 or generation == num_generations - 1:
            plt.clf()
            plt.subplot(1, 2, 1)
            plt.plot(fitness_history)
            plt.title('Fitness Function')
            plt.xlabel('Generation')
            plt.ylabel('Fitness')

            plt.subplot(1, 2, 2)
            route = np.append(best_route, best_route[0])
            plt.plot(cities[route, 0], cities[route, 1], 'o-')
            plt.title('Current Circuit')
            plt.pause(0.01)

    plt.show()
    return best_route, best_fitness

# Run the Genetic Algorithm
best_route, best_fitness = genetic_algorithm(cities, population_size, mutation_rate, num_generations)
print(f'Best route: {best_route}')
print(f'Best fitness: {best_fitness}')