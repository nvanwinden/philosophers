
# philosophers :spaghetti:
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

**Codam [42 Network] project**: an introduction to  **multithreading**  by solving the dining philosophers problem.

__The dining philosophers problem__

There are one or more philosophers sitting at a round table with a large bowl of spaghetti in the middle. Each philosopher needs two forks to eat. However, there are only **as many forks as philosophers**, one between each two philosophers. 
The aim of this project is to write a threaded program that ensures every philosopher eats. The simulation stops when a philosopher dies of starvation.

The philosophers alternatively **eat, think, or sleep**. While eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and while sleeping, they are not eating nor thinking.  A philosopher takes their right and their left forks to eat, one in each hand. When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.

__Program arguments__

|  |  |
|--|--|
| **number_of_philosophers** | The number of philosophers and also the number of forks. |
| **time_to_die (in ms)** | If a philosopher didn’t start eating *time_to_die* ms since the beginning of their last meal or the beginning of the simulation, they die. |
| **time_to_eat (in ms)** |The time it takes for a philosopher to eat. During that time, they will need to hold two forks.|
|**time_to_sleep (in ms)**|The time a philosopher will spend sleeping.|
|**number_of_times_each_philosopher_must_eat (optional argument)**|If all philosophers have eaten at least *number_of_times_each_philosopher_must_eat* times, the simulation stops. If not specified, the simulation stops when a philosopher dies.|

__Program logs__

Any state change of a philosopher must be formatted as follows in which **timestamp_in_ms** is the current timestamp in ms and **X** the philosopher number:

    timestamp_in_ms X has taken a fork
    timestamp_in_ms X is eating
    timestamp_in_ms X is sleeping
    timestamp_in_ms X is thinking
    timestamp_in_ms X died 

A displayed state message should not be mixed up with another message. A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.


__Skills__
- Imperative programming
- Unix
- Rigor

__Subject__

[Read the full subject](https://github.com/nvanwinden/philosophers/blob/master/en.subject.pdf)

## Instructions 📋

### Clone repo

`git clone https://github.com/nvanwinden/philosophers.git`

### Make

Run `make` in the project's root folder to create the `philo` executable.

### Run

`./philo 50 800 200 200`

## In action :surfing_man:

<img width="1028" alt="Screen Shot 2022-12-29 at 10 33 25 AM" src="https://user-images.githubusercontent.com/58479085/209932291-9dca9024-0c6b-4dcd-bcfd-f92fb996c76b.png">

