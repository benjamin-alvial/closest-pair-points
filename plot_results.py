import pandas as pd
import matplotlib.pyplot as plt
import math

file_path = 'performance_results_1.txt'
column_names = ['n', 'rep', 'cpu_sl', 'cpu_rd']
raw_df = pd.read_csv(file_path, names=column_names, delimiter=',')

# Specify the chunk size
NUMBER_REPS = 101

# Create an empty DataFrame to store the results
result_df = pd.DataFrame(columns=['chunk', 'n', 'avg_cpu_sl', 'avg_cpu_rd'])

# Iterate through chunks of the CSV file
for chunk_number, chunk_df in enumerate(pd.read_csv(file_path, names=column_names, delimiter=',', chunksize=NUMBER_REPS)):
    chunk_df = chunk_df.reset_index(drop=True)

    # Calculate the average for the cpu time columns
    n = chunk_df['n'][0]
    avg_cpu_sl = chunk_df['cpu_sl'].mean()
    avg_cpu_rd = chunk_df['cpu_rd'].mean()

    # Append the results to the result DataFrame
    result_df = result_df._append({'chunk': chunk_number + 1, 'n': n, 'avg_cpu_sl': avg_cpu_sl, 'avg_cpu_rd': avg_cpu_rd}, ignore_index=True)

# Display the result DataFrame
print(result_df)

# ============ Experiment 1 ============
# Creates histograms to see how the cpu times are distributed, for both algorithms.
print("============ Experiment 1 ============")
exp1_df = raw_df

fixed_n = 50000000

# Filter the DataFrame for the fixed value of n
filtered_df = exp1_df[exp1_df['n'] == fixed_n]

# Set the number of bins for the histogram
num_bins = 10

# Plot histograms for avg_cpu_sl
plt.figure(figsize=(10, 6))

min_value = filtered_df['cpu_sl'].min()
max_value =filtered_df['cpu_sl'].max()

plt.hist(filtered_df['cpu_sl'], bins=num_bins, alpha=0.5, label='cpu_sl')
plt.xlim(min_value, max_value)

plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for n={fixed_n}')
plt.legend()
plt.savefig('exp1-sl.png')
plt.show()

# Plot histograms for avg_cpu_rd
plt.figure(figsize=(10, 6))

min_value = filtered_df['cpu_rd'].min()
max_value =filtered_df['cpu_rd'].max()

plt.hist(filtered_df['cpu_rd'], bins=num_bins, alpha=0.5, label='cpu_rd')
plt.xlim(min_value, max_value)

plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for n={fixed_n}')
plt.legend()
plt.savefig('exp1-rd.png')
plt.show()

# ============ Experiment 2 ============
# Plots the average time taken by each algorithm as a function of the number of points.
print("============ Experiment 2 ============")
exp2_df = result_df
print(exp2_df)

# Plotting
plt.figure(figsize=(10, 6))

# Plot the u column as a function of the radix sort time column
plt.plot(exp2_df['n'], exp2_df['avg_cpu_sl'], label='sweep-line')

# Plot the u column as a function of the quicksort time column
plt.plot(exp2_df['n'], exp2_df['avg_cpu_rd'], label='randomized')

# Set labels and title
plt.xlabel('n')
plt.ylabel('time (s)')

# Show legend
plt.legend()

# Show the plot
plt.savefig('exp2.png')
plt.show()

# ============ Experiment 3 ============
# Plots histogram of times taken by algorithms for 
# different arrays of points of a fixed size.
file_path = 'performance_results_2.txt'
column_names = ['rep', 'cpu_sl', 'cpu_rd']
df = pd.read_csv(file_path, names=column_names, delimiter=',')

# Plot histogram with different colors for each column
plt.hist([df['cpu_sl'], df['cpu_rd']], color=['blue', 'green'], alpha=0.7, label=['cpu_sl', 'cpu_rd'])

# Add labels and title
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title('Histogram of cpu_sl and cpu_rd')

# Add legend
plt.legend()

# Show the plot
plt.savefig('exp3.png')
plt.show()