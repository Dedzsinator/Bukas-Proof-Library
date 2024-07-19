import tkinter as tk
from tkinter import ttk
import numpy as np
import random
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

window = tk.Tk()
window.title("Genetic Algorithm Maze Solver")

# Parameters
population_size = 1000
max_generations = 100
initial_mutation_rate = 0.01

# Generate a maze using Prim's algorithm
def generate_maze(width, height):
    maze = np.ones((height, width), dtype=int)
    start = (0, 0)
    end = (height-1, width-1)
    
    maze[start] = 0
    walls = [(start[0]+dy, start[1]+dx) for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)] if 0 <= start[0]+dy < height and 0 <= start[1]+dx < width]
    
    while walls:
        random_wall = random.choice(walls)
        walls.remove(random_wall)
        wx, wy = random_wall
        
        if maze[wx, wy] == 1:
            neighbors = [(wx+dy, wy+dx) for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)] if 0 <= wx+dy < height and 0 <= wy+dx < width]
            num_adjacent_open = sum(maze[nx, ny] == 0 for nx, ny in neighbors)
            if num_adjacent_open == 1:
                maze[wx, wy] = 0
                walls.extend([(wx+dy, wy+dx) for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)] if 0 <= wx+dy < height and 0 <= wy+dx < width and maze[wx+dy, wy+dx] == 1])

    # Ensure start and end points are not surrounded by walls
    ensure_accessibility(maze, start)
    ensure_accessibility(maze, end)
    
    maze[start] = 2
    maze[end] = 3
    return maze, start, end

def ensure_accessibility(maze, point):
    x, y = point
    neighbors = [(x+dy, y+dx) for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)] if 0 <= x+dy < maze.shape[0] and 0 <= y+dx < maze.shape[1]]
    if all(maze[nx, ny] == 1 for nx, ny in neighbors):
        nx, ny = random.choice(neighbors)
        maze[nx, ny] = 0

# Maze representation (0: path, 1: wall, 2: start, 3: end)
maze, start_pos, end_pos = generate_maze(9, 9)

# Precompute wall positions for faster fitness calculations
wall_positions = {(i, j) for i in range(maze.shape[0]) for j in range(maze.shape[1]) if maze[i, j] == 1}

# Split the window into two frames
left_frame = ttk.Frame(window)
left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

right_frame = ttk.Frame(window)
right_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

# Canvas for drawing the maze
canvas_width, canvas_height = 700, 500
canvas = tk.Canvas(left_frame, width=canvas_width, height=canvas_height)
canvas.pack()

# Matplotlib figure for plotting fitness
fig = Figure(figsize=(8, 8), dpi=100)
plot = fig.add_subplot(1, 1, 1)
canvas_fig = FigureCanvasTkAgg(fig, master=right_frame)
canvas_fig.draw()
canvas_fig.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

def draw_maze():
    for i in range(maze.shape[0]):
        for j in range(maze.shape[1]):
            color = "black" if maze[i, j] == 1 else "white"
            if (i, j) == start_pos:
                color = "green"
            elif (i, j) == end_pos:
                color = "red"
            canvas.create_rectangle(j*cell_size, i*cell_size, (j+1)*cell_size, (i+1)*cell_size, fill=color)

# Function to update the canvas and fitness label
def update_canvas(solution, fitness):
    canvas.delete("path")  # Remove the old path
    position = start_pos
    for move in solution:
        next_position = apply_move(position, moves[move])
        if is_valid(next_position):
            canvas.create_line(position[1]*cell_size + cell_size//2, position[0]*cell_size + cell_size//2,
                               next_position[1]*cell_size + cell_size//2, next_position[0]*cell_size + cell_size//2,
                               fill="blue", width=2, tags="path")
            position = next_position
            if position == end_pos:
                break

# Directions
moves = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}

def initialize_population(size):
    return [''.join(random.choice(list(moves.keys())) for _ in range(20)) for _ in range(size)]

def apply_move(position, move):
    return position[0] + move[0], position[1] + move[1]

def is_valid(position):
    return 0 <= position[0] < maze.shape[0] and 0 <= position[1] < maze.shape[1] and position not in wall_positions

