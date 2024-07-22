import pygame
import numpy as np
import random
import time

# Constants
CANVAS_SIZE = 1024  # Reduced for testing
REGION_SIZE = 256
ZOOM_LEVELS = [256, 128, 64, 32, 16]
WINDOW_SIZE = 1024  # Size of the Pygame window

# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((WINDOW_SIZE, WINDOW_SIZE))
pygame.display.set_caption("World Generation")

# Initialize the canvas with blue (ocean)
canvas = np.full((CANVAS_SIZE, CANVAS_SIZE), 'blue', dtype=object)

def log_and_draw(message):
    print(message)
    draw_world(screen, canvas)
    time.sleep(1)  # Short delay for live updating

def draw_world(screen, canvas):
    colors = {
        'blue': (0, 0, 255),
        'land': (34, 139, 34),
        'desert': (237, 201, 175),
        'savanna': (189, 183, 107),
        'plains': (124, 252, 0),
        'forest': (34, 139, 34),
        'dark forest': (0, 100, 0),
        'mountain': (139, 137, 137),
        'birch forest': (107, 142, 35),
        'swamp': (47, 79, 79),
        'taiga': (0, 128, 128),
        'snowy tundra': (255, 250, 250),
        'snowy taiga': (176, 224, 230)
    }

    screen.fill((0, 0, 0))
    scale = max(canvas.shape[0] // WINDOW_SIZE, 1)
    for x in range(0, canvas.shape[0], scale):
        for y in range(0, canvas.shape[1], scale):
            color = colors.get(canvas[x // scale, y // scale], (0, 0, 255))  # Default to blue for ocean
            pygame.draw.rect(screen, color, (x // scale, y // scale, 1, 1))
    pygame.display.flip()

def add_land(canvas, size, num_islands=1):
    log_and_draw(f"Adding land of size {size} with {num_islands} islands")
    for _ in range(num_islands):
        x = random.randint(0, canvas.shape[0] - size)
        y = random.randint(0, canvas.shape[1] - size)
        canvas[x:x+size, y:y+size] = 'land'
        log_and_draw(f"Added land at ({x}, {y})")

def add_initial_landmass(canvas, portion=0.1):
    log_and_draw(f"Adding initial landmass covering {portion * 100}% of the canvas")
    size = int(np.sqrt(portion) * canvas.shape[0])
    x = random.randint(0, canvas.shape[0] - size)
    y = random.randint(0, canvas.shape[1] - size)
    canvas[x:x+size, y:y+size] = 'land'
    log_and_draw(f"Added initial landmass at ({x}, {y}) covering size {size}x{size}")

def remove_excess_ocean(canvas):
    log_and_draw("Removing excess ocean")
    ocean_indices = np.argwhere(canvas == 'blue')
    for x, y in ocean_indices:
        if (x > 0 and x < canvas.shape[0] - 1 and y > 0 and y < canvas.shape[1] - 1 and
            canvas[x-1, y] == 'blue' and canvas[x+1, y] == 'blue' and
            canvas[x, y-1] == 'blue' and canvas[x, y+1] == 'blue'):
            if random.random() < 0.5:
                canvas[x, y] = 'land'
                log_and_draw(f"Converted ocean at ({x}, {y}) to land")

def add_temperatures(canvas):
    log_and_draw("Adding temperatures")
    land_indices = np.argwhere(canvas == 'land')
    for idx in land_indices:
        temperature = random.choice(['warm', 'temperate', 'cold', 'freezing'])
        canvas[tuple(idx)] = temperature
        log_and_draw(f"Added temperature {temperature} at {tuple(idx)}")

def blend_temperatures(canvas):
    log_and_draw("Blending temperatures")
    temperature_map = {
        'warm': ['temperate'],
        'cold': ['temperate'],
        'freezing': ['cold', 'temperate']
    }
    for x in range(canvas.shape[0]):
        for y in range(canvas.shape[1]):
            if canvas[x, y] in temperature_map:
                neighbors = [
                    canvas[x+dx, y+dy]
                    for dx in [-1, 0, 1] for dy in [-1, 0, 1]
                    if 0 <= x+dx < canvas.shape[0] and 0 <= y+dy < canvas.shape[1]
                ]
                for neighbor in neighbors:
                    if neighbor in temperature_map.get(canvas[x, y], []):
                        canvas[x, y] = 'temperate'
                        log_and_draw(f"Blended temperature at ({x}, {y})")

def assign_biomes(canvas):
    log_and_draw("Assigning biomes")
    biome_map = {
        'warm': ['desert', 'savanna', 'plains'],
        'temperate': ['forest', 'dark forest', 'mountain', 'plains', 'birch forest', 'swamp'],
        'cold': ['forest', 'mountain', 'taiga', 'plains'],
        'freezing': ['snowy tundra', 'snowy taiga']
    }
    biome_probabilities = {
        'warm': [0.5, 1/3, 1/6],
        'temperate': [1/6] * 6,
        'cold': [1/4] * 4,
        'freezing': [3/4, 1/4]
    }
    for x in range(canvas.shape[0]):
        for y in range(canvas.shape[1]):
            if canvas[x, y] in biome_map:
                temperature = canvas[x, y]
                biomes = biome_map[temperature]
                probabilities = biome_probabilities[temperature]
                canvas[x, y] = random.choices(biomes, probabilities)[0]
                log_and_draw(f"Assigned biome {canvas[x, y]} at ({x}, {y})")

def zoom_out(canvas, factor):
    log_and_draw(f"Zooming out by a factor of {factor}")
    new_size = canvas.shape[0] // factor
    new_canvas = np.full((new_size, new_size), 'blue', dtype=object)  # Fill with blue by default

    for x in range(new_size):
        for y in range(new_size):
            block = canvas[x*factor:(x+1)*factor, y*factor:(y+1)*factor]
            unique, counts = np.unique(block, return_counts=True)
            most_frequent = unique[np.argmax(counts)]
            new_canvas[x, y] = most_frequent

    log_and_draw("Zoomed out canvas:")
    print(new_canvas)
    return new_canvas

def generate_world():
    global canvas
    add_initial_landmass(canvas, portion=0.1)
    time.sleep(1)  # Add a 1-second delay after adding initial landmass

    for zoom in ZOOM_LEVELS[1:]:
        canvas = zoom_out(canvas, 2)
        add_land(canvas, zoom, num_islands=3 if zoom == 64 else 1)
        time.sleep(1)  # Add a 1-second delay after each zoom level

    remove_excess_ocean(canvas)
    time.sleep(1)  # Add a 1-second delay after removing excess ocean

    add_temperatures(canvas)
    time.sleep(1)  # Add a 1-second delay after adding temperatures

    add_land(canvas, REGION_SIZE)  # Add another island
    time.sleep(1)  # Add a 1-second delay after adding another island

    blend_temperatures(canvas)
    time.sleep(1)  # Add a 1-second delay after blending temperatures

    assign_biomes(canvas)
    time.sleep(1)  # Add a 1-second delay after assigning biomes

# Generate the world
generate_world()

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((0, 0, 0))
    draw_world(screen, canvas)
    pygame.display.flip()

pygame.quit()
