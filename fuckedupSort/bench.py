import subprocess
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Configuration
start_size = 10
end_size = 10000000
step_size = 500

# Initialize lists to store sizes and times
sizes = []
times = []

# Create figure and axis for plotting with a larger size
fig, ax = plt.subplots(figsize=(12, 8))  # Increase figure size here
line, = ax.plot([], [], marker='o', linestyle='-', color='b', label='Campsort')

# Plot the known functions
x_values = np.logspace(np.log10(start_size), np.log10(end_size), num=500)
ax.plot(x_values, x_values / x_values.max(), 'r--', label=r'$O(n)$')
ax.plot(x_values, np.log(x_values) / np.log(x_values).max(), 'g--', label=r'$O(\log n)$')
ax.plot(x_values, x_values * np.log(x_values) / (x_values * np.log(x_values)).max(), 'm--', label=r'$O(n \log n)$')
ax.plot(x_values, (x_values ** 2) / (x_values ** 2).max(), 'y--', label=r'$O(n^2)$')

# Set plot labels and title
ax.set_xlabel('Input Size')
ax.set_ylabel('Time (seconds)')
ax.set_title('Campsort vs. Time Complexity Functions')

# Initialize axis limits and scales
ax.set_xscale('log')
ax.set_yscale('log')
ax.grid(True)
ax.legend()

# Set initial limits to avoid log scale errors
ax.set_xlim(start_size, end_size)
ax.set_ylim(1e-3, 10)  # Adjust as needed

# Function to initialize the plot
def init():
    line.set_data([], [])
    return line,

# Function to update the graph
def update_graph(frame):
    size = start_size + frame * step_size
    if size > end_size:
        return line,
    
    # Run the benchmark
    try:
        #print the current size
        print(str(size))
        result = subprocess.run(
            ['./campsort.out', str(size)],
            capture_output=True,
            text=True,
            check=True
        )
        
        # Extract the numeric value from the output
        output_lines = result.stdout.strip().split('\n')
        time_str = output_lines[-1]  # Assuming the last line contains the time value
        elapsed_time = float(time_str)
        
    except subprocess.CalledProcessError as e:
        print(f"Error running C++ executable: {e}")
        elapsed_time = float('inf')
    except ValueError as e:
        print(f"Error converting output to float: {e}")
        elapsed_time = float('inf')
    
    # Update data
    sizes.append(size)
    times.append(elapsed_time)

    # Update plot
    line.set_data(sizes, times)
    
    # Update axis limits
    ax.set_xlim(min(sizes), max(sizes))
    ax.set_ylim(min(times) if times else 1e-3, max(times) if times else 10)

    return line,


# Create an animation
ani = animation.FuncAnimation(
    fig,
    update_graph,
    frames=range((end_size - start_size) // step_size + 1),
    init_func=init,
    repeat=False,
    blit=True
)

# Ensure the animation object is not garbage collected
plt.show()
