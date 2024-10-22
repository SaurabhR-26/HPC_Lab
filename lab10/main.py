import subprocess
import matplotlib.pyplot as plt

def run_mpi_program(num_processes, message_size):
    result = subprocess.run(
        ['mpirun','--oversubscribe', '-np', str(num_processes), './assignment10B', str(message_size)],
        capture_output=True,
        text=True
    )
    output = result.stdout
    if "Average time for reduce" in output:
        avg_time_str = output.split("Average time for reduce :")[1].split("secs")[0].strip()
        avg_time = float(avg_time_str)
        return avg_time
    else:
        raise RuntimeError(f"Error running the MPI program:\n{result.stderr}")

message_size = 1000 
process_counts = [2, 4]  
average_times = []

for num_processes in process_counts:
    try:
        avg_time = run_mpi_program(num_processes, message_size)
        print(f"Number of processes: {num_processes}, Average time: {avg_time} secs")
        average_times.append(avg_time)
    except RuntimeError as e:
        print(f"Failed to run with {num_processes} processes: {e}")
        average_times.append(None)

plt.figure(figsize=(10, 6))
plt.plot(process_counts, average_times, marker='o', linestyle='-', color='b')
plt.xlabel('Number of Processes')
plt.ylabel('Average Time for MPI_Reduce (seconds)')
plt.title(f'MPI Reduce Performance (Message size: {message_size} bytes)')
plt.grid(True)
plt.show()
