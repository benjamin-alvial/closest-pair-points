import pandas as pd
import matplotlib.pyplot as plt
import math
"""
# ============ Experiment 1 ============
# Creates histograms to see how the cpu times are distributed, for both algorithms,
# for a selection of 3 array sizes.

print("============ Experiment 1 ============")
file_path = 'performance_results_1.txt'
column_names = ['n', 'rep', 'cpu_sl', 'cpu_rdu', 'cpu_rdf', 'cpu_rdm']
raw_df = pd.read_csv(file_path, names=column_names, delimiter=',')
exp1_df = raw_df

fixed_n_array = [5000000, 25000000, 50000000]
letters = ['a', 'b', 'c']

for i in [0,1,2]:
    fixed_n = fixed_n_array[i]
    letter = letters[i]

    # Filter the DataFrame for the fixed value of n
    filtered_df = exp1_df[exp1_df['n'] == fixed_n]

    # Set the number of bins for the histogram
    num_bins = 10

    # Plot histograms for avg_cpu_sl
    plt.figure(figsize=(10, 6))
    plt.hist(filtered_df['cpu_sl'], bins=num_bins, alpha=0.5, label='cpu_sl')
    plt.xlabel('time (s)')
    plt.ylabel('frequency')
    plt.title(f'Histogram for n={fixed_n}')
    plt.legend()
    plt.savefig('exp1'+letter+'a.png')
    plt.show()

    # Plot histograms for avg_cpu_rd
    plt.figure(figsize=(10, 6))
    plt.hist([filtered_df['cpu_sl'], filtered_df['cpu_ru'], filtered_df['cpu_rdf'], filtered_df['cpu_rdm']], alpha=0.7, label=['cpu_sl', 'cpu_rdu', 'cpu_rdf', 'cpu_rdm'])
    plt.xlabel('time (s)')
    plt.ylabel('frequency')
    plt.title(f'Histogram for n={fixed_n}')
    plt.legend()
    plt.savefig('exp1'+letter+'b.png')
    plt.show()

# ============ Experiment 2 ============
# Plots the average time taken by each algorithm as a function of the number of points.

print("============ Experiment 2 ============")
file_path = 'performance_results_2.txt'
column_names = ['n', 'rep', 'cpu_sl', 'cpu_rdu', 'cpu_rdf', 'cpu_rdm']
raw_df = pd.read_csv(file_path, names=column_names, delimiter=',')

# Specify the chunk size
NUMBER_REPS = 5

# Create an empty DataFrame to store the results
result_df = pd.DataFrame(columns=['chunk', 'n', 'avg_cpu_sl', 'avg_cpu_rd'])

# Iterate through chunks of the CSV file
for chunk_number, chunk_df in enumerate(pd.read_csv(file_path, names=column_names, delimiter=',', chunksize=NUMBER_REPS)):
    chunk_df = chunk_df.reset_index(drop=True)

    # Calculate the average for the cpu time columns
    n = chunk_df['n'][0]
    avg_cpu_sl = chunk_df['cpu_sl'].mean()
    avg_cpu_rdu = chunk_df['cpu_rdu'].mean()
    avg_cpu_rdf = chunk_df['cpu_rdf'].mean()
    avg_cpu_rdm = chunk_df['cpu_rdm'].mean()

    # Append the results to the result DataFrame
    result_df = result_df._append({'chunk': chunk_number + 1, 'n': n, 'avg_cpu_sl': avg_cpu_sl, 'avg_cpu_rdu': avg_cpu_rdu, 'avg_cpu_rdf': avg_cpu_rdf, 'avg_cpu_rdm': avg_cpu_rdm}, ignore_index=True)

exp2_df = result_df
print(exp2_df)

# Plotting
plt.figure(figsize=(10, 6))

# Plot the time columns as a function of the size column
plt.plot(exp2_df['n'], exp2_df['avg_cpu_sl'], label='sweep line')
plt.plot(exp2_df['n'], exp2_df['avg_cpu_rdu'], label='randomized universal')
plt.plot(exp2_df['n'], exp2_df['avg_cpu_rdf'], label='randomized faster')
plt.plot(exp2_df['n'], exp2_df['avg_cpu_rdm'], label='randomized mersenne')

# Set labels and title
plt.xlabel('n')
plt.ylabel('time (s)')

# Show legend
plt.legend()

# Show the plot
plt.savefig('exp2.png')
plt.show()

"""
# ============ Experiment 3 ============
# Plots histogram of times taken by algorithms for 
# different arrays of points of a fixed size.

print("============ Experiment 3 ============")
file_path = 'performance_results_3.txt'
column_names = ['rep', 'cpu_sl', 'cpu_rdu', 'cpu_rdf', 'cpu_rdm']
df = pd.read_csv(file_path, names=column_names, delimiter=',')
exp3_df = df
print(exp3_df)

# ------- Plotting all in the same plot -------
# Plot histogram with different colors for each column
plt.hist([exp3_df['cpu_sl'], exp3_df['cpu_rdu'], exp3_df['cpu_rdf'], exp3_df['cpu_rdm']], alpha=0.7, label=['cpu_sl', 'cpu_rdu', 'cpu_rdf', 'cpu_rdm'])

# Add labels and title
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title('Histogram of cpu times')

# Add legend
plt.legend()

# Show the plot
plt.savefig('exp3a.png')
plt.show()

# ------- Plotting each in their own plot -------
# Set the number of bins for the histogram
num_bins = 10
fixed_n = 5000000

plt.hist(exp3_df['cpu_sl'], bins=num_bins, alpha=0.5, label='cpu_sl')
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for sweep line for n={fixed_n}')
plt.legend()
plt.savefig('exp3b.png')
plt.show()

plt.hist(exp3_df['cpu_rdu'], bins=num_bins, alpha=0.5, label='cpu_rdu')
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for randomized universal for n={fixed_n}')
plt.legend()
plt.savefig('exp3b.png')
plt.show()

plt.hist(exp3_df['cpu_rdf'], bins=num_bins, alpha=0.5, label='cpu_rdf')
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for randomized faster for n={fixed_n}')
plt.legend()
plt.savefig('exp3c.png')
plt.show()

plt.hist(exp3_df['cpu_rdm'], bins=num_bins, alpha=0.5, label='cpu_rdm')
plt.xlabel('time (s)')
plt.ylabel('frequency')
plt.title(f'Histogram for randomized mersenne for n={fixed_n}')
plt.legend()
plt.savefig('exp3d.png')
plt.show()
