all:
	gcc influx/influxData.c pvfs2-perf-mon-example.c -fPIC -g -I /opt/orangefs/include/ -L /opt/orangefs/lib/ -lpvfs2 -ldl -lcurl -lcrypto -lssl -lpthread -lm

