# NACS

Not Another Configuration System


libnacs is a C library for managing configuration files.

It loosely follows the yml / json format, allowing for de/serialization of human readable files to/from a dynamic structure in memory.

Currently YAML files are supported, using [libyaml](https://github.com/yaml/libyaml) for low level I/O, with plans for JSON and CBOR.

# Usage
Link the library against your application, and use the api in [config.h](https://github.com/kalamara/nacs/blob/master/include/config.h)  to de/serialize configurations.
Refer to the [Doxygen docs](https://github.com/kalamara/nacs/blob/master/Doxyfile) and the [test examples](https://github.com/kalamara/nacs/tree/master/tst) for more information.

# Structure
The main configuration structure config_t is a vector of different types of possible entries:

# INT 
Integer values
```yaml
age:  42
```

# STR
Plain character strings

```yaml
name:  "elvis" 

another_name:  melvin 
```

# SEQ
An indexed sequence of fixed size of blocks of data which follow the same format, in key / value pairs.
A valid sequence begins with an integer which is the size, and is followed by an array of blocks of pairs where the set of keys is the same for each block. 
Each block has two mandatory entries, ID (string) which is the name of the block, and INDEX (integer) which is the zero-based index of the block in the sequence. 
Finally there can be more key / value pairs of strings of parameters per block.

```yaml
name:  temperatures
  - 4
  - ID: north_window
  - INDEX: 0
  - MIN: 0.0
  - MAX: 100.0
  
  - ID: south_window
  - INDEX: 1
  - MIN: -10.0
  - MAX: 40.0
  
  - ID: east_window
  - INDEX: 2
  - MIN: 0.0
  - MAX: 100.0
  
  - ID: west_window
  - INDEX: 3
  - MIN: 0
  - MAX: 100

```


# MAP 
A recursive entry which holds another config_t.

```yaml
hardware:  
  name: "device 1"
  interface: "usb"
    idVendor:           0x8042 
    idProduct:          0x0042 
  name: "device 2"
    interface: "uart"
    port:          1
```