def fitness(solution):
    position = start_pos
    path_length = 0
    visited = set()
    for move in solution:
        next_position = apply_move(position, moves[move])
        if is_valid(next_position):
            position = next_position
            path_length += 1
            visited.add(position)
            if position == end_pos:
                return 1000 - path_length  # High fitness for reaching the goal, penalize longer paths
        else:
            path_length += 2  # Penalize hitting walls with higher cost
    # Penalize distance to goal for fitness
    distance_to_goal = np.sum(np.abs(np.array(position) - np.array(end_pos)))
    return 1000 - distance_to_goal - path_length  # Penalize longer paths

def select(population, fitnesses):
    sorted_pop = sorted(zip(population, fitnesses), key=lambda x: x[1], reverse=True)
    return [individual for individual, _ in sorted_pop[:len(population)//2]]

def crossover(parent1, parent2):
    cut1, cut2 = sorted(random.sample(range(1, len(parent1)), 2))
    child1 = parent1[:cut1] + parent2[cut1:cut2] + parent1[cut2:]
    child2 = parent2[:cut1] + parent1[cut1:cut2] + parent2[cut2:]
    return child1, child2

def mutate(solution, mutation_rate):
    solution = list(solution)
    for i in range(len(solution)):
        if random.random() < mutation_rate:
            solution[i] = random.choice(list(moves.keys()))
    return ''.join(solution)

# Function to update the plot
def update_plot(generations, best_fitnesses):
    plot.clear()
    plot.plot(generations, best_fitnesses, marker='o', linestyle='-')
    plot.set_title("Fitness Over Generations")
    plot.set_xlabel("Generation")
    plot.set_ylabel("Fitness")
    plot.set_xticks(range(0, max_generations, max(1, max_generations // 31)))
    plot.set_yticks(range(0, 1001, 50))
    canvas_fig.draw()

def genetic_algorithm_with_visualization():
    population = initialize_population(population_size)
    mutation_rate = initial_mutation_rate
    solution_found = False  # Flag to indicate if a solution has been found
    generation = 0
    generations = []
    best_fitnesses = []

    while generation < max_generations:
        fitnesses = [fitness(individual) for individual in population]
        best_index = fitnesses.index(max(fitnesses))
        best_solution = population[best_index]

        # Check if the current best solution connects start and end points
        if is_solution_path(best_solution):
            solution_found = True
            print(f"Solution found in generation {generation}")
            print(f"Path Solution: {best_solution}")
            update_canvas(best_solution, fitnesses[best_index])
            break
        
        # Record the best fitness of this generation
        generations.append(generation)
        best_fitnesses.append(fitnesses[best_index])
        
        # Introduce elitism: carry over the best individuals
        new_population = select(population, fitnesses)
        
        # Maintain population diversity by adding new random individuals
        while len(new_population) < population_size:
            if random.random() < 0.1:  # 10% chance to introduce new random individual
                new_population.append(''.join(random.choice(list(moves.keys())) for _ in range(20)))
            else:
                parent1, parent2 = random.sample(new_population, 2)
                child1, child2 = crossover(parent1, parent2)
                new_population.append(mutate(child1, mutation_rate))
                if len(new_population) < population_size:
                    new_population.append(mutate(child2, mutation_rate))
        
        population = new_population
        
        # Adjust mutation rate if fitness is stagnating
        if generation > 1 and best_fitnesses[-1] == best_fitnesses[-2]:
            mutation_rate = min(mutation_rate * 1.1, 1.0)  # Increase mutation rate
        else:
            mutation_rate = initial_mutation_rate  # Reset mutation rate

        update_canvas(best_solution, fitnesses[best_index])
        update_plot(generations, best_fitnesses)
        window.update_idletasks()
        window.update()
        
        generation += 1
    
    if not solution_found:
        print("No solution found within the given generations")

def is_solution_path(solution):
    position = start_pos
    for move in solution:
        next_position = apply_move(position, moves[move])
        if is_valid(next_position):
            position = next_position
            if position == end_pos:
                return True
    return False

# Initial setup
cell_size = 500 // max(maze.shape)
draw_maze()

# Start the genetic algorithm with visualization after a short delay
window.after(100, genetic_algorithm_with_visualization)

window.mainloop()