# Exporting the OrangeFS performance counters

To export the performance counters for use with Grafana, you can utilize the InfluxDB import code attached to the pvfs2-perf-mon-exmaple. Before we get into that, there are some additional requirements beyond an OrangeFS installation. 

- A linux-based system with curl development libraries installed
- InfluxDB 
- Grafana

## Installing InfluxDB

We won't go into how to install InfluxDB but instructions can be found on their website [here](https://docs.influxdata.com/influxdb/v1.7/introduction/installation/).  
Note: We are using 1.7

After installation, create a new database to hold the information for the performance counters. Below is an example. 

`
curl -i -XPOST http://localhost:8086/query --data-urlencode "q=CREATE DATABASE orangefs" 
`

## Compiling the performance example

`gcc -o perfExport influx/influxData.c pvfs2-perf-mon-example.c -fPIC -g -I /opt/orangefs/include/ -L /opt/orangefs/lib/ -lpvfs2 -ldl -lcurl -lcrypto -lssl -lpthread -lm`

## Running the performance example

To run the performance example, you will need to construct a query string. Below is an example

`
http://localhost:8086/write?db=orangefs&precision=ms
`
You will need to change `localhost` to be your server's hostname and `orangefs` to be the database you just created. After completing this, it's time to run the exporter program. Below is example usage

`./perfExport -m /mnt/orangefs/ -i http://localhost:8086/write?db=orangefs&precision=ms`

This will insert the performance data into InfluxDB.

## Installing Grafana

Instructions for installing Grafana can be found on their website [here](https://grafana.com/docs/installation/).

## Using the data

By this point, you should be familiar with Grafana's dashboard interface. Assuming all went well, you should be able to start creating graphs using the Grafana GUI. We have a starting point which contains some basic graphs so you can get started faster. The json file can be found [here](todo)

[//]: # (https://grafana.com/docs/http_api/dashboard/)