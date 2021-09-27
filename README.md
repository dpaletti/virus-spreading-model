# A Simple Model for Virus Spreading

This project implements a simplified virus spreading model built using OpenMPI.

The model simulates the movement of individuals given a certain speed, a starting position and direction in a world of rectangular countries. When two individuals are close for 10 or more minutes and one of them is infected, the other becomes infected too. An individual is infected for 10 days and, once they become healthy, they stay immune for 3 months.

This project was created as part of a set of deliveries for Middleware Technologies for Distributed Systems course.

# How to run
## Run locally
Open a terminal, enter the directory with the executable and run:

```sh
mpirun -np NUM_CORES ./virus-spreading
```

## Run distributed
To run our application, passwordless ssh must be set up from the manager to the workers and vice versa. A nfs shared folder must be created and mounted on all machines.
Open a terminal from the manager, enter the directory with the executable and run:

```sh
mpirun -np NUM_CORES -H manager:NUM_CORES_MANAGER,worker:NUM_CORES_WORKER ./virus-spreading
```

where NUM_CORES is the total number of cores, NUM_CORES_MANAGER is the number of cores to use on the manager and  NUM_CORES_MANAGER is the number of cores to use on the worker. More workers with different number of cores can be added. 

## Run configuration
The parameters of the simulation can be edited in the [Configuration file]. 

## Profiling
Make sure plotly and pandas are installed. Move to cmake-build-debug folder and run:
```sh
python3 profiling.py
```
The run configuration can be edited on profiling.py.
## Documentation
The documentation is hosted in the [GitHub Docs] folder.


## Authors
This project was developed by [Chiara Marzano](mailto:chiara.marzano@mail.polimi.it), [Massimiliano Nigro](mailto:massimiliano.nigro@mail.polimi.it), [Daniele Paletti](mailto:daniele.paletti@mail.polimi.it).

[GitHub Docs]: https://github.com/DPaletti/virus-spreading-model/documentation.pdf
[Configuration file]: https://github.com/DPaletti/virus-spreading-model/tree/main/cmake-build-debug/config
