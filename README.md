# Internet Traffic

Database Special Topic Training course final project.

## Data

Put following files into `data` directory:

* `car.txt`
* `road.cnode`
* `road.nedge`

## Building

You need to have GNU make and CMake(http://www.cmake.org/) installed.

```
mkdir build && cd build
cmake ..
make
```

### Run

### Run as command line program
```
cd build
./main
```

or

```
python main.py
```

### Run as web server

Python3 and [Django](https://www.djangoproject.com/) are required.

```
cd server
python manage.py runserver [0.0.0.0:PORT]
```

The default port is `8000`. Then open <http://localhost:8000> in your browser.
