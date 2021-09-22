import pexpect
import json
import random
import math
import csv
import pandas as pd
import plotly.express as px

CONFIG_PATH = "./config/input.json"
CSV_PATH = "../profiling/results.csv"
EXEC_PATH = "./virus-spreading"
STARTING_CORES = 2


def run_profiling(parameters, step=1, percentage=0.1, simulation_number=10):
    individuals = False
    countries = False
    cores = False
    individual_number = -1
    country_number = -1
    core_number = 4
    for index in range(len(parameters)):
        if parameters[index] == "individuals_number":
            individuals = True
        if parameters[index] == "countries":
            countries = True
        if parameters[index] == "cores":
            cores = True
            core_number = STARTING_CORES
    csv_initialization(parameters, CSV_PATH)
    for sim in range(simulation_number):
        config = input_modification(
            individuals, countries, CONFIG_PATH, step, percentage
        )
        exec_time = simulate(core_number, EXEC_PATH)
        if individuals == True:
            individual_number = config["individuals_number"]
        if countries == True:
            country_number = len(config["countries"])
        if cores == True:
            csv_insertion(
                CSV_PATH, exec_time, country_number, individual_number, core_number
            )
            core_number = core_number + 1
        else:
            csv_insertion(CSV_PATH, exec_time, country_number, individual_number, -1)
    plot(CSV_PATH)


def plot(csv_path):
    df = pd.read_csv(csv_path)
    print(df.head())
    col_names = list(df.columns)
    print(col_names)
    for col_name in col_names[:-1]:
        fig = px.line(df, x=col_name, y=col_names[-1])
        fig.show()


# Runs a simulation with core_number cores, parses the output stream and gives back the execution time
def simulate(core_number, execution_path):
    command = "/usr/bin/mpirun -np " + str(core_number) + " " + execution_path
    print(command)
    exe = pexpect.spawnu(
        command,
        encoding="utf-8",
        codec_errors="ignore",
    )
    exe.expect(pexpect.EOF)
    line = exe.before[exe.before.find("°") + 1 :]
    print(exe.before)
    return line[line.find("(") + 1 : line.find(")")]


# Inserts a new row in the csv file (working)
def csv_insertion(
    csv_path, execution_time, country_number=-1, individuals_number=-1, core_number=-1
):
    fields = []
    if country_number != -1:
        fields.append(str(country_number))
    if individuals_number != -1:
        fields.append(str(individuals_number))
    if core_number != -1:
        fields.append(str(core_number))
    fields.append(str(execution_time))
    writer = csv.writer(open(csv_path, "a+"))
    writer.writerow(fields)


# Initializates csv file with the simulation parameters (working)
def csv_initialization(parameters, csv_path):
    columns = parameters.copy()
    columns.append("execution_time")
    writer = csv.writer(open(csv_path, "w+"))
    writer.writerow(columns)


# Initializes the input json with the specified parameters (Working)
def input_initialization(
    config_path,
    individuals_number=10,
    infected_number=1,
    world_width=100,
    world_length=100,
    country_number=5,
    velocity=10,
    days=28,
    maximum_spreading_distance=5,
    time_step=3600,
    percentage=0.1,
):
    config = json.loads(open(config_path, "r").read())
    config["individuals_number"] = individuals_number
    config["infected_number"] = infected_number
    config["world"]["width"] = world_width
    config["world"]["length"] = world_length
    config["countries"].clear()
    for i in range(country_number):
        country_width, country_length = country_generator(config, percentage)
        config["countries"].append({"width": country_width, "length": country_length})
    config["velocity"] = velocity
    config["days"] = days
    config["maximum_spreading_distance"] = maximum_spreading_distance
    config["time_step"] = time_step
    json.dump(config, open(config_path, "w"))


# Modifies the input json and returns the modified dictionary (working)
def input_modification(individuals, countries, file_path, step=1, percentage=0.1):
    config = json.loads(open(file_path, "r").read())
    if individuals == True:
        config["individuals_number"] = config["individuals_number"] + step
    if countries == True:
        for _ in range(step):
            country_width, country_length = country_generator(config, percentage)
            config["countries"].append(
                {"width": country_width, "length": country_length}
            )
    json.dump(config, open(file_path, "w"))
    return config


# Generates random countries with width and length both between 0 and a percentage of the world width and length (working)
def country_generator(config, percentage):
    width_bound = math.floor(config["world"]["width"] * percentage)
    length_bound = math.floor(config["world"]["length"] * percentage)
    return random.randint(1, width_bound), random.randint(1, length_bound)


if __name__ == "__main__":
    input_initialization(
        CONFIG_PATH,
        individuals_number=300,
        infected_number=30,
        world_width=500,
        world_length=500,
        country_number=150,
        time_step=1800,
        percentage=0.05,
    )
    run_profiling(["cores"], step=1, simulation_number=3)
